cmake_minimum_required(VERSION 3.20)
project(software-renderer CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(OpenMP REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/renderer.cpp
    src/framebuffer.cpp
    src/rasterize.cpp
    src/math.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 OpenMP::OpenMP_CXX )

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
