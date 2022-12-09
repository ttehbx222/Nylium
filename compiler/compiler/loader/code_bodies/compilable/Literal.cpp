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
#include "Literal.hpp"
#include "../../../../log/logger.hpp"

using namespace nylium;

Literal::Literal(PendingDeclaration* type, void* data, size_t size, std::string& chars) : ValueHolder(ValueHolderType::LITERAL, type, CompilableType::LITERAL){
    this->f_data = data;
    this->f_size = size;
    this->f_chars = chars;
}

void Literal::compile(Assembly* assembly){
    //TODO
}

void Literal::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_0;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }
    nlog::log(loglevel, out + "literal " + f_chars);
}