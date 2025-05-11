cmake_minimum_required(VERSION 3.28.3)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.88.0 COMPONENTS program_options)

include_directories(lib)

if (Boost_FOUND)
    add_executable(pgm_editor pgm_editor.cpp)
    target_include_directories(pgm_editor PUBLIC ${Boost_INCLUDE_DIRS})
    target_link_libraries(pgm_editor PUBLIC ${Boost_LIBRARIES} image_processor_lib)
endif ()

add_subdirectory(lib)
add_subdirectory(tests)