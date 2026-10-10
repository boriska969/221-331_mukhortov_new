cmake_minimum_required(VERSION 3.16)
project(Lab1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(LR1_PassManager)
add_subdirectory(LR1_Protector)
