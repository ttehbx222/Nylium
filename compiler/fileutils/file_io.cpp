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
#include <fstream>

namespace io {
	File::File(std::string path) {
		std::ifstream file(path);
		file_path = path;
		if (file_exists = file.good()) {
			std::string line;
			while (std::getline(file, &line)) {
				file_content.push_back(line);
			}
		}
	}
	File::save() {
		std::ofstream file(file_path);
		for (std::string line : file_content) {
			file << line << std::endl;
		}
	}
}