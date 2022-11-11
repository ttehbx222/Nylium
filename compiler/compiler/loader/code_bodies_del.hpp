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

//TODO set constructors

namespace nylium {

	//Define without include
	class LoadLayer;

	//circular dependencies
	class CodeLine;
	class ValueHolder;
	class Scope;
	typedef Scope* SCOPE;
	class Operation;
	class FunctionCall;
	class AssignOperation;
	class MemberCall;
	class Declaration;
	class TypeDeclaration;
	class FieldDeclaration;
	class FunctionDeclaration;
	class ReferenceDeclaration;
	class UnresolvedDeclaration;

	class Type;
	typedef std::vector<Type*> Specification;

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

	enum class ScopeType {
		LOCAL = 0x0,
		OPEN = 0x1,
		NAMESPACE = 0x2
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
		REFERENCE,
		NAMESPACE
	};

	/*enum CodeObjectType {
		NDEF = 0x0,
		CODE_LINE = 0x1,
		VALUE_HOLDER = 0x2
	};

	class CodeObject {
	public:
		virtual CodeObjectType co_Type() { return CodeObjectType::NDEF; }
		virtual CodeObject* convert(LoadLayer* ll); //TODO move to other classes
		virtual Node<BodyMatcher*>* load(); //TODO move to other classes
	};

	class CodeLine : public CodeObject {
	public:
		CodeLine() = delete;
		CodeLine(CodeObject* parent); //TODO check if required
		virtual CodeType c_Type() { return CodeType::NDEF; }
	};

	typedef CodeLine* CODE;*/

	class ValueHolder : public CodeObject {
	protected:
		std::string f_key;
		Type* f_type;
	public:
		ValueHolder() = delete;
		ValueHolder(std::string name, Type* type);
		inline Type* type() { return f_type; }
		inline std::string key() { return f_key; }
	};

	class Scope : public CodeLine {
	private:
		ScopeType f_s_type;
		SCOPE f_parent;
		std::map<std::string, std::vector<Declaration>> f_public_accessibles, f_protected_accessibles, f_private_accessibles;
		FileInterface* f_parent_interface;
		std::vector<CODE> f_code;
	public:
		Scope() = delete;
		Scope(SCOPE scope);
		Scope(FileInterface* file);
		inline SCOPE parent() { return f_parent; }
		inline std::vector<CODE>& code() { return f_code; }
		Visibility visibilityOf(SCOPE scope);
		Declaration* searchDeclaration(UnresolvedDeclaration* decl);
		bool addDeclaration(std::string& name, Visibility visibility, Declaration* decl);

		CodeType c_Type() { return CodeType::SCOPE; }
		virtual ScopeType s_Type() { return f_s_type; }
	};

	class Declaration : public ValueHolder {
	public:
		virtual DeclarationType d_Type() { return DeclarationType::NDEF; }
	};

	class Namespace : public Scope , public Declaration{
	public:
		ScopeType s_Type() { return ScopeType::NAMESPACE; }
		DeclarationType d_Type() { return DeclarationType::NAMESPACE; }
	};

	class Operation : public CodeLine, public ValueHolder {
	private:
		Declaration* f_target;
	public:
		virtual OperationType o_Type() { return OperationType::NDEF; }
		inline Declaration* target() { return f_target; }
	};

	class MemberCall : public Operation {
	public:
		virtual OperationType o_Type() { return OperationType::MEMBER_CALL; }
	};

	class FunctionCall : public Operation {
	private:
		std::vector<ValueHolder*> f_arguments;
	public:
		inline std::vector<ValueHolder*> arguments() { return f_arguments; }

		OperationType o_Type() { return OperationType::FUNCTION_CALL; }
	};

	class AssignOperation : public Operation {
	private:
		ValueHolder* f_source;
	public:
		inline ValueHolder* source() { return f_source; }

		OperationType o_Type() { return OperationType::ASSIGN; }
	};

	class TypeDeclaration : public Declaration {
	private:
		SCOPE f_body;
	public:
		inline SCOPE body() { return f_body; }

		DeclarationType d_Type() { return DeclarationType::TYPE; }
	};

	class FieldDeclaration : public Declaration {
	public:
		DeclarationType d_Type() { return DeclarationType::FIELD; }
	};

	class FunctionDeclaration : public Declaration {
	private:
		Specification f_parameters;
	public:
		inline Specification& parameters() { return f_parameters; }

		DeclarationType d_Type() { return DeclarationType::FUNCTION; }
	};

	class ReferenceDeclaration : public Declaration {
	private:
		Declaration* f_source;
	public:
		inline Declaration* source() { return f_source; }

		DeclarationType d_Type() { return DeclarationType::REFERENCE; }
	};

	class UnresolvedDeclaration : public Declaration {};

	class Type : public TypeDeclaration{
	private:
		Specification f_specification;
	};

}