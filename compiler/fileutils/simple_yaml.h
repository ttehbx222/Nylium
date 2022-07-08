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

#include "file_io.h"
#include "serializer.h"

namespace yaml {
	enum class type {

	};
	class node {
	public:
		node(type type, serializer::serializable value);
		node(type type, std::string value);
	};
	class table : public node {
	public:
		node& get(std::string key);
	};
	class Config : public table{
	private:
		io::File* config_file;
	public:
		Config(io::File& file);
		Config(std::string file);
		void save();
	};
}