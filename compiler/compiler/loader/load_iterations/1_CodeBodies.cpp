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
        CharSequence* seq = text->at((*read_pos));
        if (seq->type == CharSequenceType::END){
            return scope;
        }
        return buildDeclaration(scope, text, read_pos);
    }
};

MainBodyMatcher* mainBM = new MainBodyMatcher();

BodyMatcher* bodyMatcherByLevel(SCOPE_LAYER layer){
    switch(layer){
        case SCOPE_LAYER::MAIN: return mainBM;
    }
    return mainBM;
}

void loadBodies(FileInterface* fInterface){

    nlog::log(nlog::LOGLEVEL::INFO, fInterface->name + ".nylium");
}