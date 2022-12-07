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
#include "Declaration.hpp"

#include "../character_sequences/NyliumCharSequence.hpp"
#include "../load_iterations/0_CharSequences.hpp"
#include "compilable/Scope.hpp"
#include "compilable/FunctionDeclaration.hpp"

using namespace nylium;

Declaration::Declaration(DeclarationAttributes* attributes, PendingDeclaration* type, std::string& name, ValueHolderType vhtype) : ValueHolder(vhtype, type, CompilableType::DECLARATION){
    this->f_attributes = attributes;
    this->f_key = name;
}