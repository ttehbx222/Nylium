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
#include "ansi.h"

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

	LOGLEVEL lowestRelevantLogLevel(){
		return lowest;
	}

	void nlog::log(LOGLEVEL level, std::string& console_out, std::string& file_out) {
		if (level > lowest){
			return;
		}
		if (file_out.length() == 0){
			file_out = console_out;
		}
		std::string color_string = "";
		std::string level_string = "";
		switch(level){
			case LOGLEVEL::DEBUG_0:
			{
				color_string = ANSI::BRIGHT_CYAN;
				level_string = "DEBUG: ";
				break;
			}
			case LOGLEVEL::DEBUG_1:
			case LOGLEVEL::DEBUG_2:
			case LOGLEVEL::DEBUG_3:
			{
				color_string = ANSI::CYAN;
				level_string = "DEBUG: ";
				break;
			}
			case LOGLEVEL::ERROR:
			{
				color_string = ANSI::RED;
				level_string = "ERROR: ";
				break;
			}
			case LOGLEVEL::INFO:
			{
				level_string = "INFO: ";
				break;
			}
			case LOGLEVEL::NONE:
			{
				color_string = ANSI::GREY;
				break;
			}
		}
		if (console >= level){
			std::cout << ANSI::RESET << PREFIX << color_string << level_string << console_out << ANSI::RESET << std::endl;
		}
		for (auto log_file : log_files) {
			if (log_file.second >= level) {
				log_file.first->ofstream() << PREFIX << level_string << file_out << std::endl;
			}
		}
	}

	#ifdef _WIN64

	#include <Windows.h>
	#include <wchar.h>
	#include <stdio.h>
	#include <conio.h>

	void nlog::init(){
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE)
		{
			return;
		}
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		if (hIn == INVALID_HANDLE_VALUE)
		{
			return;
		}
	
		DWORD dwOriginalOutMode = 0;
		DWORD dwOriginalInMode = 0;
		if (!GetConsoleMode(hOut, &dwOriginalOutMode))
		{
			return;
		}
		if (!GetConsoleMode(hIn, &dwOriginalInMode))
		{
			return;
		}

		DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

		DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
		if (!SetConsoleMode(hOut, dwOutMode))
		{
			dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
			if (!SetConsoleMode(hOut, dwOutMode))
			{
				std::cout << "Failed to set any VT mode" << std::endl;
				return;
			}
		}
	}

	#endif
}