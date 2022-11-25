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
#include "1_CodeBodies.hpp"

#include "../code_bodies/compilable/NamespaceDeclaration.hpp"
#include "../character_sequences/NyliumCharSequence.hpp"
#include "0_CharSequences.hpp"
#include "../native/keywords/Keywords.hpp"

#include "../../error_handling/errors/CB001.hpp"
#include "../../error_handling/errors/CB002.hpp"
#include "../../error_handling/errors/CB003.hpp"
#include "../../error_handling/errors/CB004.hpp"
#include "../../error_handling/errors/CB005.hpp"
#include "../../error_handling/errors/CB006.hpp"
#include "../../error_handling/errors/CB007.hpp"
#include "../../error_handling/errors/CB008.hpp"

#include "../../../log/logger.hpp"

using namespace nylium;

struct BodyMatcher{
    virtual Scope* next(Scope* scope, Text* text, size_t* read_pos) = 0;
};

struct MainBodyMatcher : public BodyMatcher {
    SCOPE next(SCOPE scope, Text* text, size_t* read_pos){
        return nullptr;
    }
};

struct FunctionBodyMatcher : public BodyMatcher {
    SCOPE next(SCOPE scope, Text* text, size_t* read_pos){
        return nullptr;
    }
};

MainBodyMatcher* mainBM = new MainBodyMatcher();
FunctionBodyMatcher* funcBM = new FunctionBodyMatcher();

BodyMatcher* bodyMatcherByLevel(SCOPE_LAYER layer){
    switch(layer){
        case SCOPE_LAYER::MAIN: 
        case SCOPE_LAYER::CLASS:
            return mainBM;
        case SCOPE_LAYER::FUNCTION:
            return funcBM;
    }
    return mainBM;
}

namespace builder{
    Scope* buildMainScope(Scope* scope, Text* text);
    namespace declaration{
        Scope* buildDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos);
        Scope* buildNamespaceDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos);
    }
}

void nylium::loadBodies(FileInterface* fInterface){
    nlog::log(nlog::LOGLEVEL::INFO, fInterface->name + ".nylium");
    Text* text = fInterface->f_text;

    text->f_current_target = text->f_scope.f_contents.front();
    fInterface->main_scope->f_text_code = &(text->f_scope);
    //TODO
}

std::vector<std::string>& keywords = allKeywords();
std::vector<std::string>& operation_keywords = operationKeywords();

namespace builder{

    Scope* buildMainScope(Scope* scope, Text* text){
        size_t read_pos = 0;
        return declaration::buildDeclaration(scope, text, new DeclarationAttributes(), &read_pos);
    }

    namespace declaration{

        Scope* declaration::buildDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos){
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;
            switch(element->elementType()){
                case ElementType::BRACKET:
                {
                    CB001::throwError(seq, text->f_interface);
                    return nullptr;
                }
                case ElementType::SCOPE:
                {
                    CB005::throwError(seq, text->f_interface);
                    return nullptr;
                }
                case ElementType::SEQUENCE:
                {
                    if (seq->type == CharSequenceType::END){ // check for importance
                        CB004::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (seq->type != CharSequenceType::NAME){
                        CB001::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (seq->chars == "public"){
                        if (attributes->f_visibility != Visibility::DEFAULT){
                            CB003::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        attributes->f_visibility = Visibility::PUBLIC;
                        return buildDeclaration(scope, text, attributes, read_pos);
                    }
                    if (seq->chars == "protected"){
                        if (attributes->f_visibility != Visibility::DEFAULT){
                            CB003::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        attributes->f_visibility = Visibility::PROTECTED;
                        return buildDeclaration(scope, text, attributes, read_pos);
                    }
                    if (seq->chars == "private"){
                        if (attributes->f_visibility != Visibility::DEFAULT){
                            CB003::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        attributes->f_visibility = Visibility::PRIVATE;
                        return buildDeclaration(scope, text, attributes, read_pos);
                    }
                    if (seq->chars == "static"){
                        if (attributes->f_static != Boolean::DEFAULT){
                            CB002::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        attributes->f_static = Boolean::TRUE;
                        return buildDeclaration(scope, text, attributes, read_pos);
                    }
                    if (seq->chars == "final"){
                        if (attributes->f_final != Boolean::DEFAULT){
                            CB002::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        attributes->f_final = Boolean::TRUE;
                        return buildDeclaration(scope, text, attributes, read_pos);
                    }
                    if (seq->chars == "class"){
                        if (attributes->f_static == Boolean::TRUE){
                            warn("\"static class\" is identical to \"namespace\"", seq, text->f_interface);
                            if (attributes->f_final == Boolean::TRUE){
                                warn("\"final\" has no effect on namespaces", seq, text->f_interface);
                            }
                            attributes->f_dtype = DeclarationType::NAMESPACE;
                            return buildNamespaceDeclaration(scope, text, attributes, read_pos);
                        }
                        attributes->f_dtype = DeclarationType::CLASS;
                        //TODO return buildTypeDeclaration
                    }
                    if (seq->chars == "struct"){
                        if (attributes->f_static == Boolean::TRUE){
                            CB007::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        attributes->f_dtype = DeclarationType::STRUCT;
                        //TODO return buildTypeDeclaration
                    }
                    /*if (seq->chars == "enum"){
                        attributes->f_dtype = DeclarationType::ENUM;
                        //TODO return buildTypeDeclaration
                    }*/ //not implemented yet
                    if (seq->chars == "namespace"){
                        if (attributes->f_static == Boolean::TRUE){
                            warn("\"static\" has no effect on namespaces", seq, text->f_interface);
                        }
                        if (attributes->f_final == Boolean::TRUE){
                            warn("\"final\" has no effect on namespaces", seq, text->f_interface);
                        }
                        attributes->f_dtype = DeclarationType::NAMESPACE;
                        return buildNamespaceDeclaration(scope, text, attributes, read_pos);
                    }
                    if (std::find(operation_keywords.begin(), operation_keywords.end(), seq->chars) != operation_keywords.end()){
                        CB006::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (attributes->f_static == Boolean::TRUE && scope->f_layer == SCOPE_LAYER::MAIN){
                        warn("Declaration must already be static", seq, text->f_interface);
                    }
                    //TODO return buildFieldOrFunctionDeclaration
                }
            }
            return nullptr; //compiler reasons
        }

        Scope* declaration::buildNamespaceDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos){
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;
            switch(element->elementType()){
                case ElementType::BRACKET:
                {
                    CB001::throwError(seq, text->f_interface);
                    return nullptr;
                }
                case ElementType::SCOPE:
                {
                    CB008::throwError(seq, text->f_interface);
                    Namespace* namespace_decl = new Namespace(std::string("$unnamed_namespace"), (SequenceScope*)element, attributes, scope);
                    //scope->addDeclaration(namespace_decl); //check for importance
                    return namespace_decl;
                }
                case ElementType::SEQUENCE:
                {
                    if (seq->type == CharSequenceType::END){ // check for importance
                        CB004::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (seq->type != CharSequenceType::NAME){
                        CB001::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (std::find(keywords.begin(), keywords.end(), seq->chars) != keywords.end()){
                        CB006::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    std::string namespace_name = seq->chars;
                    //TODO read_next
                }
            }
            return nullptr; //compiler reasons
        }

    }

}