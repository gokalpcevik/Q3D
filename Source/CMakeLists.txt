cmake_minimum_required (VERSION 3.21)

project ("Q3D")

find_package(SDL2 2.0.14 REQUIRED)
find_package(spdlog REQUIRED)
find_package(blaze CONFIG REQUIRED)

add_subdirectory ("Main")

set_target_properties("Q3D"
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        CXX_STANDARD 17)

target_include_directories("Q3D" PRIVATE
    SDL2::SDL2
    spdlog::spdlog
    )
target_link_libraries("Q3D" PRIVATE
    SDL2::SDL2
    spdlog::spdlog
    blaze::blaze)
