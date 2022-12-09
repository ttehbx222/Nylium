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

#include <string>
#include "CodeObject.hpp"

namespace nylium{

    enum class ValueHolderType{
        LITERAL,
        OPERATION,
        FIELD,
        FUNCTION,
        PENDING_DECLARATION,
        TYPE,
        NAMESPACE
    };

    struct PendingDeclaration;

    struct ValueHolder : public CodeObject, public CompilableBody{
        ValueHolderType f_vhtype;
		PendingDeclaration* f_type;
        ValueHolder(ValueHolderType vhtype, PendingDeclaration* type, CompilableType ctype);
	};

}