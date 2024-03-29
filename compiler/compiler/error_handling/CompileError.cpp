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
            break;
        }
        case ERROR_CODE::LS002:{
            error_code_str = "LS002: ";
            break;
        }
        case ERROR_CODE::LS003:{
            error_code_str = "LS003: ";
            break;
        }
        case ERROR_CODE::LS004:{
            error_code_str = "LS004: ";
            break;
        }
        case ERROR_CODE::LS005:{
            error_code_str = "LS005: ";
            break;
        }
        case ERROR_CODE::LS006:{
            error_code_str = "LS006: ";
            break;
        }
        case ERROR_CODE::LS007:{
            error_code_str = "LS007: ";
            break;
        }
        case ERROR_CODE::CB001:{
            error_code_str = "CB001: ";
            break;
        }
        case ERROR_CODE::CB002:{
            error_code_str = "CB002: ";
            break;
        }
        case ERROR_CODE::CB003:{
            error_code_str = "CB003: ";
            break;
        }
        case ERROR_CODE::CB004:{
            error_code_str = "CB004: ";
            break;
        }
        case ERROR_CODE::CB005:{
            error_code_str = "CB005: ";
            break;
        }
        case ERROR_CODE::CB006:{
            error_code_str = "CB006: ";
            break;
        }
        case ERROR_CODE::CB007:{
            error_code_str = "CB007: ";
            break;
        }
        case ERROR_CODE::CB008:{
            error_code_str = "CB008: ";
            break;
        }
        case ERROR_CODE::CB009:{
            error_code_str = "CB009: ";
            break;
        }
        case ERROR_CODE::CB010:{
            error_code_str = "CB010: ";
            break;
        }
        case ERROR_CODE::CB998:{
            error_code_str = "CB998: ";
            break;
        }
        case ERROR_CODE::CB999:{
            error_code_str = "CB999: ";
            break;
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

void nylium::warn(const char* message, CharSequence* seq, FileInterface* fInterface){
    nlog::log(nlog::LOGLEVEL::WARNING, std::string(ANSI::YELLOW) + "WARNING: " + message + " [" + fInterface->file->path() + "(" + std::to_string(seq->line) + ":" + std::to_string(seq->coloumn) + ")]");
}