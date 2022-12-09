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
#include "ClassType.hpp"

using namespace nylium;

ClassType* self = nullptr;

ClassType::ClassType(Scope* scope) : TypeDeclaration(nullptr, std::string("Class"), std::vector<PendingDeclaration*>(), scope, nullptr) {
    self = this;
    this->f_type = this;
    DeclarationAttributes* attributes = new DeclarationAttributes();
    attributes->f_final = Boolean::TRUE;
    attributes->f_visibility = Visibility::PUBLIC;
    attributes->f_static = Boolean::FALSE;
    attributes->f_dtype = DeclarationType::CLASS;
    this->f_attributes = attributes;
}

ClassType* nylium::getClassType(){
    return self;
}