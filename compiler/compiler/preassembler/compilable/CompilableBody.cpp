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
#include "CompilableBody.hpp"

#include "../../../log/logger.hpp"

using namespace nylium;

size_t index = 0;

CompilableBody::CompilableBody(CompilableType ctype){
    this->f_orderIndex = index++;
    this->f_ctype = ctype;

    if (nlog::lowestRelevantLogLevel() >= nlog::LOGLEVEL::DEBUG_3){
        nlog::log(nlog::LOGLEVEL::DEBUG_3, std::string("building CompilableBody #") + std::to_string(f_orderIndex));
    }
}