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
#include "ForKeyword.hpp"
#include "../../../../log/logger.hpp"
#include "../../code_bodies/compilable/FieldDeclaration.hpp"

using namespace nylium;

void ForKeyword::compile(Assembly* assembly){
    //TODO
}

void ForKeyword::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_2;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }
    nlog::log(loglevel, out + "for");
    nlog::log(loglevel, out + LOGGING_TABULATOR + "(");
    this->f_init->debug_print(depth+2);
    this->f_condition->debug_print(depth+2);
    this->f_iteration->debug_print(depth+2);
    nlog::log(loglevel, out + LOGGING_TABULATOR + ")");
    if (nlog::lowestRelevantLogLevel() < nlog::LOGLEVEL::DEBUG_2){
        return;
    }
    nlog::log(loglevel, out + LOGGING_TABULATOR + "{");

    std::vector<CompilableBody*> bodies;
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

    for (CompilableBody* body : bodies){
        body->debug_print(depth+2);
    }

    nlog::log(loglevel, out + LOGGING_TABULATOR + "}");
}