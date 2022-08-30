cmake_minimum_required (VERSION 3.21)

project ("Q3D")

find_package(SDL2 2.0.14 REQUIRED)
find_package(spdlog REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

add_executable("Q3D" "Main.cpp")

add_subdirectory ("Core")
add_subdirectory ("Graphics")
add_subdirectory ("Math")
add_subdirectory ("ECS")
add_subdirectory ("AssetCore")
add_subdirectory ("Utility")

set_target_properties("Q3D"
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        CXX_STANDARD 17
        CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories("Q3D" PRIVATE
    SDL2::SDL2
    spdlog::spdlog
    )
target_link_libraries("Q3D" PRIVATE
    SDL2::SDL2
    spdlog::spdlog
    Eigen3::Eigen
    fmt::fmt
    assimp::assimp
    EnTT::EnTT)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/../Assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets)