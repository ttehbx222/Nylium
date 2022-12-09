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

#include "../fileutils/file_io.hpp"

#define LOGGING_TABULATOR "   "

namespace nlog {

	enum class LOGLEVEL {
		NONE = 0,
		ERROR = 1,
		WARNING = 2,
		INFO = 3,
		DEBUG_0 = 4,
		DEBUG_1 = 5,
		DEBUG_2 = 6,
		DEBUG_3 = 7
	};

	void init();

	void addLogFile(io::File* file, LOGLEVEL level);
	void ConsoleLogFilter(LOGLEVEL level);
	LOGLEVEL lowestRelevantLogLevel(); //TODO wording highest/lowest
	void log(LOGLEVEL level, std::string& console_out, std::string& file_out = std::string("") /*If file_out is empty file_out = console_out*/);
}