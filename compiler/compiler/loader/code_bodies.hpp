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
#include "interface.h"
#include <string>
#include <map>
#include <vector>

namespace nylium {

	//Define without include
	class LoadLayer;

	class Type;
	class Declaration;
	class UnresolvedDeclaration;

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
		NDEF,
		SCOPE,
		OPERATION
	};

	enum class OperationType {
		NDEF,
		FUNCTION_CALL,
		ASSIGN,
		MEMBER_CALL
	};

	enum class DeclarationType {
		NDEF,
		TYPE,
		FIELD,
		FUNCTION,
		REFERENCE
	};

	enum CodeObjectType {
		NDEF = 0x0,
		CODE_LINE = 0x1,
		VALUE_HOLDER = 0x2
	};

	class CodeObject {
	public:
		virtual CodeObjectType co_Type() { return CodeType::NDEF; }
		virtual next(LoadLayer* ll);
	};

	class CodeLine : public CodeObject {
	public:
		virtual CodeType c_Type() { return CodeType::NDEF; }
	};

	typedef CodeLine* CODE;

	class ValueHolder : public CodeObject {
	private:
		Type* f_type;
	public:
		inline Type* type() { return f_type; }
	};

	class Scope;
	typedef Scope* SCOPE;

	class Scope : public CodeLine {
	private:
		SCOPE f_parent;
		std::map<std::string, std::vector<Declaration>> f_public_accessibles, f_protected_accessibles, f_private_accessibles;
		FileInterface* f_parent_interface;
		std::vector<CODE> f_code;
	public:
		Scope() {}
		Scope(SCOPE scope) {}
		inline SCOPE parent() { return f_parent; }
		inline std::vector<CODE>& code() { return f_code; }
		CodeType c_Type() { return CodeType::SCOPE };
		Visibility visibilityOf(SCOPE scope);
		Declaration* searchDeclaration(UnresolvedDeclaration* decl);
		bool addDeclaration(std::string& name, Visibility visibility, Declaration* decl);
	};

	class Operation : public CodeLine, public ValueHolder {
	public:
		virtual OperationType o_Type() { return OperationType::NDEF; }
	};

	class FunctionCall : public Operation {

	};

	class AssignOperation : public Operation {

	};

	class MemberCall : public Operation {

	};

	class Declaration : public ValueHolder {
	public:
		virtual DeclarationType d_Type() { return DeclarationType::NDEF; }
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

	typedef std::vector<Type*> Specification;

	class Type : public TypeDeclaration{
	private:
		Specification f_specification;
	};

}