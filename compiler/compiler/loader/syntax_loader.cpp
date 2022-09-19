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
#include "loader.h"
#include "code_body.h"
#inclued "../../log/logger.h"
#include "../../fileutils/file_io.h"

namespace nylium {

	enum SCOPE_DEPTH {
		MAIN,
		NAMESPACE
	};

	struct LoaderLayer {
		std::vector<std::pair<size_t, size_t>> vb_sb_memory;
		size_t vb_open = 0, sb_open = 0, line = 0, character = 0;
		bool more = true;
		codebody::SCOPE scope;
		io::File* file;
		std::vector<std::string> past_lines;
		std::string current_line;
		inline void operator + (codebody::SCOPE& scope) {
			this->scope = scope;
			vb_sb_memory.push_back(std::pair<size_t, size_t>(vb_open, sb_open));
			vb_open = sb_open = 0;
		}
		inline void operator --() {
			//TODO vb sb check
			scope = scope->getParent();
		}
		inline void new_line() {
			past_lines.push_back(current_line);
			more = std::getline(file->ifstream(), current_line);
			if (more) {
				character = current_line.find_first_not_of(" \t");
				line++;
			}
		}
	};

	typedef LoaderLayer* LL;

	std::map<std::string, FileInterface*>* nylium::load(std::string origin, std::vector<std::string>& files) {
		std::vector<FileInterface*>* interfaces;
		for (std::string file_name : files) {
			io::File* file = new io::File(file_name);
			LoaderLayer* loader_layer = new LoaderLayer();
			FileInterface* file_interface = new FileInterface

			//TODO loading

			delete loader_layer;
		}
 	}
}