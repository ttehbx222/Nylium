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

namespace nylium{
    
    enum class REGISTER{
        A,
        B,
        C,
        D,
        SI,
        DI,
        BP,
        SP,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15
    };

    enum class SIZE{
        U8 = 1,
        U16 = 2,
        U32 = 4,
        U64 = 8,
        U128 = 16
    };

    using REG = size_t;

    REG reserveUnnamedRegister();

}