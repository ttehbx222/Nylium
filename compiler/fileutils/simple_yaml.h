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

#include "file_io.h"
#include "serializer.h"
#include <map>

namespace yaml {
	enum class Type {
		TABLE,
		YAML_NULL,
		LINK,
		INT,
		FLOAT,
		STRING,
		LIST
	};
	class Value {
	private:
		Type value_type;
		serializer::Serializable<std::string>* value_value;
	public:
		Value();
		Value(std::string& value);
		Value(long long value);
		Value(long double value);
		Value(std::vector<std::string>& value);
		Value(std::vector<long long>& value);
		Value(std::vector<long double>& value);
		Value(Type type, serializer::Serializable<std::string>* value_value);
		static Value link(std::string& value);
		static Value detect(std::string& value);
		inline Type type() {
			return value_type;
		}
		template<class T>
		T& value();
		std::string& value();
	};
	class Node {
	private:
		Type node_type;
	public:
		inline Node(Type type) {
			node_type = type;
		}
		inline Type type() {
			return node_type;
		}
	};
	class ValueNode : public Node {
	private:
		Value node_value;
	public:
		inline ValueNode(Value& value) : Node(value.type()) {
			node_value = value;
		}
		inline Value& value() {
			return node_value;
		}
	};
	class Table : public Node {
	private:
		std::map<std::string, Node> content;
	public:
		Table();
		Node& get(std::string& key);
	};
	class Config : public Table{
	private:
		io::TextFile* config_file;
	public:
		Config(io::TextFile& file);
		Config(std::string& file);
		void save();
	};
}