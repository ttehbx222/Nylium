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
#include "FieldDeclaration.hpp"
#include "TypeDeclaration.hpp"
#include "../../../../log/logger.hpp"

using namespace nylium;

FieldDeclaration::FieldDeclaration(DeclarationAttributes* attributes, PendingDeclaration* type, std::string& label, Scope* container, AssignOperation* initializer) : PendingDeclaration(attributes, label, container, type, ValueHolderType::FIELD){
    this->f_initializer = initializer;

    if (attributes->f_final == Boolean::DEFAULT){
        attributes->f_final == Boolean::FALSE;
    }
    if (attributes->f_static == Boolean::DEFAULT){
        attributes->f_static = container->f_layer == SCOPE_LAYER::MAIN ? Boolean::TRUE : Boolean::FALSE;
    }
    if (attributes->f_visibility == Visibility::DEFAULT){
        attributes->f_visibility = container->f_layer == SCOPE_LAYER::MAIN ? Visibility::PROTECTED : Visibility::PRIVATE;
    }
}

void FieldDeclaration::compile(Assembly* assembly){
    //TODO
}

void FieldDeclaration::resolve(){
    f_type = f_container->f_accessibles.getType(f_type);
    if (!f_type){
        //error
    }
    if (f_initializer){
        f_initializer->resolve();
    }
}

void FieldDeclaration::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_0;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }
    nlog::log(loglevel, out + "field " + this->f_type->f_key + " " + this->f_key);
    if (this->f_initializer){
        nlog::log(nlog::LOGLEVEL::DEBUG_2, out + LOGGING_TABULATOR + "=");
        f_initializer->f_source->debug_print(depth+2);
    }
}