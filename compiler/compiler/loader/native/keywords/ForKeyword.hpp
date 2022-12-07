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

    struct ForKeyword : public Scope, public Keyword{
        ValueHolder* f_condition;
        ValueHolder* f_init;
        ValueHolder* f_iteration;
        inline ForKeyword(ValueHolder* init, ValueHolder* condition, ValueHolder* iteration, SequenceScope* element, Scope* scope) : Scope(scope, element, CompilableType::KEYWORD), Keyword(KeywordType::FOR) { f_init = init; f_condition = condition; f_iteration = iteration; f_layer = SCOPE_LAYER::FUNCTION;  }; //TODO add SequenceScope
        virtual void compile(Assembly*);
    };

}