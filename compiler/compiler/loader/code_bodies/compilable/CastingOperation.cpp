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
#include "CastingOperation.hpp"
#include "TypeDeclaration.hpp"
#include "FieldDeclaration.hpp"
#include "../PendingDeclaration.hpp"
#include "../../../../log/logger.hpp"

using namespace nylium;

CastingOperation::CastingOperation(ValueHolder* target, PendingDeclaration* target_type, Scope* container) : Operation(target_type, target, OperationType::CAST, container){
    
}

void CastingOperation::compile(Assembly* assembly){
    if (f_target->f_vhtype == ValueHolderType::PENDING_DECLARATION){
        f_target = f_container->f_accessibles.getField((PendingDeclaration*)f_target);
    }else{
        f_target->resolve();
    }
    if (!f_target){
        //error
    }
    f_type = f_container->f_accessibles.getType(f_type);
    if (!f_type){
        //error
    }
}

void CastingOperation::resolve(){

}

void CastingOperation::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_2;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }
    f_target->debug_print(depth);
    nlog::log(loglevel, out + LOGGING_TABULATOR + "cast");
    f_type->debug_print(depth+2);
}