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

#include "NyliumCharSequence.hpp"

namespace nylium{

    enum class BracketType{
        VALUE_BRACKET,
        SCOPE_BRACKET,
        SPECIFIER_BRACKET, // possible converted to operator later
        INDEX // later converted to operator
    };

    struct Bracket : public CharSequence {
        BracketType type;
        bool open; //true = '(<{[', false = ']}>)'

        CharSequenceType getType(){ return CharSequenceType::BRACKET; }
    };

}