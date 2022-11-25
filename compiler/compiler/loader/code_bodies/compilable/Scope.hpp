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

#include <vector>
#include "../CodeLine.hpp"
#include "../PendingDeclaration.hpp"
#include "../../utils/DeclarationSearch.hpp"
#include "../../load_iterations/0_CharSequences.hpp"


namespace nylium{

	struct FileInterface;

    struct Scope : public CodeLine {

			SCOPE_LAYER f_layer = SCOPE_LAYER::MAIN;

		    Scope* f_parent;
		    DeclarationSearch f_accessibles;
		    FileInterface* f_parent_interface;
	    	std::vector<CODE> f_code;

			SequenceScope* f_text_code;

			Scope(){}
	    	Scope(Scope* scope);
	    	Scope(FileInterface* file);
	    	inline Scope* parent() { return f_parent; }
	    	inline std::vector<CODE>& code() { return f_code; }
	    	Visibility visibilityOf(Scope* scope);
	      	Declaration* searchDeclaration(PendingDeclaration* decl);
	    	void addDeclaration(Declaration* decl) {} //TODO
	};

    typedef Scope* SCOPE;

}