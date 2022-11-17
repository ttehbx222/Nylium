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

#include "../../../datautils/linked_tree.hpp"
#include "../code_bodies/CodeObject.hpp"
#include "../character_sequences/NyliumCharSequence.hpp"

using namespace nylium;

bool isInit = false;
Tree<CharSequenceType, BodyMatcher*>* body_determ = new Tree<CharSequenceType, BodyMatcher*>(nullptr);

void init(){
    
    isInit = true;
}

void nylium::loadBodies(FileInterface* fInterface){
    if (!isInit){
        init();
    }
}