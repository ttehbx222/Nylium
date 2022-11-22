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

#include "../../error_handling/errors/LS002.hpp"
#include "../../error_handling/errors/LS003.hpp"
#include "../../error_handling/errors/LS004.hpp"
#include "../../error_handling/errors/LS005.hpp"

#include "../../../log/logger.hpp"

using namespace nylium;

const char bracket[] = "^[\\(\\)<>{}\\[\\]]";
const char empty_separator[] = "^[ \t]+";
const char end[] = "^;";
const char list_separator[] = "^,";
const char name[] = "^[A-Za-z_][A-Za-z0-9_]*";
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
        CharSequence* sequence = nullptr;
        switch(group){
            case 1:
            {
                sequence = new Bracket(chars, line_number, coloumn);
                break;  
            }
            case 2:
            {
                /*text->push_back(new EmptySeparator(chars, line_number, coloumn));
                break;  */ //TODO Check for importance
                break;
            }
            case 3:
            {
                sequence = new EndIndicator(chars, line_number, coloumn);
                break;  
            }
            case 4:
            {
                sequence = new ListSeparator(chars, line_number, coloumn);
                break;  
            }
            case 5:
            {
                sequence = new Name(chars, line_number, coloumn);
                break;  
            }
            case 6:
            {
                sequence = new Operator(chars, line_number, coloumn);
                break;  
            }
            case 7:
            {
                sequence = new Value(chars, line_number, coloumn, ValueType::INT_HEX);
                break;  
            }
            case 8:
            {
                sequence = new Value(chars, line_number, coloumn, ValueType::INT_BIN);
                break;  
            }
            case 9:
            {
                sequence = new Value(chars, line_number, coloumn, ValueType::INT_DEC);
                break;  
            }
            case 10:
            {
                sequence = new Value(chars, line_number, coloumn, ValueType::CHAR);
                break;  
            }
            case 11:
            {
                sequence = new Value(chars, line_number, coloumn, ValueType::STRING);
                break;  
            }
        }
        if (sequence){
            text->f_current_target->push(sequence, text);
        }
        line = line.substr(len, line.size()-len);
        coloumn += len;
    }
    //text->push_back(new EmptySeparator(line, line_number, coloumn)); //TODO check for importance
}

void nylium::loadCharSequences(FileInterface* fInterface){
    Text* text = new Text(fInterface);
    size_t line_number = 0;
    std::string line;
    std::ifstream& istream = fInterface->file->ifstream();

    nlog::log(nlog::LOGLEVEL::DEBUG_2, std::string("Processing file '") + fInterface->name + ".nylium'");

    while (std::getline(istream, line)){
        line_number++;
        processLine(fInterface, text, line, line_number);
    }

    nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("End of file '") + fInterface->name + ".nylium'");

    fInterface->f_text = text;
}

/*
CharSequence* Text::read(size_t* read_pos){
    if ((*read_pos) < this->size()){
        return this->at((*read_pos)++);
    }else{
        CharSequence* last_element = this->back();
        return new EndIndicator(std::string(""), last_element->line, last_element->coloumn + last_element->length);
    }
}*/

