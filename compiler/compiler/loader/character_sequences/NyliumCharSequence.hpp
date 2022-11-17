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

namespace nylium{

    enum class CharSequenceType{
        BRACKET,
        NAME,
        OPERATOR,
        VALUE,
        END,
        LIST_SEPARATOR,
        EMPTY_SEPARATOR,
        ILLEGAL
    };

    struct CharSequence {
        std::string chars;
        size_t line, coloumn, length;
        CharSequenceType type;

        void debug_log();

        CharSequence(std::string& content, size_t line_number, size_t coloumn, CharSequenceType type){
            chars = content;
            line = line_number;
            this->coloumn = coloumn;
            length = chars.length(); // check for importance
            this->type = type;
            debug_log();
        }
    };

}