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

#include <string>
#include <vector>
#include <fstream>

namespace io {
	class File {
	private:
		std::string name;
		std::ofstream file_ofstream;
		std::ifstream file_ifstream;
	public:
		File(std::string path);
		inline std::ofstream& ofstream() {
			return file_ofstream;
		}
		inline std::ifstream& ifstream() {
			return file_ifstream;
		}
		inline std::string path() {
			return name;
		}
		inline void copyTo(io::File& file) {
			file.ofstream() << ifstream().rdbuf();
		}
	};
	/*class TextFile : public File {
	private:
		std::string file_content;
	public:
		TextFile(std::string path);
		inline std::string& content() {
			return file_content;
		}
		void save();
	};*/
}