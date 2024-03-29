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

#include "../CompileError.hpp"
#include "../../loader/character_sequences/NyliumCharSequence.hpp"

namespace nylium{
    namespace LS005{
        void throwError(CharSequence* seq, FileInterface* fInterface){
                std::string message = std::string("unexpected end of line");
                new CompileError(fInterface, seq, message, ERROR_CODE::LS005);
        }
    }
}