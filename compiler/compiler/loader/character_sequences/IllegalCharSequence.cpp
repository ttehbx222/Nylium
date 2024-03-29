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
#include "IllegalCharSequence.hpp"

#include "../../error_handling/errors/LS001.hpp"

nylium::IllegalCharSequence::IllegalCharSequence(std::string& content, size_t line_number, size_t coloumn, FileInterface* fInterface) : CharSequence(content, line_number, coloumn, CharSequenceType::ILLEGAL) {
    LS001::throwError(this, fInterface);
}