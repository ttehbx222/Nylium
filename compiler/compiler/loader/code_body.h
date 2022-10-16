/**
* Copyright 2022 ttehbx222(Lukas Nieswand)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http ://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissionsand
* limitations under the License.
*/
#pragma once
#include "code_body.h"
#include "interface.h"
#include <string>
#include <map>
#include <vector>

namespace nylium {
	namespace codebody{

		class Type;

		enum class Castable {
			CAST_DIRECT,
			CAST_POSSIBLE,
			CAST_IMPOSSIBLE
		};

		enum Visibility {
			PRIVATE = 0x0,
			PROTECTED = 0x1,
			PUBLIC = 0x2
		};

		enum class CodeType {
			SCOPE,
			OPERATION
		};

		enum class OperationType {
			FUNCTION_CALL,
			ASSIGN,
			MEMBER_CALL
		};

		enum class DeclarationType {
			TYPE,
			FIELD,
			FUNCTION,
			REFERENCE
		};

		enum CodeObjectType {
			CODE_LINE = 0x1,
			VALUE_HOLDER = 0x2
		};

		class CodeObject {

		};

		class CodeLine : public CodeObject {

		};

		class ValueHolder : public CodeObject {

		};

		class Scope : public CodeLine {

		};

		class Operation : public CodeLine, public ValueHolder {

		};

		class FunctionCall : public Operation {

		};

		class AssignOperation : public Operation {

		};

		class MemberCall : public Operation {

		};

		class Declaration : public ValueHolder {

		};

		class TypeDeclaration : public Declaration {

		};

		class FieldDeclaration : public Declaration {

		};

		class FunctionDeclaration : public Declaration {

		};

		class ReferenceDeclaration : public Declaration {

		};

		class UnresolvedDeclaration : public Declaration {

		};

		class Specification {

		};

		class Type {

		};

	}
}