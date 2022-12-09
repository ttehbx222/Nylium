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
#include "PendingDeclaration.hpp"
#include "../../../log/logger.hpp"

using namespace nylium;

PendingDeclaration::PendingDeclaration(DeclarationAttributes* attributes, std::string& label, PendingDeclaration* type, ValueHolderType vhtype) : Declaration(attributes, type, label, vhtype){
    
}

PendingDeclaration::PendingDeclaration(std::string& label, std::vector<std::string>& declaration_path) : Declaration(nullptr, nullptr, label, ValueHolderType::PENDING_DECLARATION){
    this->f_declaration_path = declaration_path;
}

void PendingDeclaration::debug_print(int depth){
    nlog::LOGLEVEL loglevel = nlog::LOGLEVEL::DEBUG_0;
    std::string out = "";
    for (int i = 0; i < depth; ++i){
        out += LOGGING_TABULATOR;
    }

    nlog::log(loglevel, out + this->f_key);
}