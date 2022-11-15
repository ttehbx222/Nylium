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
#include "logger.hpp"
#include <vector>
#include <iostream>

namespace nlog {

	const char PREFIX[] = "[Nylium] ";

	std::vector<std::pair<io::File*, LOGLEVEL>> log_files;
	LOGLEVEL console = LOGLEVEL::INFO;

	LOGLEVEL lowest = console;

	void nlog::addLogFile(io::File* file, LOGLEVEL level) { //TODO log level
		log_files.push_back(std::pair<io::File*, LOGLEVEL>(file, level));
		if (level > lowest){
			lowest = level;
		}
	}

	void nlog::ConsoleLogFilter(LOGLEVEL level) {
		console = level;
		if (level > lowest){
			lowest = level;
		}
	}

	void nlog::log(LOGLEVEL level, std::string& console_out, std::string& file_out) {
		if (level > lowest){
			return;
		}
		if (file_out.length() == 0){
			file_out = console_out;
		}
		if (console >= level){
			std::cout << PREFIX << console_out << std::endl;
		}
		for (auto log_file : log_files) {
			if (log_file.second >= level) {
				log_file.first->ofstream() << PREFIX << file_out << std::endl;
			}
		}
	}
}