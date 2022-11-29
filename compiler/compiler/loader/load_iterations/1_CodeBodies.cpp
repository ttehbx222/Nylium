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

#include "../code_bodies/compilable/TypeDeclaration.hpp"
#include "../code_bodies/compilable/FunctionCallOperation.hpp"
#include "../code_bodies/Operation.hpp"
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
#include "../../error_handling/errors/CB009.hpp"
#include "../../error_handling/errors/CB010.hpp"

#include "../../../log/logger.hpp"

using namespace nylium;

namespace builder{
    Scope* buildStart(Scope* scope, Text* text, size_t* read_pos);
    void import(Scope* scope, Text* text, size_t* read_pos);
    namespace declaration{
        Scope* buildDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos);
        Scope* buildNamespaceDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos);
        Scope* buildTypeDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos); 
    }
    namespace misc{
        Scope* buildFieldOrOperationOrFunctionDeclaration(Scope* scope, Text* text, size_t* read_pos, PendingDeclaration* first_label);
    }
    namespace operation{
        Operation* buildOperationStart(Scope* scope, Text* text, size_t* read_pos);
        Operation* buildOperationArgument(Scope* scope, Text* text, size_t* read_pos, PendingDeclaration* target, std::string& operation, bool f_operator);
    }
}

void nylium::loadBodies(FileInterface* fInterface){
    nlog::log(nlog::LOGLEVEL::INFO, fInterface->name + ".nylium");
    Text* text = fInterface->f_text;

    fInterface->main_scope->f_text_code = &(text->f_scope);

    std::vector<Scope*> toBeLoaded = {fInterface->main_scope};
    std::vector<Scope*> newToBeLoaded;

    while(!toBeLoaded.empty()){
        for (Scope* scope : toBeLoaded){
            for (SequenceLine* line : scope->f_text_code->f_contents){
                Scope* newScope = nullptr;
                size_t read_pos = 0;
                try{
                    switch(scope->f_layer){
                        case SCOPE_LAYER::MAIN:
                        {
                            text->f_current_target = line;
                            newScope = builder::buildStart(scope, text, &read_pos);
                            break;
                        }
                    }
                }catch(CharSequence* seq){

                }
                if (newScope){
                    newToBeLoaded.push_back(newScope);
                }
            }
        }
        toBeLoaded = newToBeLoaded;
        newToBeLoaded.clear();
    }
}

std::vector<std::string>& keywords = allKeywords();
std::vector<std::string>& operation_keywords = operationKeywords();

bool assertCustomLabels(CharSequence* seq, Text* text){
    if (seq->type == CharSequenceType::END){ // check for importance
        CB004::throwError(seq, text->f_interface);
        return false;
    }
    if (seq->type != CharSequenceType::NAME){
        CB001::throwError(seq, text->f_interface);
        return false;                    
    }
    if (std::find(keywords.begin(), keywords.end(), seq->chars) != keywords.end()){
        CB006::throwError(seq, text->f_interface);
        return false;
    }
    return true;
}

namespace builder{

