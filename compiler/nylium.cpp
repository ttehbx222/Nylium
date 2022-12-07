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

#include "log/logger.hpp"
#include "compiler/loader/Loader.hpp"
#include "compiler/preassembler/Preassembler.hpp"

using namespace nylium;

int main(/*TODO params*/) { //TEST RUN
	nlog::init();
	nlog::ConsoleLogFilter(nlog::LOGLEVEL::DEBUG_3);
	Project* project = loadProject(std::string("TestRun"));
	if (project->error){
		return -1;
	}
	Assembly* assembly = preassembleProject(project);
	return 0;
}