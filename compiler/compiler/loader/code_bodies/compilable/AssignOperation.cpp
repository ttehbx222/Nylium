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
#include "AssignOperation.hpp"
#include "Literal.hpp"
#include "../../../preassembler/utils/Names.hpp"

using namespace nylium;

AssignOperation::AssignOperation(ValueHolder* target, ValueHolder* source) : Operation(target->f_type, target){
    this->f_source = source;
}

void AssignOperation::compile(Assembly* assembly){
    switch(this->f_vhtype){
        case ValueHolderType::LITERAL:
        {
            AssemblyStorageElement* source_element = new AssemblyStorageElement((Literal*)this->f_source);
            assembly->f_data.push_back(source_element);
            //TODO
            //TODO memory_location of field
        }
    }
    //error
}