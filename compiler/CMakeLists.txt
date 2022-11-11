cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(NyliumCompiler)

#compiler.loader
add_executable(NyliumCompiler "compiler/loader/syntax_loader.cpp")