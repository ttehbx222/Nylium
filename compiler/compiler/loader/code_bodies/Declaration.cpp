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
#include "compilable/FunctionDeclaration.hpp"

#include "../../error_handling/errors/CB001.hpp"
#include "../../error_handling/errors/CB002.hpp"
#include "../../error_handling/errors/CB003.hpp"
#include "../../error_handling/errors/CB004.hpp"

using namespace nylium;

Scope* buildFDeclaration(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes, std::string& pending){ //Field or Function declaration
    CharSequence* seq = text->read(read_pos);
    if (seq->type == CharSequenceType::END){
        CB004::throwError(seq, scope->f_parent_interface);
        return scope;
    }
    if (seq->type != CharSequenceType::NAME){
        CB001::throwError(seq, scope->f_parent_interface);
        return buildFDeclaration(scope, text, read_pos, attributes, pending);
    }
    std::string name = seq->chars;
    seq = text->read(read_pos);
    //no specifier brackets yet
    if (seq->type == CharSequenceType::BRACKET){
        if (seq->chars == "("){
            attributes->f_dtype = DeclarationType::FUNCTION;
            return nylium::buildFunctionDeclaration(scope, text, read_pos, attributes, new PendingDeclaration(pending), name, new Parameters());
        }
        CB001::throwError(seq, scope->f_parent_interface);
        return buildFDeclaration(scope, text, read_pos, attributes, pending);
    }
    if (seq->type == CharSequenceType::END){
        //return field declaration
    }
    if (seq->type == CharSequenceType::OPERATOR){
        if (seq->chars == "="){
            //continue to FieldDeclaration with init value
        }
    }
    CB001::throwError(seq, scope->f_parent_interface);
    return buildFDeclaration(scope, text, read_pos, attributes, pending);
}

Scope* nylium::buildDeclaration(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes){
    CharSequence* seq = text->read(read_pos);
    if (seq->type == CharSequenceType::END){
        CB004::throwError(seq, scope->f_parent_interface);
        return scope;
    }
    if (seq->type != CharSequenceType::NAME){
        CB001::throwError(seq, scope->f_parent_interface);
        return buildDeclaration(scope, text, read_pos, attributes);
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
            CB002::throwError(seq, scope->f_parent_interface);
        }
        attributes->f_static = Boolean::TRUE;
        return buildDeclaration(scope, text, read_pos, attributes);
    }
    if (seq->chars == "final"){
        if (attributes->f_final == Boolean::TRUE){
            CB002::throwError(seq, scope->f_parent_interface);
        }
        attributes->f_final = Boolean::TRUE;
        return buildDeclaration(scope, text, read_pos, attributes);
    }
    if (seq->chars == "public"){
        if (attributes->f_visibility != Visibility::DEFAULT){
            CB003::throwError(seq, scope->f_parent_interface);
        }
        attributes->f_visibility = Visibility::PUBLIC;
        return buildDeclaration(scope, text, read_pos, attributes);
    }
    if (seq->chars == "protected"){
        if (attributes->f_visibility != Visibility::DEFAULT){
            CB003::throwError(seq, scope->f_parent_interface);
        }
        attributes->f_visibility = Visibility::PROTECTED;
        return buildDeclaration(scope, text, read_pos, attributes);
    }
    if (seq->chars == "private"){
        if (attributes->f_visibility != Visibility::DEFAULT){
            CB003::throwError(seq, scope->f_parent_interface);
        }
        attributes->f_visibility = Visibility::PRIVATE;
        return buildDeclaration(scope, text, read_pos, attributes);
    }
    //non of the above true
    {
        return buildFDeclaration(scope, text, read_pos, attributes, seq->chars);
    }
}