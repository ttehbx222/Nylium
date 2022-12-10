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
#include "DeclarationMap.hpp"
#include "../code_bodies/compilable/TypeDeclaration.hpp"
#include "../code_bodies/compilable/FieldDeclaration.hpp"
#include "../code_bodies/compilable/FunctionDeclaration.hpp"

using namespace nylium;

constexpr int TYPES_RESOLVE = 0x1;
constexpr int FIELDS_RESOLVE = 0x2;
constexpr int FUNCTIONS_RESOLVE = 0x4;
constexpr int OPERATIONS_RESOLVE = 0x8;

bool DeclarationMap::addDeclaration(Declaration* decl){
    auto declarationContainer = declarations.find(decl->f_key);
    if (declarationContainer == declarations.end()){
        declarations.insert({decl->f_key, new DeclarationContainer()});
        declarationContainer = declarations.find(decl->f_key);
    }
    switch(decl->f_vhtype){
        case ValueHolderType::FIELD:
        {
            if (declarationContainer->second->f_field){
                //error
                return false;
            }
            declarationContainer->second->f_field = (FieldDeclaration*)decl;
            break;
        }
        case ValueHolderType::FUNCTION:
        {
            FunctionDeclaration* funcDecl = (FunctionDeclaration*)decl;
            declarationContainer->second->f_functions.push_back(funcDecl);
            break;
        }
        case ValueHolderType::NAMESPACE:
        case ValueHolderType::TYPE:
        {
            if (declarationContainer->second->f_namespace){
                //error
                return false;
            }
            declarationContainer->second->f_namespace = (Namespace*)decl;
            break;
        }
    }
    return true;
}

FieldDeclaration* DeclarationMap::getField(PendingDeclaration* name){
    auto declarationContainer = declarations.find(name);
    if (declarationContainer == declarations.end()){
        //error
        return nullptr;
    }
    return declarationContainer->second->f_field;
}

Namespace* DeclarationMap::getNamespace(PendingDeclaration* name, bool locked){
    //TODO
    return result;
}

FunctionDeclaration* DeclarationMap::getFunction(PendingDeclaration* name, std::vector<ValueHolder*>& arguments){
    if (!(this->resolve_flags & FUNCTIONS_RESOLVE)){
        //error
        return nullptr;
    }
    auto declarationContainer = declarations.find(name);
    if (declarationContainer == declarations.end()){
        //error
        return nullptr;
    }
    for (FunctionDeclaration* allFunc : declarationContainer->second->f_functions){
        if (allFunc->f_parameters.size() != arguments.size()){
            continue;
        }
        bool match = true;
        for (size_t i = 0; i < arguments.size(); ++i){
            if (((TypeDeclaration*)arguments.at(i)->f_type)->conversionTo((TypeDeclaration*)allFunc->f_parameters.at(i)->f_type) != Castable::DIRECT){
                match = false;
                break;
            }
        }
        if (match){
            return allFunc;
        }
    }
    return nullptr;
}

void DeclarationMap::resolveTypes(){
    if (resolve_flags & TYPES_RESOLVE){
        return;
    }
    //TODO
    resolve_flags |= TYPES_RESOLVE;
}