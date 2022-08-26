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
#include <string>
#include <map>

namespace nylium {
	namespace syntax {

		class TypeDeclaration;
		class Type;

		class Specification {
			size_t size;
			Type* spec_types;
		};

		class Type {
		private:
			TypeDeclaration type;
			Specification spec;
		public:
			//TODO matching
		};

		class Scope {
		private:
			Scope* parent;
			std::map<std::string, Declaration*> accessables;
		public:
			inline Scope* getParent() {
				return parent;
			}
			Declaration* searchAccessables(std::string key, Specification sepc);
		};

		class ValueHolder {
		public:
			Type& getType() = 0;
		};

		enum OperationType {
			FUNCTION_CALL,
			OPERATOR,
			ASSIGN,
			MEMBER_CALL
		};

		class Operation : public ValueHolder {
		private:
			OperationType type;
			std::string operation;
		};

		enum DeclarationType {
			TYPE,
			FIELD,
			FUNCTION
		};
		class Declaration : public ValueHolder {
		public:
			virtual DeclarationType getDeclType() = 0;
		};

		class TypeDeclaration : public Declaration {
		private:
			Scope* class_body;
		public:
			DeclarationType getDeclType() {
				return TYPE;
			}
		};
		class FieldDeclaration : public Declaration {
		public:
			DeclarationType getDeclType() {
				return FIELD;
			}
		};
		class FunctionDeclaration : public Declaration {
		private:
			Scope* function_body;
		public:
			DeclarationType getDeclType() {
				return FUNCTION;
			}
		};
	}
}