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

#include <vector>
#include "NamespaceDeclaration.hpp"
#include "FieldDeclaration.hpp"

namespace nylium{

    struct FunctionDeclaration : public Namespace {
        std::vector<FieldDeclaration*> f_parameters; //TODO add return value
        FunctionDeclaration(DeclarationAttributes* attributes, PendingDeclaration* return_type, std::string& name, Scope* scope, SequenceScope* text_code, std::vector<FieldDeclaration*>& parameters);
        virtual void compile(Assembly*);
        void debug_print(int depth);
        void resolve();
    };

}