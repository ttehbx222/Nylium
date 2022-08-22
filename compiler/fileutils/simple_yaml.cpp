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
#include "simple_yaml.h"

namespace yaml {
	Value::Value() {

	}
	Value::Value(std::string& value) {

	}
	Value::Value(long long value) {

	}
	Value::Value(long double value) {

	}
	Value::Value(std::vector<std::string>& value) {

	}
	Value::Value(std::vector<long long>& value) {

	}
	Value::Value(std::vector<long double>& value) {

	}
	Value::Value(Type type, serializer::Serializable<std::string>* value_value) {

	}
	Value Value::link(std::string value) {

	}
	Value Value::detect(std::string value) {

	}

	std::string& Value::value() {
		
	}
	
	Table::Table() : Node(Type::TABLE) {

	}
	Node& Table::get(std::string& key) {

	}

	
	Config::Config(io::TextFile& file) {

	}
	Config::Config(std::string& file) {

	}
	void Config::save() {

	}
}