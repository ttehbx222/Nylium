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
#include "CompileError.hpp"

#include "../loader/project/Interface.hpp"
#include "../loader/character_sequences/NyliumCharSequence.hpp"
#include "../../log/logger.hpp"
#include "../../log/ansi.h"

#include <regex>

std::regex ansi_color_regex("\033\\[[0-9]*m");

nylium::CompileError::CompileError(FileInterface* file, CharSequence* location, std::string& message, ERROR_CODE code){
    this->file = file;
    this->location = location;
    this->console_message = message + " [" + file->file->path() + "(" + std::to_string(location->line) + ":" + std::to_string(location->coloumn) + ")]";
    
    std::string error_code_str = "";
    switch(code){
        case ERROR_CODE::LS001:{
            error_code_str = "LS001: ";
        }
    }

    console_message = std::string(ANSI::BRIGHT_RED) + error_code_str + ANSI::RED + console_message;
    
    this->code = code;
    this->file_message = std::regex_replace(console_message, ansi_color_regex, "");
    file->project->error = true;
    file->project->errors.push(this);
}

void nylium::CompileError::print(){
    nlog::log(nlog::LOGLEVEL::ERROR, console_message, file_message);
}