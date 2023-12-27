# Minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Project name
project(raytracingweekend)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})
