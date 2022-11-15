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
#include <map>

namespace nylium{

    struct ProjectContent{
        virtual bool isInterface() = 0;
    };

    struct Project;

    struct Package : public ProjectContent {
        std::string location;
        std::map<std::string, ProjectContent*> contents;

        Package(std::string& location);
        void loadPackage(std::string& path, Project* project);
        bool isInterface(){ return false; }
    };

    struct Project : public Package {
        std::string name;
        std::string file_path;
        std::vector<ProjectContent*> interfaces;
        Project(std::string& name);
    };

}