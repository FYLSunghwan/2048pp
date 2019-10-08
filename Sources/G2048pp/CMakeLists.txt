# Target name
set(targetLib G2048lib)
set(targetExecutable G2048pp)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(${targetExecutable} ${sources})
add_library(${targetLib} ${sources})