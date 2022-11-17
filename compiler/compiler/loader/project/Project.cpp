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
#include "Project.hpp"

#include <filesystem>
#include <regex>

#include "Interface.hpp"

#include "../../../fileutils/file_io.hpp"
#include "../../../log/logger.hpp"

using namespace nylium;

const char package_name[] = "[a-zA-Z0-9_]+";
const char codefile_name[] = "[a-zA-Z0-9_]+\\.nylium";

std::regex regex_package_name(package_name);
std::regex regex_codefile_name(codefile_name);

Package::Package(std::string& location){
    this->location = location;
}

void Package::loadPackage(std::string& path, Project* project){
    std::filesystem::path directory(path);
    std::filesystem::directory_iterator end_itr;
    for (std::filesystem::directory_iterator dir_itr(directory); dir_itr != end_itr; dir_itr++){
        std::string new_path = dir_itr->path().string();
        std::string filename = dir_itr->path().filename().string();
        if (std::filesystem::is_directory(dir_itr->status())){
            if (std::regex_match(filename, regex_package_name)){
                nlog::log(nlog::LOGLEVEL::DEBUG_2, std::string("DEBUG: New Package: '") + location + "." + filename + "'");
                Package* new_package = new Package(location + "." + filename);
                new_package->loadPackage(new_path, project);
                contents.insert(std::pair<std::string, ProjectContent*>(filename, new_package));
            }
        }else{
            if (std::regex_match(filename, regex_codefile_name)){
                nlog::log(nlog::LOGLEVEL::DEBUG_2, std::string("DEBUG: New FileInterface: '") + location + "." + filename + "'");
                filename = filename.substr(0, filename.size()-7);
                contents.insert(std::pair<std::string, ProjectContent*>(filename, new FileInterface(filename, new_path, location + "." + filename, project, this)));
            }
        }
    }
}

Project::Project(std::string& name) : Package(std::string("")){
    this->name = name;
    file_path = io::local_path();
    loadPackage(file_path, this);
}

void Project::flushErrors(){
    while(!errors.empty()){
        errors.front()->print();
        errors.pop();
    }
}