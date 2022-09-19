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
#include <map>
#include <string>
#include <vector>
#include "../../log/logger.h"
#include "../../fileutils/file_io.h"

namespace nylium{
	namespace codebody {
		class Declaration;
		class Scope;
		typedef Scope* SCOPE;
	}
	struct ProjectObject {
		virtual bool isInterface() = 0;
		inline bool isPackage() {
			return !isInterface();
		}
	};
	class FileInterface : public ProjectObject{
	private:
		std::map<std::string, std::vector<codebody::Declaration>> public_accessibles, protected_accessibles, private_accessibles;
		std::vector<FileInterface*> imports;

		codebody::SCOPE main_scope;

		io::File* file;
	public:
		FileInterface(io::File* file) {
			this->file = file;
		}
		bool isInterface() {
			return true;
		}
		//TODO access accessibles
	};
	struct Package {
		std::map<std::string, ProjectObject*> objects;
		bool isInterface() {
			return false;
		}
		inline ProjectObject* get(std::string path, log::TextBlock& text_block) {
			ProjectObject* result;
			bool error = false;
			size_t index = path.find_first_of('.');
			if (index == std::string::npos) {
				result = objects.at(path);
			}
			else {
				ProjectObject* local = objects.at(path.substr(0,index));
				//TODO null check
				if (local->isInterface()) {
					error = true;
					log::log(text_block, log::LOGLEVEL::ERROR, std::vector<std::string>(), log::CODE::IMPORT_INTO_INTERFACE);
				}
				//TODO
			}
			if (result == nullptr && !error) {
				log::log(text_block, log::LOGLEVEL::ERROR, std::vector<std::string>(), log::CODE::INTERFACE_NOT_FOUND);
			}
		}
	};
}