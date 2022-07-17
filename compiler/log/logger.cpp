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
#include "logger.h"
#include <vector>

namespace log {

	std::vector<io::File> log_files;
	bool console = false;

	void log::addLogFile(io::File& file) { //TODO log level
		log_files.push_back(file);
	}

	void log::logToConsole(bool value) { //TODO log level
		console = value;
		if (console) {
			//TODO enable colors
		}
	}

	void log::raw_log(std::string str) {

	}
}