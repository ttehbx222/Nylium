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

#include "../character_sequences/IllegalCharSequence.hpp"

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

const char first_chars[] = "[]()<>{} \t;,ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_+-*/&|^!=:.0123456789'\"";

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

void processLine(FileInterface* fInterface, Text* text, std::string line, size_t line_number){
    size_t coloumn = 0;
    while(!line.empty()){
        std::smatch results;
        std::regex_search(line, results, regex_text);
        char group = -1;
        char len;
        std::string chars;
        for (char i = 1; i<12; i++){
            if (len = results[i].length()){
                group = i;
                chars = results[i].str();
                break;
            }
        }
        if (group == -1){
            size_t error_size = line.find_first_of(first_chars);
            new IllegalCharSequence(line.substr(0,error_size), line_number, coloumn, fInterface);
            line = line.substr(error_size, line.length() - error_size);
            coloumn += error_size;
            continue;
        }
        switch(group){
            case 1:
            {
                text->push_back(new Bracket(chars, line_number, coloumn));
                break;  
            }
            case 2:
            {
                text->push_back(new EmptySeparator(chars, line_number, coloumn));
                break;  
            }
            case 3:
            {
                text->push_back(new EndIndicator(chars, line_number, coloumn));
                break;  
            }
            case 4:
            {
                text->push_back(new ListSeparator(chars, line_number, coloumn));
                break;  
            }
            case 5:
            {
                text->push_back(new Name(chars, line_number, coloumn));
                break;  
            }
            case 6:
            {
                text->push_back(new Operator(chars, line_number, coloumn));
                break;  
            }
            case 7:
            {
                text->push_back(new Value(chars, line_number, coloumn, ValueType::INT_HEX));
                break;  
            }
            case 8:
            {
                text->push_back(new Value(chars, line_number, coloumn, ValueType::INT_BIN));
                break;  
            }
            case 9:
            {
                text->push_back(new Value(chars, line_number, coloumn, ValueType::INT_DEC));
                break;  
            }
            case 10:
            {
                text->push_back(new Value(chars, line_number, coloumn, ValueType::CHAR));
                break;  
            }
            case 11:
            {
                text->push_back(new Value(chars, line_number, coloumn, ValueType::STRING));
                break;  
            }
        }
        line = line.substr(len, line.size()-len);
        coloumn += len;
    }
    text->push_back(new EmptySeparator(line, line_number, coloumn));
}

void nylium::loadCharSequences(FileInterface* fInterface){
    Text* text = new Text();
    size_t line_number = 0;
    std::string line;
    std::ifstream& istream = fInterface->file->ifstream();

    nlog::log(nlog::LOGLEVEL::DEBUG_2, std::string("DEBUG: Processing file '") + fInterface->name + ".nylium'");

    while (std::getline(istream, line)){
        line_number++;
        processLine(fInterface, text, line, line_number);
    }

    nlog::log(nlog::LOGLEVEL::DEBUG_2, std::string("DEBUG: End of file '") + fInterface->name + ".nylium'");

    fInterface->f_text = text;
}

