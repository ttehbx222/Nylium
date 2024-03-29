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

#include <vector>

#include "CallOperation.hpp"
#include "../Declaration.hpp"

namespace nylium{

    struct FunctionCallOperation : public CallOperation {
        std::vector<ValueHolder*> f_arguments;
        FunctionCallOperation(PendingDeclaration* target, std::string& label, std::vector<ValueHolder*>& arguments, Scope* container, bool f_static = false);
        void compile(Assembly*);
        void debug_print(int depth);
        void resolve();
    };

}