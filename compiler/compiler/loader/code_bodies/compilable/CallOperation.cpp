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
#include "CallOperation.hpp"
#include "TypeDeclaration.hpp"
#include "FieldDeclaration.hpp"
#include "../../../../log/logger.hpp"

using namespace nylium;

CallOperation::CallOperation(ValueHolder* target, bool f_static, std::string& key, Scope* container, OperationType otype) : Operation(nullptr, target, otype, container) {
    this->f_static = f_static;
    this->f_key = key;
}

void CallOperation::compile(Assembly* assembly){
    //TODO
}

void CallOperation::resolve(){
    if (f_target->f_vhtype == ValueHolderType::PENDING_DECLARATION){
        f_target = f_container->f_accessibles.getField((PendingDeclaration*)f_target);
    }else{
        f_target->resolve();
    }
    if (!f_target){
        //error
    }
    if (f_static){
        //error
    }
    TypeDeclaration* type = (TypeDeclaration*)f_target->f_type;
    auto container = type->f_accessibles.declarations.find(f_key);
    if (container == type->f_accessibles.declarations.end()){
        //error
        return;
    }
    if (!container->second->f_field){
        //error
        return;
    }
    f_result = container->second->f_field;
    f_type = f_result->f_type;
}

void CallOperation::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_2;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }
    f_target->debug_print(depth);
    if (f_static){
        nlog::log(loglevel, out + LOGGING_TABULATOR + "::" + f_key);
    }else{
        nlog::log(loglevel, out + LOGGING_TABULATOR + "." + f_key);
    }
}