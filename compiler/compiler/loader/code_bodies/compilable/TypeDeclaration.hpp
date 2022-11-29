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
#pragma once
#include "NamespaceDeclaration.hpp"
#include "../../../../log/logger.hpp"

namespace nylium{

    struct TypeDeclaration : public Namespace {
        TypeDeclaration(std::string& name, SequenceScope* text_code, DeclarationAttributes* attributes, Scope* scope) : Namespace(name, text_code, attributes, scope) {
            //TODO add default ValueHolder#type convert to Type
            this->f_layer = SCOPE_LAYER::CLASS;

            if (attributes->f_dtype == DeclarationType::CLASS){
                nlog::log(nlog::LOGLEVEL::DEBUG_0, std::string("class ") + name);
            }
            if (attributes->f_dtype == DeclarationType::STRUCT){
                nlog::log(nlog::LOGLEVEL::DEBUG_0, std::string("struct ") + name);
            }
            if (attributes->f_dtype == DeclarationType::ENUM){
                nlog::log(nlog::LOGLEVEL::DEBUG_0, std::string("enum ") + name);
            }
        }
    };

}