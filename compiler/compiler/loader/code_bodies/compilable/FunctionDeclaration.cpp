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
#include "FunctionDeclaration.hpp"

#include "../../load_iterations/0_CharSequences.hpp"

#include "../../../error_handling/errors/CB001.hpp"
#include "../../../error_handling/errors/CB004.hpp"
#include "../../../../log/logger.hpp"

using namespace nylium;

/*Scope* buildParameter(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes, PendingDeclaration* return_type, std::string& name, Parameters* parameters, PendingDeclaration* param_type){
    CharSequence* seq = text->read(read_pos);
    if (seq->type == CharSequenceType::END){
        CB004::throwError(seq, scope->f_parent_interface);
        return scope;
    }
    if (seq->type != CharSequenceType::NAME){
        CB001::throwError(seq, scope->f_parent_interface);
    }
    parameters->push_back(new FieldDeclaration(param_type, seq->chars));
    seq = text->read(read_pos);
    if (seq->type == CharSequenceType::END){
        CB004::throwError(seq, scope->f_parent_interface);
        return scope;
    }
    if (seq->type == CharSequenceType::BRACKET){
        if (seq->chars == ")"){
            seq = text->read(read_pos);
            if (seq->type == CharSequenceType::END){
                CB004::throwError(seq, scope->f_parent_interface);
                return scope;
            }
            if (seq->type == CharSequenceType::BRACKET){
                if (seq->chars == "{"){
                    FunctionDeclaration* function_decl = new FunctionDeclaration(scope, attributes, return_type, name, parameters);
                    return function_decl;
                }
            }
        }
        CB001::throwError(seq, scope->f_parent_interface);
        return buildParameter(scope, text, read_pos, attributes, return_type, name, parameters, param_type);
    }
    
    if (seq->type == CharSequenceType::LIST_SEPARATOR){
        seq = text->read(read_pos);
        if (seq->type == CharSequenceType::END){
            CB004::throwError(seq, scope->f_parent_interface);
            return scope;
        }
        if (seq->type == CharSequenceType::NAME){
            return buildParameter(scope, text, read_pos, attributes, return_type, name, parameters, new PendingDeclaration(seq->chars));
        }
    }
    CB001::throwError(seq, scope->f_parent_interface);
    return buildParameter(scope, text, read_pos, attributes, return_type, name, parameters, param_type);
}

Scope* buildFunction(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes, PendingDeclaration* return_type, std::string& name, Parameters* parameters){
    CharSequence* seq = text->read(read_pos);
    if (seq->type == CharSequenceType::END){
        CB004::throwError(seq, scope->f_parent_interface);
        return scope;
    }
    if (seq->type == CharSequenceType::BRACKET){
        if (seq->chars == ")"){
            seq = text->read(read_pos);
            if (seq->type == CharSequenceType::END){
                CB004::throwError(seq, scope->f_parent_interface);
                return scope;
            }
            if (seq->type == CharSequenceType::BRACKET){
                if (seq->chars == "{"){
                    FunctionDeclaration* function_decl = new FunctionDeclaration(scope, attributes, return_type, name, parameters);
                    return function_decl;
                }
            }
        }
        CB001::throwError(seq, scope->f_parent_interface);
        return buildFunction(scope, text, read_pos, attributes, return_type, name, parameters);
    }
    if (seq->type == CharSequenceType::NAME){
        return buildParameter(scope, text, read_pos, attributes, return_type, name, parameters, new PendingDeclaration(seq->chars));
    }
    CB001::throwError(seq, scope->f_parent_interface);
    return buildFunction(scope, text, read_pos, attributes, return_type, name, parameters);
}

Scope* nylium::buildFunctionDeclaration(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes, PendingDeclaration* return_type, std::string& name, Parameters* parameters){
    {
        if (attributes->f_visibility == Visibility::DEFAULT){
            attributes->f_visibility = Visibility::PROTECTED;
        }
        if (attributes->f_static == Boolean::DEFAULT){
            if (scope->f_layer == SCOPE_LAYER::MAIN){
                attributes->f_static = Boolean::TRUE;
            }else{
                attributes->f_static = Boolean::FALSE;
            }
        }
        if (attributes->f_final == Boolean::DEFAULT){
            attributes->f_final = Boolean::FALSE;
        }
    }
    return buildFunction(scope, text, read_pos, attributes, return_type, name, parameters);
}

FunctionDeclaration::FunctionDeclaration(Scope* scope, DeclarationAttributes* attributes, PendingDeclaration* return_type, std::string& name, Parameters* parameters){
    f_parent = scope;
    f_attributes = attributes;
    f_parameters = parameters;
    f_type = return_type;
    f_key = name;
    f_layer = SCOPE_LAYER::FUNCTION;
    f_parent_interface = scope->f_parent_interface;

    if (nlog::lowestRelevantLogLevel() >= nlog::LOGLEVEL::DEBUG_0){
        std::string message = "function ";
        message += return_type->f_key + " " + name + "(";
        if (!parameters->empty()){
            FieldDeclaration* field = parameters->at(0);
            message += field->f_type->f_key + " " + field->f_key;
            for (size_t i = 1; i < parameters->size(); i++){
                field = parameters->at(i);
                message += ", " + field->f_type->f_key + " " + field->f_key;
            }
        }
        message += ")";
        nlog::log(nlog::LOGLEVEL::DEBUG_0, message);
    }
}*/