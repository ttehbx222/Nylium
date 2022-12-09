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
#include "../../utils/DeclarationMap.hpp"
#include "../../load_iterations/0_CharSequences.hpp"


namespace nylium{

	struct FileInterface;

    struct Scope : public CodeLine, public CompilableBody {

			SCOPE_LAYER f_layer = SCOPE_LAYER::MAIN;

		    Scope* f_parent;
		    DeclarationMap f_accessibles;
			std::vector<Scope*> f_decls;
		    FileInterface* f_parent_interface;
	    	std::vector<CompilableBody*> f_code;
			int f_depth;

			SequenceScope* f_text_code;

	    	Scope(Scope* scope, SequenceScope* seqScope, CompilableType ctype = CompilableType::SCOPE);
	    	Scope(FileInterface* file);
	    	inline Scope* parent() { return f_parent; }
	    	inline std::vector<CompilableBody*>& code() { return f_code; }
	    	Visibility visibilityOf(Scope* scope);
	      	Declaration* searchDeclaration(PendingDeclaration* decl);
	    	void addDeclaration(Declaration* decl) { //TODO move to cpp //TODO check if order of declaration is needed inside functions
				if (decl->f_ctype == CompilableType::SCOPE || decl->f_vhtype == ValueHolderType::NAMESPACE || decl->f_vhtype == ValueHolderType::FUNCTION || decl->f_vhtype == ValueHolderType::TYPE){
					f_decls.push_back((Scope*)decl);
				}
				f_accessibles.addDeclaration(decl);
			}

			void resolveDeclarations();

			virtual void compile(Assembly*);
			virtual void debug_print(int depth);
	};

    typedef Scope* SCOPE;

}