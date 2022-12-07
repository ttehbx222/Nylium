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

    typedef std::vector<FieldDeclaration*> Parameters;

    struct FunctionDeclaration : public Namespace {
        Parameters* f_parameters;
        FunctionDeclaration(DeclarationAttributes* attributes, PendingDeclaration* return_type, std::string& name, Scope* scope, SequenceScope* text_code, Parameters* parameters);
        virtual void compile(Assembly*);
    };

    //Scope* buildFunctionDeclaration(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes, PendingDeclaration* return_type, std::string& name, Parameters* parameters);

}