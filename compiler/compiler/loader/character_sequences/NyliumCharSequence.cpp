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
#include "NyliumCharSequence.hpp"

#include "../../../log/logger.hpp"

void nylium::CharSequence::debug_log(){
    if (nlog::lowestRelevantLogLevel() < nlog::LOGLEVEL::DEBUG_3){
        return;
    }
    std::string message = "(" + std::to_string(line) + ":" + std::to_string(coloumn) + ") ";



    switch(type){
        case CharSequenceType::BRACKET:
        {
            message += "bracket";
            break;
        }
        case CharSequenceType::EMPTY_SEPARATOR:
        {
            message += "empty";
            break;
        }
        case CharSequenceType::END:
        {
            message += "endl";
            break;
        }
        case CharSequenceType::ILLEGAL:
        {
            message += "illegal";
            break;
        }
        case CharSequenceType::LIST_SEPARATOR:
        {
            message += "separator";
            break;
        }
        case CharSequenceType::NAME:
        {
            message += "label";
            break;
        }
        case CharSequenceType::OPERATOR:
        {
            message += "operator";
            break;
        }
        case CharSequenceType::VALUE:
        {
            message += "value";
            break;
        }
    }
    message += ": " + chars;

    nlog::log(nlog::LOGLEVEL::DEBUG_3, message);
}