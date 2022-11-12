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

#include "code_bodies/compilable/AssignOperation.hpp"
#include "code_bodies/compilable/FunctionCallOperation.hpp" //includes CallOperation.hpp
#include "code_bodies/compilable/FunctionDeclaration.hpp" //includes NamespaceDeclaration.hpp
#include "code_bodies/compilable/Keyword.hpp"
#include "code_bodies/compilable/ReferenceDeclaration.hpp" //includes FieldDeclaration.hpp
#include "code_bodies/Type.hpp" //includes TypeDeclaration.hpp
#include "project/LoadLayer.hpp"

namespace nylium{

    CodeObject* constructNext(LoadLayer* ll);

}