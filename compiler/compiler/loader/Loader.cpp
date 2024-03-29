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
#include "Loader.hpp"

#include "load_iterations/0_CharSequences.hpp"
#include "load_iterations/1_CodeBodies.hpp"
#include "load_iterations/2_InternalLinking.hpp"
#include "native/types/Types.hpp"

#include "project/Interface.hpp"

using namespace nylium;

Project* nylium::loadProject(std::string& name){
    Project* project = new Project(name);
    for (FileInterface* fInterface : project->interfaces){
        loadCharSequences(fInterface);
    }
    project->flushErrors();
    initNativeTypes(project->interfaces.front()); //TODO add own scope
    for (FileInterface* fInterface : project->interfaces){
        loadBodies(fInterface);
    }
    project->flushErrors();
    linkBodies(project);
    project->flushErrors();
    return project;
}