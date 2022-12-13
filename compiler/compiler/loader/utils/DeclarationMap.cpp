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

bool DeclarationMap::addDeclaration(Declaration* decl){ //TODO not add to interface if in function
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
            this->f_scope->f_parent_interface->f_accessibles.addField((FieldDeclaration*)decl);
            break;
        }
        case ValueHolderType::FUNCTION:
        {
            FunctionDeclaration* funcDecl = (FunctionDeclaration*)decl;
            declarationContainer->second->f_functions.push_back(funcDecl);
            this->f_scope->f_parent_interface->f_accessibles.addFunction((FunctionDeclaration*)decl);
            break;
        }
        case ValueHolderType::NAMESPACE:
        {
            if ((!declarationContainer->second->f_namespace.empty()) && declarationContainer->second->f_namespace.front()->f_vhtype == ValueHolderType::TYPE){
                //error
                return false;
            }
            declarationContainer->second->f_namespace.push_back((Namespace*)decl);
            break;
        }
        case ValueHolderType::TYPE:
        {
            if (!declarationContainer->second->f_namespace.empty()){
                //error
                return false;
            }
            declarationContainer->second->f_namespace.push_back((Namespace*)decl);
            this->f_scope->f_parent_interface->f_accessibles.addType((TypeDeclaration*)decl);
            break;
        }
    }
    return true;
}

/*FieldDeclaration* DeclarationMap::getField(PendingDeclaration* name){
    if (name->f_declaration_path.empty()){
        auto container = declarations.find(name->f_key);
        if (container == declarations.end() || !container->second->f_field){
            Scope* parent = f_scope->f_parent;
            if (!parent){
                //TODO other files
                return nullptr;
            }
            if (f_scope->f_ctype == CompilableType::DECLARATION){
                FieldDeclaration* result = parent->f_accessibles.getField(name);
                return result ? result : parent->f_accessibles.getField(new PendingDeclaration(name->f_key, std::vector<std::string>({((Namespace*)f_scope)->f_key}));
            }else{
                return parent->f_accessibles.getField(name);
            }
        }
        return container->second->f_field;
    }else{
        std::vector<Namespace*> namespaces = getNamespaces(name->f_declaration_path);
        for (Namespace* _namespace : namespaces){
            FieldDeclaration* result = _namespace->f_accessibles.getField(new PendingDeclaration(name->f_key));
            if (result){
                return result;
            }
        }

        Scope* parent = f_scope->f_parent;
        if (!parent){
            //TODO other files
            return nullptr;
        }
        if (f_scope->f_ctype == CompilableType::DECLARATION){
            FieldDeclaration* result = parent->f_accessibles.getField(name);
            if (result){
                return result;
            }
            std::vector<std::string> addition = name->f_declaration_path;
            addition.push_back(((Namespace*)f_scope)->f_key);
            return parent->f_accessibles.getField(new PendingDeclaration(name->f_key, addition));
        }else{
            return parent->f_accessibles.getField(name);
        }
    }
}

Namespace* DeclarationMap::getNamespace(PendingDeclaration* name){
    if (name->f_declaration_path.empty()){
        auto container = declarations.find(name->f_key);
        if (container == declarations.end() || container->second->f_namespace.empty()){
            Scope* parent = f_scope->f_parent;
            if (!parent){
                //TODO other file
                return nullptr;
            }
            if (f_scope->f_ctype == CompilableType::DECLARATION){
                Namespace* result = parent->f_accessibles.getNamespace(name);
                return result ? result : parent->f_accessibles.getNamespace(new PendingDeclaration(name->f_key, std::vector<std::string>({((Namespace*)f_scope)->f_key}));
            }else{
                return parent->f_accessibles.getNamespace(name);
            }
        }
        if (container->second->f_namespace.size() > 1){
            //error
            return nullptr;
        }
        return container->second->f_namespace.front();
    }else{
        std::vector<Namespace*> namespaces = getNamespaces(name->f_declaration_path);
        for (Namespace* _namespace : namespaces){
            Namespace* result = _namespace->f_accessibles.getNamespace(new PendingDeclaration(name->f_key));
            if (result){
                return result;
            }
        }

        Scope* parent = f_scope->f_parent;
        if (!parent){
            //TODO other files
            return nullptr;
        }
        if (f_scope->f_ctype == CompilableType::DECLARATION){
            Namespace* result = parent->f_accessibles.getNamespace(name);
            if (result){
                return result;
            }
            std::vector<std::string> addition = name->f_declaration_path;
            addition.push_back(((Namespace*)f_scope)->f_key);
            return parent->f_accessibles.getNamespace(new PendingDeclaration(name->f_key, addition));
        }else{
            return parent->f_accessibles.getNamespace(name);
        }
    }
}

FunctionDeclaration* DeclarationMap::getFunction(PendingDeclaration* name, std::vector<ValueHolder*>& arguments){
    if (name->f_declaration_path.empty()){
        auto container = declarations.find(name->f_key);
        if (container == declarations.end() || container->second->f_namespace.empty()){
            Scope* parent = f_scope->f_parent;
            if (!parent){
                //TODO other file
                return nullptr;
            }
            if (f_scope->f_ctype == CompilableType::DECLARATION){
                Namespace* result = parent->f_accessibles.getNamespace(name);
                return result ? result : parent->f_accessibles.getNamespace(new PendingDeclaration(name->f_key, std::vector<std::string>({((Namespace*)f_scope)->f_key}));
            }else{
                return parent->f_accessibles.getNamespace(name);
            }
        }
        if (container->second->f_namespace.size() > 1){
            //error
            return nullptr;
        }
        return container->second->f_namespace.front();
    }else{
        std::vector<Namespace*> namespaces = getNamespaces(name->f_declaration_path);
        for (Namespace* _namespace : namespaces){
            Namespace* result = _namespace->f_accessibles.getNamespace(new PendingDeclaration(name->f_key));
            if (result){
                return result;
            }
        }

        Scope* parent = f_scope->f_parent;
        if (!parent){
            //TODO other files
            return nullptr;
        }
        if (f_scope->f_ctype == CompilableType::DECLARATION){
            Namespace* result = parent->f_accessibles.getNamespace(name);
            if (result){
                return result;
            }
            std::vector<std::string> addition = name->f_declaration_path;
            addition.push_back(((Namespace*)f_scope)->f_key);
            return parent->f_accessibles.getNamespace(new PendingDeclaration(name->f_key, addition));
        }else{
            return parent->f_accessibles.getNamespace(name);
        }
    }
}

std::vector<Namespace*> DeclarationMap::getNamespaces(std::vector<std::string> path){
    
}*/

