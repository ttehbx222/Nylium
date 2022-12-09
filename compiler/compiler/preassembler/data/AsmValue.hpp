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

#include "Registers.hpp"

namespace nylium{

    struct AssemblyValue{
    };

    struct AssemblyLiteral : public AssemblyValue {
        size_t f_size;
        void* f_data;
    };

    struct AssemblyRegister : public AssemblyValue {
        SIZE f_size;
        REGISTER f_register;
    };

    struct PendingReference;

    struct AssemblyMemoryReference : public AssemblyValue {
        SIZE f_size;
        PendingReference* f_ref;
    };

}