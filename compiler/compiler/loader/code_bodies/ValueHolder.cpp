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
#include "ValueHolder.hpp"

using namespace nylium;

ValueHolder::ValueHolder(ValueHolderType vhtype, PendingDeclaration* type, CompilableType ctype) : CompilableBody(ctype){
    this->f_vhtype = vhtype;
    this->f_type = type;
}