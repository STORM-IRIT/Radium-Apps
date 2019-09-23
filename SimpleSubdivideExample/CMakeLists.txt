# Build Simplifier
cmake_minimum_required(VERSION 3.13)

set(app_target subdivide)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Radium REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(
  ${app_target}
  main.cpp
    )

target_link_libraries(
    ${app_target}
    Radium::RadiumCore
    Radium::RadiumIO
    )

