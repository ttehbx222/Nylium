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
#include "NamespaceDeclaration.hpp"
#include "../../../../log/logger.hpp"
#include "FieldDeclaration.hpp"

using namespace nylium;

Namespace::Namespace(DeclarationAttributes* attributes, std::string& name, Scope* scope, SequenceScope* text_code, PendingDeclaration* type, ValueHolderType vhtype) : Scope(scope, text_code, CompilableType::DECLARATION), PendingDeclaration(attributes, name, type, vhtype){
    if (attributes->f_dtype == DeclarationType::NAMESPACE){
    }
}

void Namespace::compile(Assembly* assembly){
    //TODO
}

void Namespace::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_0;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }
    nlog::log(loglevel, out + "namespace " + this->f_key);
    nlog::log(loglevel, out + LOGGING_TABULATOR + "{");

    std::vector<CompilableBody*> bodies;

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

    for (CompilableBody* body : bodies){
        body->debug_print(depth+2);
    }

    nlog::log(loglevel, out + LOGGING_TABULATOR + "}");
}