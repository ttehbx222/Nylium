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
#include "../code_bodies/compilable/CastingOperation.hpp"
#include "../code_bodies/Operation.hpp"
#include "../character_sequences/NyliumCharSequence.hpp"
#include "0_CharSequences.hpp"
#include "../native/keywords/Keywords.hpp"
#include "../native/keywords/IfKeyword.hpp"
#include "../native/keywords/ForKeyword.hpp"
#include "../native/keywords/WhileKeyword.hpp"

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

#include "../../error_handling/errors/CB998.hpp"
#include "../../error_handling/errors/CB999.hpp"

#include "../../../log/logger.hpp"

using namespace nylium;

namespace builder{
    Scope* buildStart(Scope* scope, Text* text, size_t* read_pos);
    void import(Scope* scope, Text* text, size_t* read_pos);
    namespace keyword{
        Scope* buildIfKeyword(Scope* scope, Text* text, size_t* read_pos);
        Scope* buildWhileKeyword(Scope* scope, Text* text, size_t* read_pos);
        Scope* buildForKeyword(Scope* scope, Text* text, size_t* read_pos);
        Scope* buildElseKeyword(Scope* scope, Text* text, size_t* read_pos/*,IfKeyword if_statement*/);
    }
    namespace declaration{
        Scope* buildDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos);
        Scope* buildNamespaceDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos);
        Scope* buildTypeDeclaration(Scope* scope, Text* text, DeclarationAttributes* attributes, size_t* read_pos); 
    }
    namespace misc{
        Scope* buildFieldOrOperationOrFunctionDeclaration(Scope* scope, Text* text, size_t* read_pos, PendingDeclaration* first_label);
        ValueHolder* buildValueHolder(Scope* scope, Text* text, size_t* read_pos, int previous_priority = 0);
    }
    namespace operation{
        int operatorPriority(std::string& _operator);
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
                /*if (seq->chars == "struct" && ((int)scope->f_layer & ((int)SCOPE_LAYER::CLASS | (int)SCOPE_LAYER::MAIN))){
                    DeclarationAttributes* attributes = new DeclarationAttributes();
                    if (attributes->f_static == Boolean::TRUE){
                        CB007::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    attributes->f_dtype = DeclarationType::STRUCT;
                    return declaration::buildTypeDeclaration(scope, text, attributes, read_pos);
                }
                if (seq->chars == "enum"){
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

                if (seq->chars == "if" && ((int)scope->f_layer & (int)SCOPE_LAYER::FUNCTION)){
                    return keyword::buildIfKeyword(scope, text, read_pos);
                }

                if (seq->chars == "while" && ((int)scope->f_layer & (int)SCOPE_LAYER::FUNCTION)){
                    return keyword::buildWhileKeyword(scope, text, read_pos);
                }

                if (seq->chars == "for" && ((int)scope->f_layer & (int)SCOPE_LAYER::FUNCTION)){
                    return keyword::buildForKeyword(scope, text, read_pos);
                }

                if (seq->chars == "else" && ((int)scope->f_layer & (int)SCOPE_LAYER::FUNCTION)){
                    //TODO check if previous is if
                    //return buildElseKeyword
                }

                return misc::buildFieldOrOperationOrFunctionDeclaration(scope, text, read_pos, new PendingDeclaration(seq->chars));
            }
        }
        return nullptr;
    }

    void import(Scope* scope, Text* text, size_t* read_pos){
        Element* element = text->f_current_target->read(read_pos);
        CharSequence* seq = element->f_sequence;
        ProjectContent* content = text->f_interface->project;
        while(seq->type != CharSequenceType::END){
            if (element->elementType() != ElementType::SEQUENCE){
                CB001::throwError(seq, text->f_interface);
            }
            assertCustomLabels(seq, text);
            if (content->isInterface()){
                CB999::throwError(seq, text->f_interface);
                return;
            }
            auto content_temp = ((Package*)content)->contents.find(seq->chars);
            if (content_temp == ((Package*)content)->contents.end()){
                CB999::throwError(seq, text->f_interface);
                return;
            }
            content = content_temp->second;
            element = text->f_current_target->read(read_pos);
            seq = element->f_sequence;
            if (seq->chars == ";"){
                break;
            }
            if (seq->chars == "."){
                element = text->f_current_target->read(read_pos);
                seq = element->f_sequence;
                continue;
            }
            CB999::throwError(seq, text->f_interface);
            return;
        }
        if (!content->isInterface()){
            CB999::throwError(seq, text->f_interface);
            return;
        }
        text->f_interface->imports.push_back((FileInterface*)content);
    }

    namespace keyword{

        Scope* buildIfKeyword(Scope* scope, Text* text, size_t* read_pos){
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;

            if (element->elementType() != ElementType::BRACKET || ((SequenceBracket*)element)->f_btype != BracketListType::SINGLE){
                CB999::throwError(seq, text->f_interface);
                return nullptr;
            }

            SequenceLine* temp = text->f_current_target;
            text->f_current_target = ((SequenceBracket*)element)->f_contents.front();
            size_t temp_read_pos = 0;
            ValueHolder* operation = misc::buildValueHolder(scope, text, &temp_read_pos);
            text->f_current_target = temp;
            
            element = text->f_current_target->read(read_pos);
            seq = element->f_sequence;

            if (element->elementType() != ElementType::SCOPE || ((SequenceScope*)element)->f_stype != ScopeListType::SCOPE){
                CB999::throwError(seq, text->f_interface);
                return nullptr;
            }

            Scope* if_statement = new IfKeyword(operation, (SequenceScope*)element, scope);
            scope->code().push_back(if_statement);
            return if_statement;
        }

        Scope* buildForKeyword(Scope* scope, Text* text, size_t* read_pos){
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;

            if (element->elementType() != ElementType::BRACKET || ((SequenceBracket*)element)->f_btype != BracketListType::ENDED_LINE_LIST || ((SequenceBracket*)element)->f_contents.size() != 3){
                CB999::throwError(seq, text->f_interface);
                return nullptr;
            }

            SequenceLine* temp = text->f_current_target;

            size_t temp_read_pos = 0;
            text->f_current_target = ((SequenceBracket*)element)->f_contents.front();

            Scope* wrapper_scope = new Scope(scope, nullptr);

            buildStart(wrapper_scope, text, &temp_read_pos);

            ValueHolder* init_operation = (ValueHolder*)wrapper_scope->f_code.front();

            temp_read_pos = 0;
            text->f_current_target = ((SequenceBracket*)element)->f_contents.at(1);
            ValueHolder* condition_operation = misc::buildValueHolder(wrapper_scope, text, &temp_read_pos);

            temp_read_pos = 0;
            text->f_current_target = ((SequenceBracket*)element)->f_contents.at(2);
            ValueHolder* iteration_operation = misc::buildValueHolder(wrapper_scope, text, &temp_read_pos);

            text->f_current_target = temp;

            element = text->f_current_target->read(read_pos);
            seq = element->f_sequence;

            if (element->elementType() != ElementType::SCOPE || ((SequenceScope*)element)->f_stype != ScopeListType::SCOPE){
                CB999::throwError(seq, text->f_interface);
                return nullptr;
            }

            Scope* for_statement = new ForKeyword(init_operation, condition_operation, iteration_operation, (SequenceScope*)element, scope);
            scope->code().push_back(for_statement);
            delete wrapper_scope;
            return for_statement;
        }

        Scope* buildWhileKeyword(Scope* scope, Text* text, size_t* read_pos){
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;

            if (element->elementType() != ElementType::BRACKET || ((SequenceBracket*)element)->f_btype != BracketListType::SINGLE){
                CB999::throwError(seq, text->f_interface);
                return nullptr;
            }

            SequenceLine* temp = text->f_current_target;
            text->f_current_target = ((SequenceBracket*)element)->f_contents.front();
            size_t temp_read_pos = 0;
            ValueHolder* operation = misc::buildValueHolder(scope, text, &temp_read_pos);
            text->f_current_target = temp;
            
            element = text->f_current_target->read(read_pos);
            seq = element->f_sequence;

            if (element->elementType() != ElementType::SCOPE || ((SequenceScope*)element)->f_stype != ScopeListType::SCOPE){
                CB999::throwError(seq, text->f_interface);
                return nullptr;
            }

            Scope* while_statement = new WhileKeyword(operation, (SequenceScope*)element, scope);
            scope->code().push_back(while_statement);
            return while_statement;
        }
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
                    std::vector<PendingDeclaration*> inheritance;
                    if (seq->type == CharSequenceType::OPERATOR && seq->chars == ":"){
                        seq = text->f_current_target->read(read_pos)->f_sequence;
                        if (!assertCustomLabels(seq, text)){
                            CB999::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        inheritance.push_back(new PendingDeclaration(seq->chars));
                        element = text->f_current_target->read(read_pos);
                        seq = element->f_sequence;
                        //TODO multi inheritance
                    }
                    if (element->elementType() != ElementType::SCOPE){
                        CB001::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    if (((SequenceScope*)element)->f_stype == ScopeListType::INITIALIZER_LIST){
                        CB009::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    TypeDeclaration* type_decl = new TypeDeclaration(type_name, (SequenceScope*)element, attributes, scope);
                    type_decl->f_supertypes = inheritance;
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
                        (*read_pos)-=2;
                        ValueHolder* valueHolder = buildValueHolder(scope, text, read_pos);
                        if (valueHolder){
                            scope->f_code.push_back(valueHolder);
                        }
                        return nullptr;
                        /*Operation* operation;
                        if (seq->chars == "." || seq->chars == "::"){
                            operation = operation::buildOperationArgument(scope, text, read_pos, first_label, std::string(""), false);
                        }else{
                            operation = operation::buildOperationArgument(scope, text, read_pos, first_label, std::string(""), true);
                        }
                        
                        if (operation){
                            scope->f_code.push_back(operation);
                        }*/
                    }
                    if (!assertCustomLabels(seq, text)){
                        return nullptr;
                    }
                    //TODO return buildFieldOrFunctionDeclaration
                }
            }
        }

        ValueHolder* misc::buildValueHolder(Scope* scope, Text* text, size_t* read_pos, int previous_priority){ //TODO implement operator priority
            Element* element = text->f_current_target->read(read_pos);
            CharSequence* seq = element->f_sequence;

            ValueHolder* last = nullptr;
            int last_priority = 11;

            while(seq->type != CharSequenceType::END){
                switch(seq->type){
                case CharSequenceType::OPERATOR:
                {
                    if (last){
                        if (seq->chars == "."){
                        //TODO member call
                        return nullptr;
                        }
                        if (seq->chars == "::"){
                        //TODO static member call
                        return nullptr;
                        }
                        if (seq->chars == "="){
                            //TODO assign operation
                            return nullptr;
                        }
                        int current_priority = operation::operatorPriority(seq->chars);
                        if (current_priority > previous_priority){
                            if (current_priority > last_priority){
                                CB998::throwError(seq, text->f_interface);
                                return nullptr;
                            }
                            if (current_priority == 10){ //value++
                                last_priority = 10;
                                last = new FunctionCallOperation(last, seq->chars, std::vector<ValueHolder*>());
                                break;
                            }
                            ValueHolder* source = buildValueHolder(scope, text, read_pos, current_priority);
                            last = new FunctionCallOperation(last, seq->chars, std::vector<ValueHolder*>({source}));
                            last_priority = current_priority;
                            break;
                        }else{
                            --(*read_pos);
                            return last;
                        }
                    }else{
                        if (seq->chars != "++" && seq->chars != "--" && seq->chars != "!"){
                            CB999::throwError(seq, text->f_interface);
                            return nullptr;
                        }
                        ValueHolder* target = buildValueHolder(scope, text, read_pos, 11);
                        last_priority = 11;
                        last = new FunctionCallOperation(target, seq->chars + "x", std::vector<ValueHolder*>());
                        break;
                    }
                }
                case CharSequenceType::NAME:
                {
                    if (last){
                        CB999::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    last = new PendingDeclaration(seq->chars);
                    break;
                }
                case CharSequenceType::BRACKET:
                {
                    if (last || element->elementType() != ElementType::BRACKET || ((SequenceBracket*)element)->f_btype != BracketListType::SINGLE){
                        CB999::throwError(seq, text->f_interface);
                        return nullptr;
                    }
                    SequenceLine* temp = text->f_current_target;
                    size_t temp_read_pos = 0;
                    text->f_current_target = ((SequenceBracket*)element)->f_contents.front();
                    last = buildValueHolder(scope, text, &temp_read_pos);
                    text->f_current_target = temp;
                    if (last->f_vhtype == ValueHolderType::DECLARATION){
                        element = temp->read(read_pos);
                        seq = element->f_sequence;
                        switch(seq->type){
                            case CharSequenceType::BRACKET:
                            {
                                if (element->elementType() != ElementType::BRACKET || ((SequenceBracket*)element)->f_btype != BracketListType::SINGLE){
                                    CB999::throwError(seq, text->f_interface);
                                    return nullptr;
                                }
                                temp = text->f_current_target;
                                temp_read_pos = 0;
                                text->f_current_target = ((SequenceBracket*)element)->f_contents.front();
                                ValueHolder* cast_target = buildValueHolder(scope, text, &temp_read_pos);
                                text->f_current_target = temp;
                                last = new CastingOperation(cast_target, (PendingDeclaration*)last);
                                break;
                            }
                            case CharSequenceType::OPERATOR:
                            {
                                bool result = false; //false = not casting
                                size_t fake_read_pos = *read_pos;
                                CharSequence* outlook = temp->read(&fake_read_pos)->f_sequence;
                                while (outlook->type != CharSequenceType::END){
                                    switch(outlook->type){
                                        case CharSequenceType::OPERATOR:
                                        {
                                            if (outlook->chars == "++" || outlook->chars == "--"){
                                                break;
                                            }
                                            if (outlook->chars == "!"){ //TODO add ~ operator
                                                goto break_loop;
                                            }
                                            result = true;
                                        }
                                        case CharSequenceType::NAME:
                                        case CharSequenceType::BRACKET:
                                        {
                                            goto break_loop;
                                        }
                                    }
                                    outlook = temp->read(&fake_read_pos)->f_sequence;
                                }
                                break_loop:
                                if (result){
                                    ValueHolder* cast_target = buildValueHolder(scope, text, read_pos);
                                    last = new CastingOperation(cast_target, (PendingDeclaration*)last);
                                }
                                break;
                            }
                            case CharSequenceType::NAME:
                            {
                                --(*read_pos);
                                ValueHolder* cast_target = buildValueHolder(scope, text, read_pos, 12);
                                last = new CastingOperation(cast_target, (PendingDeclaration*)last);
                                break;
                            }
                            default:
                            {
                                CB999::throwError(seq, text->f_interface);
                                return nullptr;
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    CB999::throwError(seq, text->f_interface);
                    return nullptr;
                }
                }
                element = text->f_current_target->read(read_pos);
                seq = element->f_sequence; 
            }
            if (!last){
                CB999::throwError(seq, text->f_interface);
            }
            return last;
        }

    }

    namespace operation{

        int operation::operatorPriority(std::string& operation){
            if (operation == "="){ //target = value returns target
                return 1;
            }
            if (operation == "||"){ //value1 || value2
                return 2;
            }
            if (operation == "&&"){//value1 && value2
                return 3;
            }
            if (operation == "|" || operation == "&" ||operation == "^"){//value1 | value2
                return 4;
            }
            if (operation == "==" || operation == "!="){//value1 == value2 returns bool
                return 5;
            }
            if (operation == "<" || operation == "<=" || operation == ">=" || operation == ">"){ // value1 < value2 returns bool
                return 6;
            }
            if (operation == "+" || operation == "-"){ //value1 + value2
                return 8;
            }
            if (operation == "*" || operation == "/"){ //value1 * value2
                return 9;
            }
            if (operation == "<<" || operation == ">>"){ //value1 << value2
                return 7;
            }
            if (operation == "++" || operation == "--"){ //value++
                return 10;
            }
            //++value technicaly 11
            //!value technicaly 11
            return 0;
        }

        /*Operation* operation::buildOperationStart(Scope* scope, Text* text, size_t* read_pos){
            //todo handle ++$, --$ operators$
            //todo handle single word inputs;
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
        }*/

    }


}