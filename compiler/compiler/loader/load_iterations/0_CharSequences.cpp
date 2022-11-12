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
#include "0_CharSequences.hpp"

const char regex_bracket[] = "[\\(\\)<>{}\\[\\]]";
const char regex_empty_separator[] = "[ \t]+";
const char regex_end[] = ";";
const char regex_list_separator[] = ",";
const char regex_name[] = "[A-Za-z_][A-Za-z0-9]*";
const char regex_operator[] = "[\\+\\-\\*\\/\\&\\|\\^\\!\\=]";

const char regex_value_int_hex[] = "0x[A-Fa-f0-9]+";
const char regex_value_int_bin[] = "0b[01]+";
const char regex_value_int_dec[] = "[0-9]+";

const char regex_value_char[] = "'[^'\\\\]'|'[\\\\].'";
const char regex_value_str[] = "\"([^\"\\\\]|[\\\\].)*\"";

nylium::Text* nylium::loadCharSequences(nylium::FileInterface* fInterface){
    
}