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

#include "../../log/ansi.h"

namespace nylium{

    enum class ERROR_CODE{
        LS001, //IllegalCharSequence
        CB001, //unexpected char
        CB002, //keyword multi-use
        CB003, //visibility multi-declaration
        CB004, //unexpected end of declaration
    };

    struct FileInterface;
    struct CharSequence;

    struct CompileError{
        FileInterface* file;
        CharSequence* location;
        std::string console_message;
        std::string file_message;
        ERROR_CODE code;
        CompileError(FileInterface* file, CharSequence* location, std::string& message, ERROR_CODE code);
        void print();
    };

}