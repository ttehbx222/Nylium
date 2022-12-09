cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(NyliumCompiler)
add_executable(NyliumCompiler "nylium.cpp"
#compiler.error_handling
"compiler/error_handling/CompileError.cpp"
"compiler/error_handling/errors/CB001.cpp"
"compiler/error_handling/errors/CB004.cpp"
#compiler.loader.character_sequences
"compiler/loader/character_sequences/Bracket.cpp"
"compiler/loader/character_sequences/Value.cpp"
"compiler/loader/character_sequences/NyliumCharSequence.cpp"
"compiler/loader/character_sequences/IllegalCharSequence.cpp"
#compiler.loader.code_bodies
"compiler/loader/code_bodies/compilable/AssignOperation.cpp"
"compiler/loader/code_bodies/compilable/CallOperation.cpp"
"compiler/loader/code_bodies/compilable/CastingOperation.cpp"
"compiler/loader/code_bodies/compilable/FieldDeclaration.cpp"
"compiler/loader/code_bodies/compilable/FunctionCallOperation.cpp"
"compiler/loader/code_bodies/compilable/FunctionDeclaration.cpp"
"compiler/loader/code_bodies/compilable/Keyword.cpp"
"compiler/loader/code_bodies/compilable/Literal.cpp"
"compiler/loader/code_bodies/compilable/NamespaceDeclaration.cpp"
"compiler/loader/code_bodies/compilable/Scope.cpp"
"compiler/loader/code_bodies/compilable/TypeDeclaration.cpp"

"compiler/loader/code_bodies/CodeObject.cpp"
"compiler/loader/code_bodies/Declaration.cpp"
"compiler/loader/code_bodies/Operation.cpp"
"compiler/loader/code_bodies/PendingDeclaration.cpp"
"compiler/loader/code_bodies/ValueHolder.cpp"
#compiler.loader.load_iterations
"compiler/loader/load_iterations/0_CharSequences.cpp"
"compiler/loader/load_iterations/1_CodeBodies.cpp"
"compiler/loader/load_iterations/2_InternalLinking.cpp"
#compiler.loader.native.keywords
"compiler/loader/native/keywords/Keywords.cpp"
"compiler/loader/native/keywords/ElseKeyword.cpp"
"compiler/loader/native/keywords/ForKeyword.cpp"
"compiler/loader/native/keywords/IfKeyword.cpp"
"compiler/loader/native/keywords/WhileKeyword.cpp"
#compiler.loader.native.types
"compiler/loader/native/types/Types.cpp"
"compiler/loader/native/types/ClassType.cpp"
"compiler/loader/native/types/BoolType.cpp"
#compiler.loader.project
"compiler/loader/project/Interface.cpp"
"compiler/loader/project/Project.cpp"
#compiler.loader.utils
"compiler/loader/utils/DeclarationMap.cpp"
#compiler.loader
"compiler/loader/Loader.cpp"
#compiler.preassembler
"compiler/preassembler/Preassembler.cpp"
#compiler.preassembler.data
"compiler/preassembler/data/AsmStorage.cpp"
"compiler/preassembler/data/Registers.cpp"
#compiler.preassembler.compilable
"compiler/preassembler/compilable/CompilableBody.cpp"
#fileutils
"fileutils/file_io.cpp"
#log
"log/logger.cpp"
)