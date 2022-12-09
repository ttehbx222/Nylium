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
#include "../data/AssemblyRepresentation.hpp"

namespace nylium{

    enum class CompilableType{
        KEYWORD,
        SCOPE,
        OPERATION,
        DECLARATION,
        LITERAL
    };

    struct CompilableBody {
        CompilableType f_ctype;
        virtual void compile(Assembly* assembly) = 0;
        inline CompilableBody(CompilableType ctype){
            this->f_ctype = ctype;
        }
        virtual void debug_print(int depth) = 0;
        virtual void resolve() = 0;
    };

}