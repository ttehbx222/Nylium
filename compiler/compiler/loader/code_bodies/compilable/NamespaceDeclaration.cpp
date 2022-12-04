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

using namespace nylium;

Namespace::Namespace(std::string& name, SequenceScope* text_code, DeclarationAttributes* attributes, Scope* scope) : Scope(scope, text_code) {
    this->f_attributes = attributes;
    this->f_key = name;
    if (attributes->f_dtype == DeclarationType::NAMESPACE){
        nlog::log(nlog::LOGLEVEL::DEBUG_0, std::string("namespace ") + name);
    }
}