void DeclarationMap::resolveTypes(){
    if (resolve_flags & TYPES_RESOLVE){
        return;
    }
    //TODO
    resolve_flags |= TYPES_RESOLVE;
}

TypeDeclaration* DeclarationMap::getType(PendingDeclaration* decl){
    return f_scope->f_parent_interface->f_accessibles.getType(f_scope, decl);
}
FieldDeclaration* DeclarationMap::getField(PendingDeclaration* decl){ //TODO order of declaration & execution
    if (decl->f_declaration_path.empty()){
        Scope* current = f_scope;
        while (current->f_layer == SCOPE_LAYER::FUNCTION){
            auto container = current->f_accessibles.declarations.find(decl->f_key);
            if (container == current->f_accessibles.declarations.end() || !container->second->f_field){
                continue;
            }
            return container->second->f_field;
        }
    }
    return f_scope->f_parent_interface->f_accessibles.getField(f_scope, decl);
}
FunctionDeclaration* DeclarationMap::getFunction(PendingDeclaration* decl, std::vector<ValueHolder*>& param_types){
    return f_scope->f_parent_interface->f_accessibles.getFunction(f_scope, decl, param_types);
}

TypeDeclaration* DeclarationLinking::getType(Scope* source, PendingDeclaration* decl, bool other_files){
    
    auto find_declaration = f_classes.find(decl->f_key);
    if (find_declaration != f_classes.end()){
        while (source->f_ctype != CompilableType::DECLARATION){
            source = source->f_parent;
            if (!source)
            {
                break;
            }
        }
        std::vector<std::string> local_path = source ? ((Namespace*)source)->f_declaration_path : std::vector<std::string>();
        if (source){
            local_path.push_back(((Namespace*)source)->f_key);
        }
        std::vector<std::string>& referenced_path = decl->f_declaration_path;
        std::vector<TypeDeclaration*>& types = find_declaration->second;

        bool ambiguous = false;
        TypeDeclaration* last_match = nullptr;
        int last_match_strength = -1;

        for (size_t i = types.size() - 1; i >= 0; --i){
            TypeDeclaration* type = types.at(i);
            if (type->f_declaration_path.size() < last_match_strength){ //only works because the code is iterated one depth at a time
                break;
            }
            size_t j = decl->f_declaration_path.size() - 1;
            long long dif = type->f_declaration_path.size() - 1 - j;
            if (dif < 0){
                break;
            }
            bool match = true;
            while (match && j >= 0){
                match = decl->f_declaration_path.at(j) == type->f_declaration_path.at(dif+j);
                --j;
            }
            if (!match){
                continue;
            }
            for(j = 0; match && j < dif; ++j){
                match = local_path.at(j) == type->f_declaration_path.at(j);
            }
            if (!match){
                continue;
            }
            if (last_match_strength < dif){
                //TODO
            }
            if (last_match_strength == dif){
                //ambiguous
            }
        }


    }

}
FieldDeclaration* DeclarationLinking::getField(Scope* source, PendingDeclaration*){

}
FunctionDeclaration* DeclarationLinking::getFunction(Scope* source, PendingDeclaration*, std::vector<ValueHolder*>&){

}
bool DeclarationLinking::addField(FieldDeclaration* decl){

}
bool DeclarationLinking::addFunction(FunctionDeclaration* decl){

}
bool DeclarationLinking::addType(TypeDeclaration* decl){

}