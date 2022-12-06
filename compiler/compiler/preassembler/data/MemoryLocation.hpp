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

#include <map>

#include "Registers.hpp"
#include "../../loader/code_bodies/compilable/TypeDeclaration.hpp"

namespace nylium{

    enum class MemoryState {
        MEMORY,
        REGISTER
    };

    struct MemoryLocation {
        bool fitted = false;
        SIZE f_size;
        MemoryState f_state;
        REG f_address;
    };

    struct TypeTemplate {
        TypeDeclaration* f_target;
        std::map<TypeDeclaration*, MemoryLocation*> f_access;
    };

}