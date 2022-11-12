cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(NyliumCompiler)

#compiler.loader.character_sequences
#compiler.loader.code_bodies
add_executable(NyliumCompiler "compiler/loader/code_bodies/CodeObject.cpp")
#compiler.loader.load_iterations
add_executable(NyliumCompiler "compiler/loader/load_iterations/0_CharSequences.cpp")
#compiler.loader.native.keywords
#compiler.loader.native.types
#compiler.loader.project
#compiler.loader.utils
#compiler.loader