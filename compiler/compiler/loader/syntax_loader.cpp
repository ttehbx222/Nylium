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
#include "loader.h"
#include "code_body.h"
#include "../../log/logger.h"
#include "../../fileutils/file_io.h"
#include "LoadLayer.hpp"

namespace nylium {

	bool load_code(FileInterface* interfaces, Package* package);

	Package* nylium::load(std::string origin, std::vector<std::string>& files) {
		std::map<std::string, FileInterface*>* interfaces = new std::map<std::string, FileInterface*>();
		Package* root = new Package();
		for (std::string file_name : files) {
			io::File* file = new io::File(file_name);
			FileInterface* file_interface = new FileInterface(file, root); //WIP
		}
		for (auto const& [path, file_interface] : interfaces) {
			LoaderLayer* loader_layer = new LoaderLayer();
			loader_layer->info.scope = file_interface->scope();

			bool success = load_code(file_interface, root, loader_layer);
			//TODO error handling

			delete loader_layer;
		}
		return root;
 	}

	bool load_code(FileInterface* interfaces, Package* package, LoadLayer* ll) {


		return true;
	}
}