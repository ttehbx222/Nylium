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
#include "../code_bodies/compilable/Scope.hpp"
#include "../utils/DeclarationSearch.hpp"
#include "../../../fileutils/file_io.hpp"
#include "Project.hpp"


namespace nylium{

    class Text; //defined in 0_CharSequences.hpp

    struct FileInterface : ProjectContent {
        const DeclarationSearch f_accessibles;
        std::string name, import_path;
        const std::vector<FileInterface*> imports;

        const Scope main_scope;

        io::File* file;

        Package* parent;
        Project* project;

        Text* f_text;

    };

}