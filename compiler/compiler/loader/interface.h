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
	class Package;
	class FileInterface : public ProjectObject{
	private:
		std::map<std::string, std::vector<codebody::Declaration>> public_accessibles, protected_accessibles, private_accessibles;
		std::string name, import_path = "";
		std::vector<FileInterface*> imports;

		codebody::SCOPE main_scope;

		io::File* file;
	public:
		FileInterface(io::File* file, Package* root) {
			this->file = file;
			size_t index;
			std::string parent_path = file->parent_path();
			{
				std::string local_path = io::local_path();
				size_t local_path_length = local_path.size();
				if (parent_path.rfind(local_path, 0) == 0) {
					parent_path = parent_path.substr(local_path_length + 1, parent_path.size() - local_path_length - 1);
				}
			}
			//TODO regexx replace / with into import path
			
			//TODO set in package
		}
		bool isInterface() {
			return true;
		}
		inline codebody::SCOPE scope() {
			return main_scope;
		}
		//TODO access accessibles
	};
	class Package : public ProjectObject {
	private:
		std::string absolute_path;
		std::map<std::string, ProjectObject*> objects;
	public:
		bool isInterface() {
			return false;
		}
		inline ProjectObject* get(std::string path, log::TextBlock& text_block, bool* error_flag) {
			ProjectObject* result;
			size_t index = path.find_first_of('.');
			if (index == std::string::npos) {
				result = objects.at(path);
			}
			else {
				ProjectObject* local = objects.at(path.substr(0,index));
				if (local == nullptr) {
					(*error_flag) = true;
					log::log(text_block, log::LOGLEVEL::ERROR, std::vector<std::string>(), log::CODE::INTERFACE_NOT_FOUND);
					break;
				}
				if (local->isInterface()) {
					(*error_flag) = true;
					log::log(text_block, log::LOGLEVEL::ERROR, std::vector<std::string>(), log::CODE::IMPORT_INTO_INTERFACE);
					break;
				}
				result = ((Package*)local)->get(path.substr(index + 1, path.size() - index - 1), text_block, error_flag);
			}
			if (result == nullptr && !(*error_flag)) {
				log::log(text_block, log::LOGLEVEL::ERROR, std::vector<std::string>(), log::CODE::INTERFACE_NOT_FOUND); //NO_EFFECT
			}
			return result;
		}
		inline bool set(std::string path, FileInterface* f_interface, log::TextBlock& text_block) {
			bool error = false;
			size_t index = path.find_first_of('.');
			if (index == std::string::npos) {
				objects.insert(std::pair<std::string, ProjectObject*>(path, f_interface));
			}
			else {
				std::string sub_path = path.substr(0, index);
				ProjectObject* local = objects.at(sub_path);
				if (local == nullptr) {
					local = new Package();
					objects.insert(std::pair<std::string, ProjectObject*>(sub_path))
				}
				else if (local->isInterface()) {
					log::log(text_block, log::LOGLEVEL::ERROR, std::vector<std::string>(), log::CODE::PACKAGE_INTERFACE_OVERLAP);
					error = true;
					return error;
				}
				error = local->set(path.substr(index + 1, path.size() - index - 1), f_interface, text_block);
			}
			return error;
		}
	};
}