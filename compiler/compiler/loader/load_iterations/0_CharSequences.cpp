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
#include <string>
#include <regex>

#include "0_CharSequences.hpp"

#include "../character_sequences/Bracket.hpp"
#include "../character_sequences/EmptySeparator.hpp"
#include "../character_sequences/End.hpp"
#include "../character_sequences/ListSeparator.hpp"
#include "../character_sequences/Name.hpp"
#include "../character_sequences/Operator.hpp"
#include "../character_sequences/Value.hpp"

#include "../../../log/logger.hpp"

using namespace nylium;

const char bracket[] = "^[\\(\\)<>{}\\[\\]]";
const char empty_separator[] = "^[ \t]+";
const char end[] = "^;";
const char list_separator[] = "^,";
const char name[] = "^[A-Za-z_][A-Za-z0-9]*";
const char operator_[] = "^[\\+\\-\\*\\/\\&\\|\\^\\!\\=\\:\\.]";

const char value_int_hex[] = "^0x[A-Fa-f0-9]+";
const char value_int_bin[] = "^0b[01]+";
const char value_int_dec[] = "^[0-9]+";

const char value_char[] = "^'[^'\\\\]'|'[\\\\].'";
const char value_str[] = "^\"([^\"\\\\]|[\\\\].)*\"";

const std::regex regex_text(std::string("(")
    +bracket+")|("
    +empty_separator+")|("
    +end+")|("
    +list_separator+")|("
    +name+")|("
    +operator_+")|("
    +value_int_hex+")|("
    +value_int_bin+")|("
    +value_int_dec+")|("
    +value_char+")|("
    +value_str+")");

//TODO create regex without start of line condition

void processLine(Text* text, std::string line, size_t line_number){
    size_t coloumn = 0;
    while(!line.empty()){
        std::smatch results;
        std::regex_search(line, results, regex_text);
        char group = -1;
        char len;
        for (char i = 1; i<12; i++){
            if (len = results[i].length()){
                group = i;
                break;
            }
        }
        if (group == -1){
            //TODO invalid character
        }
        switch(group){
            case 1:
            {
                text->push_back(new Bracket(line, line_number, coloumn));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Bracket: ") + line.substr(0, len));
                break;  
            }
            case 2:
            {
                text->push_back(new EmptySeparator(line, line_number, coloumn));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Empty: ") + line.substr(0, len));
                break;  
            }
            case 3:
            {
                text->push_back(new EndIndicator(line, line_number, coloumn));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: End: ") + line.substr(0, len));
                break;  
            }
            case 4:
            {
                text->push_back(new ListSeparator(line, line_number, coloumn));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Separator: ") + line.substr(0, len));
                break;  
            }
            case 5:
            {
                text->push_back(new Name(line, line_number, coloumn));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Name: ") + line.substr(0, len));
                break;  
            }
            case 6:
            {
                text->push_back(new Operator(line, line_number, coloumn));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Operator: ") + line.substr(0, len));
                break;  
            }
            case 7:
            {
                text->push_back(new Value(line, line_number, coloumn, ValueType::INT_HEX));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Vlaue: ") + line.substr(0, len));
                break;  
            }
            case 8:
            {
                text->push_back(new Value(line, line_number, coloumn, ValueType::INT_BIN));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Value: ") + line.substr(0, len));
                break;  
            }
            case 9:
            {
                text->push_back(new Value(line, line_number, coloumn, ValueType::INT_DEC));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Value: ") + line.substr(0, len));
                break;  
            }
            case 10:
            {
                text->push_back(new Value(line, line_number, coloumn, ValueType::CHAR));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Value: ") + line.substr(0, len));
                break;  
            }
            case 11:
            {
                text->push_back(new Value(line, line_number, coloumn, ValueType::STRING));
                nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Value: ") + line.substr(0, len));
                break;  
            }
            case -1:
            {
                goto pl_error_exit;
            }
        }
        line = line.substr(len, line.size()-len);
    }
    pl_error_exit:
    text->push_back(new EmptySeparator(line, line_number, coloumn));
    nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("DEBUG: Empty: "));
}

Text* nylium::loadCharSequences(FileInterface* fInterface){
    Text* text = new Text();
    size_t line_number = 0;
    std::string line;
    std::ifstream& istream = fInterface->file->ifstream();

    while (std::getline(istream, line)){
        line_number++;
        nlog::log(nlog::LOGLEVEL::DEBUG_2, std::string("DEBUG: Processing line ") + std::to_string(line_number) + " in '" + fInterface->name + "'");
        processLine(text, line, line_number);
    }

    nlog::log(nlog::LOGLEVEL::DEBUG_2, std::string("DEBUG: End of file '") + fInterface->name + "'");

    return text;
}

