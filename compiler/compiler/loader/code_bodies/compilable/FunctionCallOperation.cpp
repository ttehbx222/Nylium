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
#include "FunctionCallOperation.hpp"
#include "../../../../log/logger.hpp"

using namespace nylium;

FunctionCallOperation::FunctionCallOperation(ValueHolder* target, std::string& label, std::vector<ValueHolder*>& arguments, Scope* container, bool f_static) : CallOperation(target, f_static, label, container, OperationType::FUNCTION){
    f_arguments = arguments;
}

void FunctionCallOperation::compile(Assembly* assembly){
    
}

void FunctionCallOperation::resolve(){
    
}

void FunctionCallOperation::debug_print(int depth){
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
    nlog::log(loglevel, out + LOGGING_TABULATOR + LOGGING_TABULATOR + "(");

    for (ValueHolder* argument : f_arguments){
        argument->debug_print(depth+3);
    }

    nlog::log(loglevel, out + LOGGING_TABULATOR + LOGGING_TABULATOR + "(");
}