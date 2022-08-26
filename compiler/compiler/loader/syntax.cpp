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
#include "syntax.h"

namespace nylium {
	namespace syntax {
		bool init = false;
		Tree<codebody::CB_Type> expected_main;

		void init();
		
		Tree<codebody::CB_Type>* get() {
			if (!init) {
				init();
			}
			return &expected_main;
		}

		void init() {
			//n1
			auto n1_ocb = expected_main.add(codebody::CB_Type::OPTION_CODE_BRACKET);
			auto n1_ofi = expected_main.add(codebody::CB_Type::OPTION_FIELD);
			auto n1_ofu = expected_main.add(codebody::CB_Type::OPTION_FUNCTION);
			auto n1_oo = expected_main.add(codebody::CB_Type::OPTION_OBJECT);
			auto n1_t = expected_main.add(codebody::CB_Type::TYPE);
			auto n1_n = expected_main.add(codebody::CB_Type::NAME);

			//linking back
			expected_main.addPtr(codebody::CB_Type::CODE_BRACKET, &expected_main);
			expected_main.addPtr(codebody::CB_Type::END, &expected_main);

			n1_ocb->addPtr(codebody::CB_Type::OPTION_CODE_BRACKET, n1_ocb);
			n1_ofi->addPtr(codebody::CB_Type::OPTION_FIELD, n1_ofi);
			n1_ofu->addPtr(codebody::CB_Type::OPTION_FUNCTION, n1_ofu);
			n1_oo->addPtr(codebody::CB_Type::OPTION_OBJECT, n1_oo);
			
			//n2
			auto n2_ocb_cb = n1_ocb->add(codebody::CB_Type::CODE_BRACKET);
			auto n2_ocb_n = n1_ocb->add(codebody::CB_Type::NAME);

			auto n2_ofi_t = n1_ofi->add(codebody::CB_Type::TYPE);

			auto n2_ofu_t = n1_ofu->add(codebody::CB_Type::TYPE);
		}
	}
}