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
#include "Scope.hpp"

using namespace nylium;

Scope::Scope(Scope* scope, SequenceScope* seqScope, CompilableType ctype) : CompilableBody(ctype){
    this->f_layer = scope->f_layer;
    this->f_parent = scope;
    this->f_text_code = seqScope;
    this->f_parent_interface = scope->f_parent_interface;
    this->f_depth = scope->f_depth+1;
}

Scope::Scope(FileInterface* fInterface) : CompilableBody(CompilableType::SCOPE){
    this->f_parent_interface = fInterface;
    this->f_text_code = &(fInterface->f_text->f_scope);
}