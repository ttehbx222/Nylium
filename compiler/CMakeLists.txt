cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(NyliumCompiler)
add_executable(NyliumCompiler "nylium.cpp"
#compiler.loader.character_sequences
"compiler/loader/character_sequences/Bracket.cpp" "compiler/loader/character_sequences/Value.cpp"
#compiler.loader.code_bodies
"compiler/loader/code_bodies/CodeObject.cpp"
#compiler.loader.load_iterations
"compiler/loader/load_iterations/0_CharSequences.cpp" "compiler/loader/load_iterations/1_CodeBodies.cpp" "compiler/loader/load_iterations/2_InternalLinking.cpp"
#compiler.loader.native.keywords
#compiler.loader.native.types
#compiler.loader.project
"compiler/loader/project/Interface.cpp" "compiler/loader/project/Project.cpp"
#compiler.loader.utils
#compiler.loader
"compiler/loader/Loader.cpp"
#fileutils
"fileutils/file_io.cpp"
#log
"log/logger.cpp"
)