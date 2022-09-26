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
#include <streambuf>
#include <filesystem>

namespace io {

	std::string local = "";

	File::File(std::string path) {
		name = path;
		file_ofstream.open(path, std::ios_base::out | std::ios_base::app);
		file_ifstream.open(path);
		absolute_parent_path = std::filesystem::path(path).parent_path().string();
	}

	std::string localPath() {
		if (local == "") {
			local = std::filesystem::current_path().parent_path().string();
			if (local.find_last_of('/') == local.size() - 1) {				//removes / at end if there is one
				local = local.substr(0, local.size() - 1);
			}
		}
		return local;
	}
}