cmake_minimum_required(VERSION 3.28.3)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.88.0 COMPONENTS program_options)

include_directories(lib)

if (Boost_FOUND)
    add_executable(pgm_editor pgm_editor.cpp)
    target_include_directories(pgm_editor PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(pgm_editor PUBLIC ${Boost_LIBRARIES} image_processor_lib)

    add_executable(ppm_editor ppm_editor.cpp)
    target_include_directories(ppm_editor PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(ppm_editor PUBLIC ${Boost_LIBRARIES} image_processor_lib)

    add_executable(image_drawing image_drawing.cpp)
    target_include_directories(image_drawing PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(image_drawing PUBLIC ${Boost_LIBRARIES} image_processor_lib)
endif ()

add_subdirectory(lib)
add_subdirectory(tests)