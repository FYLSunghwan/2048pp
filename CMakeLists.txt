# CMake version
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

# Declare Project
project(G2048pp)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Set enable output of compile commands during generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Includes
include_directories(Includes)
include_directories(Libraries)
include_directories(Libraries/random/include)

# Sources
add_subdirectory(Sources/G2048pp)