void SequenceLine::push(CharSequence* in, Text* text){
    switch(in->type){
        case CharSequenceType::END:
        {
            switch(f_parent->elementType()){
                case ElementType::BRACKET:
                {
                    SequenceBracket* parent = ((SequenceBracket*)f_parent);
                    switch(parent->f_btype){
                        case BracketListType::OPERN_LINE_LIST:
                        {
                            LS002::throwError(in, text->f_interface);
                            return;
                        }
                        case BracketListType::SINGLE:
                        {
                            parent->f_btype = BracketListType::ENDED_LINE_LIST;
                            //continue at case ENDED_LINE_LIST
                        }
                        case BracketListType::ENDED_LINE_LIST:
                        {
                            this->f_elements.push_back(in);
                            SequenceLine* line = new SequenceLine(parent);
                            parent->f_contents.push_back(line);
                            text->f_current_target = line;
                            return;
                        }
                    }
                    return; //compiler reasons
                }
                case ElementType::SCOPE:
                {
                    SequenceScope* parent = ((SequenceScope*)f_parent);
                    if (parent == &(text->f_scope)){
                        LS005::throwError(in, text->f_interface);
                        return;
                    }
                    switch(parent->f_stype){
                        case ScopeListType::INITIALIZER_LIST:
                        {
                            LS002::throwError(in, text->f_interface);
                            return;
                        }
                        case ScopeListType::SINGLE:
                        {
                            parent->f_stype = ScopeListType::SCOPE;
                            //continue at case SCOPE
                        }
                        case ScopeListType::SCOPE:
                        {
                            this->f_elements.push_back(in);
                            SequenceLine* line = new SequenceLine(parent);
                            parent->f_contents.push_back(line);
                            text->f_current_target = line;
                            return;
                        }
                    }
                    return; //compiler reasons
                }
            }
            return; //compiler reasons
        }
        case CharSequenceType::BRACKET:
        {
            switch(in->chars[0]){
                case '(':
                {
                    SequenceBracket* bracket = new SequenceBracket(this);
                    SequenceLine* line = new SequenceLine(bracket);
                    f_elements.push_back(bracket);
                    bracket->f_contents.push_back(line);
                    text->f_current_target = line;
                    return;
                }
                case ')':
                {
                    if (f_parent->elementType() != ElementType::BRACKET){
                        LS003::throwError(in, text->f_interface);
                        return;
                    }
                    text->f_current_target = (SequenceLine*)f_parent->f_parent;
                    return;
                }
                case '{':
                {
                    SequenceScope* scope = new SequenceScope(this);
                    SequenceLine* line = new SequenceLine(scope);
                    f_elements.push_back(scope);
                    scope->f_contents.push_back(line);
                    text->f_current_target = line;
                    return;
                }
                case '}':
                {
                    if (f_parent->elementType() != ElementType::SCOPE){
                        LS003::throwError(in, text->f_interface);
                        return;
                    }
                    text->f_current_target = (SequenceLine*) f_parent->f_parent;
                    if (!text->f_current_target){
                        LS004::throwError(in, text->f_interface);
                        text->f_current_target = text->f_scope.f_contents.at(0);
                    }
                    return;
                }
                case '[':
                case ']':
                case '<':
                case '>':
                {
                    this->f_elements.push_back(in);
                }
            }
            return; //compiler reasons
        }
        case CharSequenceType::LIST_SEPARATOR:
        {
            switch(f_parent->elementType()){
                case ElementType::BRACKET:
                {
                    SequenceBracket* parent = ((SequenceBracket*)f_parent);
                    switch(parent->f_btype){
                        case BracketListType::ENDED_LINE_LIST:
                        {
                            LS002::throwError(in, text->f_interface);
                            return;
                        }
                        case BracketListType::SINGLE:
                        {
                            parent->f_btype = BracketListType::OPERN_LINE_LIST;
                            //continue at case OPEN_LINE_LIST
                        }
                        case BracketListType::OPERN_LINE_LIST:
                        {
                            this->f_elements.push_back(in);
                            SequenceLine* line = new SequenceLine(parent);
                            parent->f_contents.push_back(line);
                            text->f_current_target = line;
                            return;
                        }
                    }
                    return; //compiler reasons
                }
                case ElementType::SCOPE:
                {
                    SequenceScope* parent = ((SequenceScope*)f_parent);
                    switch(parent->f_stype){
                        case ScopeListType::SCOPE:
                        {
                            LS002::throwError(in, text->f_interface);
                            return;
                        }
                        case ScopeListType::SINGLE:
                        {
                            parent->f_stype = ScopeListType::INITIALIZER_LIST;
                            //continue at case INITIALIZER_LIST
                        }
                        case ScopeListType::INITIALIZER_LIST:
                        {
                            this->f_elements.push_back(in);
                            SequenceLine* line = new SequenceLine(parent);
                            parent->f_contents.push_back(line);
                            text->f_current_target = line;
                            return;
                        }
                    }
                    return; //compiler reasons
                }
            }
            return; //compiler reasons
        }
        default:
        {
            this->f_elements.push_back(in);
        }
    }
}
