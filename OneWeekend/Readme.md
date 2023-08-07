# Intro

This folder contains the version of the first weekend of the Raytracing in one weekend series.

# Building

Currently it depends on the stb_image as suggested by the tutorials.

## Windows

It makes use of Visual Studio 2022, and third party dependecies are expected to have been installed via vcpkg.

## POSIX OSes

Initial support has been added for clang 17, alongside cmake 3.26 and ninja 1.11.1.

Note that there are still some issues, see the CMakeLists.txt file for more information.
