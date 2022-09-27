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

#include "../fileutils/file_io.h"

namespace nylium {
	class FileInterface;
}


namespace nlog {
	
	enum class CODE {
		NONE = 0,
		UNEXPECTED_CHAR = 1,
		IMPORT_INTO_INTERFACE = 2,
		INTERFACE_NOT_FOUND = 3,
		PACKAGE_INTERFACE_OVERLAP = 4
	};

	enum class LOGLEVEL {
		NONE = 0,
		ERROR = 1,
		WARNING = 2,
		INFO = 3,
		DEBUG_1 = 4,
		DEBUG_2 = 5,
		DEBUG_3 = 6
	};

	struct TextBlock {
		nylium::FileInterface* file;
		size_t line, chararcter, length;
		TextBlock(nylium::FileInterface* file, size_t line, size_t character, size_t length) {
			this->file = file;
			this->line = line;
			this->chararcter = character;
			this->length = length;
		}
	};

	void addLogFile(io::File* file, LOGLEVEL level);
	void logToConsole(LOGLEVEL level);
	void log(TextBlock& location, LOGLEVEL level, std::vector<std::string>& arguments, CODE errorCode = CODE::NONE);
}
#include "../compiler/loader/interface.h"