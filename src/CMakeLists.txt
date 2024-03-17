cmake_minimum_required (VERSION 3.22)

project(HexViewer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

set(SOURCE_EXE hex.cpp)
add_executable(hex ${SOURCE_EXE})
