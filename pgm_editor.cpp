#include "image/PGMImage.h"
#include "image/processors/AlphaBetaProcessing.h"
#include "image/processors/GammaProcessing.h"
#include "image/processors/ConvolutionProcessing.h"
#include "image/processors/kernels/IdentityKernel.h"
#include "image/processors/kernels/GaussianBlurKernel.h"
#include "image/processors/kernels/MeanBlurKernel.h"
#include "image/processors/kernels/VerticalSobelKernel.h"
#include "image/processors/kernels/HorizontalSobelKernel.h"
#include <boost/program_options.hpp>
#include <filesystem>

int main(int argc, char *argv[]) {
    namespace po = boost::program_options;
    namespace fs = std::filesystem;
    try {
        float alpha_val = 0.0, beta_val = 0.0, gamma_val = 0.0;
        std::string kernel_name;
        std::string file_path;

        std::set<std::string> valid_kernel_names = {"identity", "mean-blur", "gauss-blur", "v-sobel", "h-sobel"};

        auto kernel_validator = [&valid_kernel_names](const std::string &value) {
            if (valid_kernel_names.find(value) == valid_kernel_names.end()) {
                std::stringstream msg;
                msg << "Invalid value for -ker: " << value << ". Allowed values are: ";
                for (const auto &v: valid_kernel_names) {
                    msg << v << " ";
                }
                throw po::validation_error(po::validation_error::invalid_option_value, "ker", value);
            }
            return value;
        };

        po::options_description desc("Image processor CLI");
        desc.add_options()
                ("help,h", "Produce help message")
                ("a", po::value<float>(&alpha_val), "Float value for alpha")
                ("b", po::value<float>(&beta_val), "Float value for beta")
                ("g", po::value<float>(&gamma_val), "Float value for gamma")
                ("ker", po::value<std::string>(&kernel_name)->notifier(kernel_validator),
                 "String value for kernel name")
                ("file_path", po::value<std::string>(&file_path)->required(), "Input file path");

        po::positional_options_description pos_desc;
        pos_desc.add("file_path", 1);

        // Parse command line
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
                          .options(desc)
                          .positional(pos_desc)
                          .run(),
                  vm);

        po::notify(vm);

        // Help message
        if (vm.count("help")) {
            std::cout << "Usage: pgm_editor [options] file_path\n";
            std::cout << desc << "\n";
            return 0;
        }

        // Validate option groupings
        bool has_a = vm.count("a");
        bool has_b = vm.count("b");
        bool has_g = vm.count("g");
        bool has_ker = vm.count("ker");

        if ((has_a && !has_b) || (!has_a && has_b)) {
            throw std::runtime_error("Both -a and -b must be specified together.");
        }

        int group_count = (has_a && has_b ? 1 : 0) + has_g + has_ker;
        if (group_count > 1) {
            throw std::runtime_error("Arguments -a/-b, -g, and -ker are mutually exclusive.");
        }

        imgproc::PGMImage image, result;
        image.load(file_path);

        imgproc::PGMImageProcessor *processor = nullptr;

        if (has_a && has_b) {
            processor = new imgproc::AlphaBetaProcessing(alpha_val, beta_val);
        } else if (has_g) {
            processor = new imgproc::GammaProcessing(gamma_val);
        } else if (has_ker) {
            imgproc::Kernel *kernel = nullptr;
            if (kernel_name == "identity") {
                kernel = new imgproc::IdentityKernel();
            } else if (kernel_name == "mean-blur") {
                kernel = new imgproc::MeanBlurKernel();
            } else if (kernel_name == "gauss-blur") {
                kernel = new imgproc::GaussianBlurKernel();
            } else if (kernel_name == "v-sobel") {
                kernel = new imgproc::VerticalSobelKernel();
            } else if (kernel_name == "h-sobel") {
                kernel = new imgproc::HorizontalSobelKernel();
            }
            if (kernel) processor = new imgproc::ConvolutionProcessing(kernel);
            else processor = new imgproc::ConvolutionProcessing(); // should never happen but just for 100% safety
        }

        if (processor) processor->processImage(image, result);

        fs::path input_path(file_path);
        std::string filename = input_path.filename().string();
        fs::path parent_dir = input_path.parent_path();
        fs::path output_path = parent_dir / ("modified-" + filename);

        delete processor;
        result.save(output_path.string());
        std::cout << "Saved modified image to: " << output_path.string();

    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
