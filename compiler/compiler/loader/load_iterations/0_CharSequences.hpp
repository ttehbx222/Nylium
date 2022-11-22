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
#include "../character_sequences/NyliumCharSequence.hpp"
#include "../project/Interface.hpp"

namespace nylium{

    struct SequenceLine : public ContainerElement{
        std::vector<Element*> f_elements;

        inline SequenceLine(ContainerElement* parent) { f_parent = parent; }
        inline Element* read(size_t* read_pos) { return f_elements.at((*read_pos)++); }
        
        void push(CharSequence* in, Text* text);
        ElementType elementType() { return ElementType::LINE; }
    };

    enum class BracketListType {
        OPEN_LINE_LIST,
        SINGLE,
        ENDED_LINE_LIST
    };

    struct SequenceBracket : public ContainerElement{
        BracketListType f_btype = BracketListType::SINGLE;
        std::vector<SequenceLine*> f_contents;

        inline SequenceBracket(ContainerElement* parent) { f_parent = parent; }
        ElementType elementType() { return ElementType::BRACKET; }
    };

    enum class ScopeListType {
        SCOPE,
        INITIALIZER_LIST,
        SINGLE //unused
    };

    struct SequenceScope : public ContainerElement{
        ScopeListType f_stype = ScopeListType::SCOPE;
        std::vector<SequenceLine*> f_contents;

        inline SequenceScope(ContainerElement* parent) { f_parent = parent; }

        ElementType elementType() { return ElementType::SCOPE; }
    };

    struct Text {
        SequenceScope f_scope = SequenceScope(nullptr);
        SequenceLine* f_current_target = new SequenceLine(&f_scope);
        FileInterface* f_interface;

        inline Text(FileInterface* fInterface) { f_interface = fInterface; f_scope.f_contents.push_back(f_current_target); }
        void log();
    };

    void loadCharSequences(FileInterface* fInterface);

}