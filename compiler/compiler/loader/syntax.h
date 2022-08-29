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
#include <vector>

namespace nylium {
	namespace syntax {

		class TypeDeclaration;
		class Type;

		typedef std::vector<Type*> Specification;

		class Type {
		private:
			TypeDeclaration* type;
			Specification spec;
		public:
			//TODO matching
		};

		enum Visibility {
			PRIVATE,
			PROTECTED,
			PUBLIC
		};

		enum CodeType {
			SCOPE,
			OPERATION
		};

		class CodeLine {
		public:
			virtual CodeType getCodeType() = 0;
		};

		class Scope : public CodeLine{
		private:
			Scope* parent;
			std::map<std::string, Declaration*> public_accessables;
			std::map<std::string, Declaration*> protected_accessables;
			std::map<std::string, Declaration*> private_accessables;
			std::vector<CodeLine*> code;
		public:
			Scope() {}
			Scope(Scope* scope) {
				parent = scope;
			}
			inline Scope* getParent() {
				return parent;
			}
			inline std::vector<CodeLine*>& getCode() {
				return code;
			}
			Visibility canSee(Scope* scope);
			Declaration* searchAccessables(Scope* origin, std::string& key, Specification& sepc);
			void addAccessible(std::string& name, Visibility visibility, Declaration* decl);
		};

		class ValueHolder {
		public:
			virtual Type& getType() = 0;
		};

		enum OperationType {
			FUNCTION_CALL,
			OPERATOR,
			ASSIGN,
			MEMBER_CALL
		};

		class FunctionCall;

		class Operation : public ValueHolder, public CodeLine {
		private:
			Type return_value;
			OperationType type;
			std::string operation;
		public:
			inline void setOperation(std::string& operation) {
				this->operation = operation;
			}
			inline std::string& getOperation() {
				return operation;
			}
			inline void setOperationType(OperationType type) {
				this->type = type;
			}
			inline OperationType getOperationType() {
				return type;
			}
			CodeType getCodeType() {
				return OPERATION;
			}
		};

		class FunctionCall : public Operation {
		private:
			size_t size;
			ValueHolder* arguments;
		public:
			void setArguments(ValueHolder* arguments, size_t size);
		};

		enum DeclarationType {
			TYPE,
			FIELD,
			FUNCTION,
			REFERENCE
		};

		struct DeclOptions {
			bool opt_static = false, opt_const = false;
		};

		class Declaration : public ValueHolder {
		protected:
			std::string name;
			Visibility visibility;
			DeclOptions options;
		public:
			virtual DeclarationType getDeclType() = 0;
			inline Visibility getVisibility() {
				return visibility;
			}
			inline Visibility setVisibility(Visibility visibility) {
				this->visibility = visibility;
			}
			inline DeclOptions& getOptions() {
				return options;
			}
			void setName(std::string& name) {
				this->name = name;
			}
			std::string& getName() {
				return name;
			}
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
		class ReferenceDeclaration : public Declaration {
		private:
			FieldDeclaration* refrenced;
		public:
			DeclarationType getDeclType() {
				return REFERENCE;
			}
		};
	}
}