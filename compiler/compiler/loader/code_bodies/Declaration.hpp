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

#include "ValueHolder.hpp"

namespace nylium{

    enum class Visibility {
		PRIVATE = 0x0,
		PROTECTED = 0x1,
		PUBLIC = 0x2,
        DEFAULT
	};

    enum class DeclarationType {
        CLASS,
        STRUCT,
        ENUM,
        FIELD,
        FUNCTION,
        REFERENCE,
        NAMESPACE
    };

    enum class Boolean{
        TRUE,
        FALSE,
        DEFAULT
    };

    struct DeclarationAttributes {
        Visibility f_visibility = Visibility::DEFAULT;
        DeclarationType f_dtype;
        Boolean f_final = Boolean::DEFAULT;
        Boolean f_static = Boolean::DEFAULT;
    };

    struct Declaration : public ValueHolder {
        DeclarationAttributes* f_attributes;
        std::string f_key;
    };

    //Scope* buildDeclaration(Scope* scope, Text* text, size_t* read_pos, DeclarationAttributes* attributes = new DeclarationAttributes());

}