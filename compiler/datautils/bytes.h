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

typedef BYTE unsigned char;

struct Bytes {
	BYTE* ptr;
	size_t length;
	Bytes(BYTE* ptr, size_t length) {
		this->ptr = malloc(length);
		this->length = length;
		memcpy(this->ptr, ptr, length);
	}
	append(BYTE* ptr, size_t length) {
		size_t new_length = this->length + length;
		BYTE* new_ptr = (BYTE*) malloc(new_length);
		memcpy(new_ptr, this->ptr, this->length);
		memcpy(new_ptr + this->length, ptr, length);

	}
	inline append(Bytes& bytes) {
		append(bytes.ptr, bytes.length);
	}
};