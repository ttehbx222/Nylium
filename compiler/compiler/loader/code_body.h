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

namespace nylium {
	namespace codebody {
		enum CB_Type {
			OPTION_FIELD = 0x1,
			OPTION_FUNCTION = 0x2,
			OPTION_OBJECT = 0x4,
			OPTION_CODE_BRACKET = 0x8,
			TYPE = 0x10,
			NAME = 0x20,
			VALUE_BRACKET = 0x40,
			CODE_BRACKET = 0x80,
			SPECIFY_BRACKET = 0x100,
			OPERATOR = 0x200,
			MEMBER_SEPERATOR = 0x400,
			STATIC_SEPERATOR = 0x800,
			END = 0x1000
			//TODO more types
		};
		struct CodeBody {
			int type;
		};
		CodeBody* get(CB_Type type, std::string name);
	}
}