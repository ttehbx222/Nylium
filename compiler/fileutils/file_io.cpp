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

namespace io {
	File::File(std::string path) {
		name = path;
		file_ofstream.open(path);
		file_ifstream.open(path);
	}
	TextFile::TextFile(std::string path) : File(path) {
		std::ifstream& file = ifstream();
		if (file.good()) {
			file_content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
		}
	}
	void TextFile::save() {
		ofstream() << file_content;
	}
}