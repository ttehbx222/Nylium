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

namespace serializer {
#define TYPE_ERROR -2
	template<class V>
	class Serializable {
	public:
		virtual V serialize() = 0;
		template<class T>
		virtual T& value() = 0;
	};
	namespace string {
		class SerializableString : public Serializable<std::string>{
		private:
			std::string s_str;
		public:
			template<class T>
			T& value() {
				if (typeid(T) != typeid(std::string)) {
					throw TYPE_ERROR;
				}
				return s_str;
			}
			std::string serialze() {
				return s_str;
			}
		};
	}
}