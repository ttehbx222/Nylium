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
#include "1_CodeBodies.hpp"

#include "../code_bodies/compilable/Scope.hpp"
#include "../character_sequences/NyliumCharSequence.hpp"
#include "0_CharSequences.hpp"

#include "../../../log/logger.hpp"

using namespace nylium;

struct BodyMatcher{
    virtual Scope* next(Scope* scope, Text* text, size_t* read_pos) = 0;
};

struct MainBodyMatcher : public BodyMatcher {
    SCOPE next(SCOPE scope, Text* text, size_t* read_pos){
        return nullptr;
    }
};

struct FunctionBodyMatcher : public BodyMatcher {
    SCOPE next(SCOPE scope, Text* text, size_t* read_pos){
        return nullptr;
    }
};

MainBodyMatcher* mainBM = new MainBodyMatcher();
FunctionBodyMatcher* funcBM = new FunctionBodyMatcher();

BodyMatcher* bodyMatcherByLevel(SCOPE_LAYER layer){
    switch(layer){
        case SCOPE_LAYER::MAIN: 
        case SCOPE_LAYER::CLASS:
            return mainBM;
        case SCOPE_LAYER::FUNCTION:
            return funcBM;
    }
    return mainBM;
}

namespace builder{
    Scope* buildMainScope(Scope* scope, Text* text);
    namespace declaration{
        Scope* buildDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos);
    }
}

void nylium::loadBodies(FileInterface* fInterface){
    nlog::log(nlog::LOGLEVEL::INFO, fInterface->name + ".nylium");
    Text* text = fInterface->f_text;

    text->f_current_target = text->f_scope.f_contents.front();
    fInterface->main_scope->text_code = &(text->f_scope);
    //TODO
}

namespace builder{

    Scope* buildMainScope(Scope* scope, Text* text){
        size_t read_pos = 0;
        return declaration::buildDeclaration(scope, text, new DeclarationAttributes(), &read_pos);
    }

    namespace declaration{

        Scope* declaration::buildDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos){
            Element* element = text->f_current_target->read(read_pos);
            switch(element->elementType()){
                case ElementType::BRACKET:
                case ElementType::SCOPE:
                case ElementType::SEQUENCE:
            }
        }

    }

}