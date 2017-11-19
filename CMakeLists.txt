cmake_minimum_required(VERSION 3.0)

project(4D_interpol)

file(GLOB AUTO_SOURCES "*.cpp" "*.h")

add_executable(Run ${AUTO_SOURCES})