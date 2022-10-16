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

namespace nylium {
	enum SCOPE_DEPTH {
		MAIN,
		NAMESPACE
	};

	struct LL_info {
		size_t vb_open = 0, sb_open = 0;
		codebody::SCOPE scope;
	};

	struct LoadLayer {
		std::vector<LL_info> memory;
		LL_info info;
		size_t  line = 0, character = 0;
		bool more = true;
		io::File* file;
		std::vector<std::string> past_lines;
		std::string current_line;
		inline void operator + (codebody::SCOPE& scope) {
			memory.push_back(info);
			info = LL_info();
			info.scope = scope;
		}
		inline void operator --() {
			//TODO vb sb check
			info = memory.pop_back();
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

	typedef LoadLayer* LL;
}