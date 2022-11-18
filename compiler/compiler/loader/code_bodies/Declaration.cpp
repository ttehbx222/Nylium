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
#include "Declaration.hpp"

#include "../character_sequences/NyliumCharSequence.hpp"
#include "../load_iterations/0_CharSequences.hpp"
#include "compilable/Scope.hpp"

using namespace nylium;

Scope* fieldOrFunctionBodyMatcher(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes, std::string& pending, DeclarationBodyMatcher* matcher){
    CharSequence* seq = text->at((*read_pos)++);
    if (seq->type != CharSequenceType::NAME){
        //TODO unexpected char
        return fieldOrFunctionBodyMatcher(scope, text, read_pos, attributes, pending, matcher);
    }
    std::string name = seq->chars;
    seq = text->at((*read_pos)++);
    //no specifier brackets yet
    if (seq->type == CharSequenceType::BRACKET){
        if (seq->chars == "("){
            //continue to function declaration
        }
        //TODO unexpected char
        return fieldOrFunctionBodyMatcher(scope, text, read_pos, attributes, pending, matcher);
    }
    if (seq->type == CharSequenceType::END){
        //return field declaration
    }
    if (seq->type == CharSequenceType::OPERATOR){
        if (seq->chars == "="){
            //continue to AssignOperation declaration with FieldDeclaration target
        }
    }
    //TODO unexpected char
    return fieldOrFunctionBodyMatcher(scope, text, read_pos, attributes, pending, matcher);
}

Scope* DeclarationBodyMatcher::next(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes){
    CharSequence* seq = text->at((*read_pos)++);
    if (seq->type == CharSequenceType::END){
        //TODO unexpected abort of declaration
        return scope;
    }
    if (seq->type != CharSequenceType::NAME){
        //TODO unexpected char
        return this->next(scope, text, read_pos, attributes);
    }
    if (seq->chars == "namespace"){
        //continue to namespace declaration
    }
    if (seq->chars == "class"){
        attributes->f_dtype = DeclarationType::CLASS;
        //continue to TypeDeclaration
    }
    if (seq->chars == "struct"){
        attributes->f_dtype = DeclarationType::STRUCT;
        //continue to TypeDeclaration
    }
    /*if (seq->chars == "enum"){
        attributes->f_dtype = DeclarationType::ENUM;
        //continue to TypeDeclaration
    }*/
    if (seq->chars == "static"){
        if (attributes->f_static == Boolean::TRUE){
            //TODO error multi "static"
        }
        attributes->f_static = Boolean::TRUE;
        return this->next(scope, text, read_pos, attributes);
    }
    if (seq->chars == "final"){
        if (attributes->f_final == Boolean::TRUE){
            //TODO error multi "final"
        }
        attributes->f_final = Boolean::TRUE;
        return this->next(scope, text, read_pos, attributes);
    }
    if (seq->chars == "public"){
        if (attributes->f_visibility != Visibility::DEFAULT){
            //TODO error multi definition of visibility
        }
        attributes->f_visibility = Visibility::PUBLIC;
        return this->next(scope, text, read_pos, attributes);
    }
    if (seq->chars == "protected"){
        if (attributes->f_visibility != Visibility::DEFAULT){
            //TODO error multi definition of visibility
        }
        attributes->f_visibility = Visibility::PROTECTED;
        return this->next(scope, text, read_pos, attributes);
    }
    if (seq->chars == "private"){
        if (attributes->f_visibility != Visibility::DEFAULT){
            //TODO error multi definition of visibility
        }
        attributes->f_visibility = Visibility::PRIVATE;
        return this->next(scope, text, read_pos, attributes);
    }
    //non of the above true
    {
        return fieldOrFunctionBodyMatcher(scope, text, read_pos, attributes, seq->chars, this);
    }
}