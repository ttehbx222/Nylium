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

#include "../../code_bodies/compilable/Scope.hpp"
#include "../../code_bodies/Operation.hpp"
#include "../../code_bodies/compilable/Keyword.hpp"

namespace nylium{

    struct ConditionalScope : public Scope, public Keyword {
        inline ConditionalScope(Scope* scope, SequenceScope* text_code) : Scope(scope, text_code){};
    };

    struct IfKeyword : ConditionalScope{
        ValueHolder* f_condition;
        ConditionalScope* f_following = nullptr;
        ConditionalScope* f_last = this;
        inline IfKeyword(ValueHolder* condition, SequenceScope* element, Scope* scope) : ConditionalScope(scope, element) { f_condition = condition;f_layer = SCOPE_LAYER::FUNCTION;  }; //TODO add SequenceScope
        virtual void compile(Assembly*);
    };

}