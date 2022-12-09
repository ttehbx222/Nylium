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
#include <string>
#include <vector>
#include <map>

namespace nylium{

    struct Namespace;
    struct FunctionDeclaration;
    struct FieldDeclaration;
    struct TypeDeclaration;
    struct Declaration;

    struct DeclarationContainer{
        Namespace* f_namespace = nullptr;
        FieldDeclaration* f_field = nullptr;
        std::vector<FunctionDeclaration*> f_functions;
    };

    struct DeclarationMap{
        bool resolved;
        std::map<std::string, DeclarationContainer*> declarations;
        Namespace* getNamespace(std::string&);
        FieldDeclaration* getField(std::string&);
        FunctionDeclaration* getFunction(std::string&, std::vector<ValueHolder*>&);
        void resolveDeclarations();
        bool addDeclaration(Declaration*);
    };

}