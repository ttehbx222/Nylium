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
#include <iostream>

namespace nlog {

	

	std::vector<std::pair<io::File*, LOGLEVEL>> log_files;
	LOGLEVEL console = LOGLEVEL::INFO;

	void nlog::addLogFile(io::File* file, LOGLEVEL level) { //TODO log level
		log_files.push_back(std::pair<io::File*, LOGLEVEL>(file, level));
	}

	void nlog::logToConsole(LOGLEVEL level) { //TODO log level
		console = level;
		//TODO add colors
	}

	std::pair<std::string, std::string>* log_unexpected_char(TextBlock& location, LOGLEVEL level, std::vector<std::string>& arguments);
	std::pair<std::string, std::string>* log_unknown_error(TextBlock& location, LOGLEVEL level, CODE code);

	void nlog::log(TextBlock& location, LOGLEVEL level, std::vector<std::string>& arguments, CODE code = 0) {
		std::pair<std::string, std::string>* content = nullptr;
		switch (code) {
		case CODE::UNEXPECTED_CHAR:
		{
			content = log_unexpected_char(location, level, arguments);
			break;
		}
		default:
		{
			content = log_unknown_error(location, level, code);
		}
		}
		
		if (content) {
			std::cout << content->first << std::endl;
			for (auto log_file : log_files) {
				if (log_file.second >= level) {

				}
			}
			delete content;
		}
	}

	std::pair<std::string, std::string>* log_unexpected_char(TextBlock& location, LOGLEVEL level, std::vector<std::string>& arguments) {
		//TODO
		return nullptr;
	}

	std::pair<std::string, std::string>* log_unknown_error(TextBlock& location, LOGLEVEL level, CODE code) {
		//TODO
		return nullptr;
	}

}