    Scope* builder::buildStart(Scope* scope, Text* text, size_t* read_pos){
        SequenceLine* element = text->f_current_target->read(read_pos);
        CharSequence* seq = element->f_sequence;
        switch(element->elementType()){
            case ElementType::BRACKET:
            {
                CB001::throwError(seq, text->f_interface);
                return nullptr;
            }
            case ElementType::SCOPE:
            {
                //TODO nested function scope
                CB005::throwError(seq, text->f_interface);
                return nullptr;
            }
            case ElementType::SEQUENCE:
            {
                if (seq->type == CharSequenceType::END){ // check for importance
                    return nullptr;
                }
                //TODO hadle ++$, --$ operators
                if (seq->type != CharSequenceType::NAME){
                    CB001::throwError(seq, text->f_interface);
                    return nullptr;
                }
                if (text->f_current_target->f_parent == &(text->f_scope) && seq->chars == "import"){
                    builder::import(scope, text, read_pos);
                    return nullptr;
                }
                if (seq->chars == "public"){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_visibility != Visibility::DEFAULT){
                        CB003::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    attributes->f_visibility = Visibility::PUBLIC;
                    return declaration::buildDeclaration(scope, text, attributes, read_pos);
                }
                if (seq->chars == "protected"){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_visibility != Visibility::DEFAULT){
                        CB003::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    attributes->f_visibility = Visibility::PROTECTED;
                    return declaration::buildDeclaration(scope, text, attributes, read_pos);
                }
                if (seq->chars == "private"){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_visibility != Visibility::DEFAULT){
                        CB003::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    attributes->f_visibility = Visibility::PRIVATE;
                    return declaration::buildDeclaration(scope, text, attributes, read_pos);
                }
                if (seq->chars == "static"){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_static != Boolean::DEFAULT){
                        CB002::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    attributes->f_static = Boolean::TRUE;
                    return declaration::buildDeclaration(scope, text, attributes, read_pos);
                }
                if (seq->chars == "final"){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_final != Boolean::DEFAULT){
                        CB002::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    attributes->f_final = Boolean::TRUE;
                    return declaration::buildDeclaration(scope, text, attributes, read_pos);
                }
                if (seq->chars == "class" && ((int)scope->f_layer & ((int)SCOPE_LAYER::CLASS | (int)SCOPE_LAYER::MAIN))){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_static == Boolean::TRUE){
                        warn("\"static class\" is identical to \"namespace\"", seq, text->f_interface);
                        if (attributes->f_final == Boolean::TRUE){
                            warn("\"final\" has no effect on namespaces", seq, text->f_interface);
                        }
                        attributes->f_dtype = DeclarationType::NAMESPACE;
                        return declaration::buildNamespaceDeclaration(scope, text, attributes, read_pos);
                    }
                    attributes->f_dtype = DeclarationType::CLASS;
                    return declaration::buildTypeDeclaration(scope, text, attributes, read_pos);
                }
                if (seq->chars == "struct" && ((int)scope->f_layer & ((int)SCOPE_LAYER::CLASS | (int)SCOPE_LAYER::MAIN))){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_static == Boolean::TRUE){
                        CB007::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    attributes->f_dtype = DeclarationType::STRUCT;
                    return declaration::buildTypeDeclaration(scope, text, attributes, read_pos);
                }
                /*if (seq->chars == "enum"){
                    attributes->f_dtype = DeclarationType::ENUM;
                    return declaration::buildTypeDeclaration(scope, text, attributes, read_pos);
                }*/ //not implemented yet
                if (seq->chars == "namespace" && ((int)scope->f_layer & (int)SCOPE_LAYER::MAIN)){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_static == Boolean::TRUE){
                        warn("\"static\" has no effect on namespaces", seq, text->f_interface);
                    }
                    if (attributes->f_final == Boolean::TRUE){
                        warn("\"final\" has no effect on namespaces", seq, text->f_interface);
                    }
                    attributes->f_dtype = DeclarationType::NAMESPACE;
                    return declaration::buildNamespaceDeclaration(scope, text, attributes, read_pos);
                }

                //TODO check for operation keywords

                return misc::buildFieldOrOperationOrFunctionDeclaration(scope, text, read_pos, new PendingDeclaration(seq->chars));
            }
        }
        return nullptr;
    }

    void import(Scope* scope, Text* text, size_t* read_pos){
        //TODO import
    }

    namespace declaration{

        Scope* declaration::buildDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos){
            SequenceLine* element = text->f_current_target->read(read_pos);
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
                        return declaration::buildTypeDeclaration(scope, text, attributes, read_pos);
                    }
                    if (seq->chars == "struct"){
                        if (attributes->f_static == Boolean::TRUE){
                            CB007::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        attributes->f_dtype = DeclarationType::STRUCT;
                        return declaration::buildTypeDeclaration(scope, text, attributes, read_pos);
                    }
                    /*if (seq->chars == "enum"){
                        attributes->f_dtype = DeclarationType::ENUM;
                        return declaration::buildTypeDeclaration(scope, text, attributes, read_pos);
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
                    if (attributes->f_static == Boolean::TRUE && (int)scope->f_layer & (int)SCOPE_LAYER::MAIN){
                        warn("\"static\" has no effect", seq, text->f_interface);
                    }
                    if (attributes->f_static == Boolean::TRUE && (int)scope->f_layer & (int)SCOPE_LAYER::MAIN){
                        warn("\"static\" has no effect", seq, text->f_interface);
                    }
                    //return buildFieldOrFunctionDeclaration
                }
            }
            return nullptr; //compiler reasons
        }

        Scope* declaration::buildNamespaceDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos){
            SequenceLine* element = text->f_current_target->read(read_pos);
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
                    return nullptr;
                }
                case ElementType::SEQUENCE:
                {
                    if (!assertCustomLabels(seq, text)){
                        return nullptr;
                    }
                    std::string namespace_name = seq->chars;

                    element = text->f_current_target->read(read_pos);
                    seq = element->f_sequence;
                    if (element->elementType() != ElementType::SCOPE){
                        CB001::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (((SequenceScope*)element)->f_stype == ScopeListType::INITIALIZER_LIST){
                        CB009::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    Namespace* namespace_decl = new Namespace(namespace_name, (SequenceScope*)element, attributes, scope);
                    scope->addDeclaration(namespace_decl);
                    return namespace_decl;
                }
            }
            return nullptr; //compiler reasons
        }

        Scope* declaration::buildTypeDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos){
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
                    CB010::throwError(seq, text->f_interface);
                    return nullptr;
                }
                case ElementType::SEQUENCE:
                {
                    if (!assertCustomLabels(seq, text)){
                        return nullptr;
                    }
                    std::string type_name = seq->chars;

                    element = text->f_current_target->read(read_pos);
                    seq = element->f_sequence;
                    if (element->elementType() != ElementType::SCOPE){ //TODO inheritance
                        CB001::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (((SequenceScope*)element)->f_stype == ScopeListType::INITIALIZER_LIST){
                        CB009::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    TypeDeclaration* type_decl = new TypeDeclaration(type_name, (SequenceScope*)element, attributes, scope);
                    scope->addDeclaration(type_decl);
                    return type_decl;
                }
            }
        }

    }

    namespace misc{

        Scope* misc::buildFieldOrOperationOrFunctionDeclaration(Scope* scope, Text* text, size_t* read_pos, PendingDeclaration* first_label){
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;

            switch(element->elementType()){
                case ElementType::BRACKET:
                case ElementType::SCOPE:
                {
                    CB001::throwError(seq, text->f_interface);
                    return nullptr;
                }
                case ElementType::SEQUENCE:
                {
                    if (seq->type == CharSequenceType::OPERATOR && (int)scope->f_layer & (int)SCOPE_LAYER::FUNCTION){
                        Operation* operation;
                        if (seq->chars == "." || seq->chars == "::"){
                            operation = operation::buildOperationArgument(scope, text, read_pos, first_label, std::string(""), false);
                        }else{
                            operation = operation::buildOperationArgument(scope, text, read_pos, first_label, std::string(""), true);
                        }
                        
                        if (operation){
                            scope->f_code.push_back(operation);
                        }
                    }
                    if (!assertCustomLabels(seq, text)){
                        return nullptr;
                    }
                    //TODO return buildFieldOrFunctionDeclaration
                }
            }
        }

    }

    namespace operation{

        Operation* operation::buildOperationStart(Scope* scope, Text* text, size_t* read_pos){
            //todo handle ++$, --$ operators
            return nullptr;
        }

        Operation* operation::buildOperationArgument(Scope* scope, Text* text, size_t* read_pos, PendingDeclaration* target, std::string& operation, bool f_operator){
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;

            switch(element->elementType()){
                case ElementType::BRACKET:
                {
                    switch(seq->chars[0]){
                        case '(':
                        {
                            if (!f_operator){
                                if (operation == ""){
                                    //error 
                                    return nullptr;
                                }
                                //return buildFunctionCallOperation
                            }
                            Operation* argument = buildOperationStart(scope, text, read_pos);
                            if (argument){
                                Operation* result = new FunctionCallOperation(target, operation, std::vector<ValueHolder*>({argument}));
                                return result;
                            }
                            return nullptr;
                        }
                        case ')':
                        {
                            if (f_operator){
                                //return functioncalloperation, no argument
                            }
                            if (operation == ""){
                                //error
                                return nullptr;
                            }
                            //return calloperation
                        }
                        default:
                        {
                            CB001::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                    }
                }
                case ElementType::SCOPE:
                {
                    //TODO initializer list
                    CB001::throwError(seq, text->f_interface);
                    return nullptr;
                }
                case ElementType::SEQUENCE:
                {
                    if (seq->type == CharSequenceType::OPERATOR){
                        if (f_operator){
                            return buildOperationArgument(scope, text, read_pos, target, operation + seq->chars, true);
                        }else{
                            //return call operation as source continuing with wrapped operation
                        }
                    }
                    if (!assertCustomLabels(seq, text)){
                        return nullptr;
                    }
                    if (f_operator){
                        //return function call operation
                    }
                    if (operation == ""){
                        return buildOperationArgument(scope, text, read_pos, target, seq->chars, false);
                    }
                    //error
                    return nullptr;
                }
            }
        }

    }


}