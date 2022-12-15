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
#include "Scope.hpp"
#include "../../../../log/logger.hpp"

#include "FieldDeclaration.hpp"
#include "TypeDeclaration.hpp"
#include "FunctionDeclaration.hpp"

using namespace nylium;

Scope::Scope(Scope* scope, SequenceScope* seqScope, CompilableType ctype) : CompilableBody(ctype, scope){
    this->f_layer = scope->f_layer;
    this->f_parent = scope;
    this->f_text_code = seqScope;
    this->f_parent_interface = scope->f_parent_interface;
    this->f_depth = scope->f_depth+1;
}

Scope::Scope(FileInterface* fInterface) : CompilableBody(CompilableType::SCOPE, nullptr){
    this->f_parent_interface = fInterface;
    this->f_text_code = &(fInterface->f_text->f_scope);
}

void Scope::compile(Assembly* assembly){
    //TODO
}

void Scope::resolve(){
    resolveScope();
}

void Scope::resolveScope(){
    for (CompilableBody* body : this->f_code){
        body->resolve();
    }
}

void Scope::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_2;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }
    nlog::log(loglevel, out + "{");

    std::vector<CompilableBody*> bodies;

    if (f_layer == SCOPE_LAYER::FUNCTION){
        std::vector<CompilableBody*> sorted_fields;
        for (auto container : f_accessibles.declarations){
            for (size_t i = 0; i < sorted_fields.size(); ++i){
                CompilableBody* body = sorted_fields.at(i);
                if (container.second->f_field->f_orderIndex > body->f_orderIndex){
                    sorted_fields.insert(sorted_fields.begin() + i + 1, container.second->f_field);
                    goto exit_field_sort;
                }
            }
            sorted_fields.push_back(container.second->f_field);
        }
        exit_field_sort:
        const size_t max_operation_index = this->f_code.size();
        size_t operation_index = 0;
        const size_t max_declaration_index = sorted_fields.size();
        size_t declaration_index = 0;
        while (operation_index < max_operation_index || declaration_index < max_declaration_index){
            if (operation_index >= max_operation_index){
                bodies.push_back(sorted_fields.at(declaration_index++));
                continue; //TODO shortcut
            }
            if (declaration_index >= max_declaration_index){
                bodies.push_back(this->f_code.at(operation_index++));
                continue; //TODO shortcut
            }
            CompilableBody* operation = this->f_code.at(operation_index);
            CompilableBody* declaration = sorted_fields.at(declaration_index);
            if (operation->f_orderIndex > declaration->f_orderIndex){
                bodies.push_back(declaration);
                declaration_index++;
            }else{
                bodies.push_back(operation);
                operation_index++;
            }
        }
    }else{
        for (auto container : f_accessibles.declarations){
            if (container.second->f_field){
                bodies.push_back(container.second->f_field);
            }
        }
        for (auto container : f_accessibles.declarations){
            if (container.second->f_namespace){
                bodies.push_back((Scope*)container.second->f_namespace);
            }
        }
        for (auto container : f_accessibles.declarations){
            for (FunctionDeclaration* function : container.second->f_functions){
                bodies.push_back((Scope*)function);
            }
        }
    }

    for (CompilableBody* body : bodies){
        body->debug_print(depth+1);
    }

    nlog::log(loglevel, out + "}");
}