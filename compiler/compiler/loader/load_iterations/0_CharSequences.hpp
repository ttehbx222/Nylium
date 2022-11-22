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
        
        void push(CharSequence* in, Text* text);
        ElementType elementType() { return ElementType::LINE; }
    };

    enum class BracketListType {
        OPERN_LINE_LIST,
        SINGLE,
        ENDED_LINE_LIST,
        EMPTY
    };

    struct SequenceBracket : public ContainerElement{
        BracketListType f_btype = BracketListType::EMPTY;
        std::vector<SequenceLine*> f_contents;

        inline SequenceBracket(ContainerElement* parent) { f_parent = parent; }

        void push(CharSequence* in, Text* text);
        ElementType elementType() { return ElementType::BRACKET; }
    };

    struct SequenceScope : public ContainerElement{
        std::vector<SequenceLine*> f_contents;

        inline SequenceScope(ContainerElement* parent) { f_parent = parent; }

        void push(CharSequence* in, Text* text);
        ElementType elementType() { return ElementType::SCOPE; }
    };

    struct Text {
        SequenceScope f_scope;
        ContainerElement* f_current_target = &f_scope;
        FileInterface* f_interface;
        inline Text(FileInterface* fInterface) { f_interface = fInterface; }
    };

    void loadCharSequences(FileInterface* fInterface);

}