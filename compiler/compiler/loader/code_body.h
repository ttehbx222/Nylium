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
	namespace codebody {

		class TypeDeclaration;
		class Type;

		typedef std::vector<Type*> Specification;

		class Type {
		private:
			TypeDeclaration type;
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

		typedef CodeLine* CODE;

		class Scope;
		typedef Scope* SCOPE;

		class Scope : public CodeLine{
		private:
			SCOPE parent;
			
			std::vector<CODE> code;
		public:
			Scope() {}
			Scope(SCOPE scope) {
				parent = scope;
			}
			inline SCOPE getParent() {
				return parent;
			}
			inline std::vector<CODE>& getCode() {
				return code;
			}
			Visibility canSee(SCOPE scope);
			Declaration& searchAccessibles(SCOPE origin, std::string& key, Specification& sepc);
			void addAccessible(std::string& name, Visibility visibility, Declaration& decl);
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
		protected:
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
			FunctionCall& toCall() {
				return FunctionCall(*this);
			}
		};

		class FunctionCall : public Operation {
		private:
			size_t size;
			ValueHolder* arguments;
		public:
			FunctionCall(Operation& operation) {
				type = FUNCTION_CALL;
			}
			inline void setArguments(ValueHolder* arguments, size_t size) {
				this->size = size;
				this->arguments = arguments;
			}
		};

		enum DeclarationType {
			TYPE,
			FIELD,
			FUNCTION,
			REFRENCE
		};

		struct DeclOptions {
			bool opt_static = false, opt_const = false;
		};

		class TypeDeclaration;
		class FieldDeclaration;
		class FunctionDeclaration;
		class RefrenceDeclaration;

		class Declaration : public ValueHolder {
		protected:
			std::string name;
			Visibility visibility;
			DeclOptions options;
			DeclarationType decl_type;
		public:
			DeclarationType getDeclType() {
				return decl_type;
			}
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

			TypeDeclaration& toType() {
				return TypeDeclaration(*this);
			}
			FieldDeclaration& toField() {
				return FieldDeclaration(*this);
			}
			FunctionDeclaration& toFunction() {
				return FunctionDeclaration(*this);
			}
			RefrenceDeclaration& toRefrence() {
				return RefrenceDeclaration(*this);
			}

		};

		class TypeDeclaration : public Declaration {
		private:
			Scope* class_body;
		public:
			TypeDeclaration() {
				decl_Type = TYPE;
			}
			TypeDeclaration(Declaration& decl) {

			}
		};
		class FieldDeclaration : public Declaration {
		private:
			ValueHolder* initial_value;
		public:
			FieldDeclaration() {
				decl_Type = FIELD;
			}
		};
		class FunctionDeclaration : public Declaration {
		private:
			Scope* function_body;
		public:
			FunctionDeclaration() {
				decl_Type = FUNCTION;
			}
		};
		class RefrenceDeclaration : public Declaration {
		private:
			FieldDeclaration* refrenced;
		public:
			RefrenceDeclaration() {
				decl_Type = REFRENCE;
			}
		};
	}
}