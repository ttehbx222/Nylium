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
    struct ValueHolder;
    struct Scope;
    struct PendingDeclaration;

    struct DeclarationContainer{
        std::vector<Namespace*> f_namespace;
        FieldDeclaration* f_field = nullptr;
        std::vector<FunctionDeclaration*> f_functions;
    };

    struct DeclarationMap{
        Scope* f_scope;
        int resolve_flags = 0x0;
        std::map<std::string, DeclarationContainer*> declarations;
        Namespace* getNamespace(PendingDeclaration*);
        FieldDeclaration* getField(PendingDeclaration*);
        FunctionDeclaration* getFunction(PendingDeclaration*, std::vector<ValueHolder*>&);
        std::vector<Namespace*> getNamespaces(std::vector<std::string>);
        void resolveTypes();
        void resolveFields();
        void resolveFunctions();
        void resolveOperations();
        bool addDeclaration(Declaration*);
        inline DeclarationMap(Scope* scope){f_scope = scope;}
    };

}