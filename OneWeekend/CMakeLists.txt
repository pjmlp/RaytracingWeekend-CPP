# See https://www.kitware.com/import-cmake-c20-modules/ for how it was done

# Note there are some issues with header units in cmake.
# https://gitlab.kitware.com/cmake/cmake/-/issues/24616

# There is also anothe issue with clang's module support
# https://github.com/llvm/llvm-project/issues/62707
# https://github.com/Kitware/CMake/commit/7b05724ac81c3262ce8aded5578326ecec327ae4

cmake_minimum_required(VERSION 3.26)
project(std_module_example CXX)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")

# Default to C++ extensions being off. Clang's modules support have trouble
# with extensions right now and it is not required for any other compiler
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  include(gcc_modules.cmake)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
# Ensure some code quality is taken care of.
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# Uncoment for debug builds
#set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

add_library(RayTracingLib)
target_sources(RayTracingLib
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    RaytracingLib/algebra.ixx
    RaytracingLib/camera.ixx
    RaytracingLib/color.ixx
    RaytracingLib/hittable.ixx
    RaytracingLib/images.ixx
    RaytracingLib/material.ixx
    RaytracingLib/ray.ixx
    RaytracingLib/RaytracingLib.ixx
    RaytracingLib/scene.ixx
    RaytracingLib/sphere.ixx
)

add_executable(RayTracing Raytracing/main.cpp)
target_link_libraries(RayTracing PRIVATE RayTracingLib)
