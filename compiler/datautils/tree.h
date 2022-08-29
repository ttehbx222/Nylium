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
#include <map>

//gitignored

template <class T>
class Tree {
private:
	std::map<T, Tree<T>*> next_by_value;
public:
	Tree(){}
	Tree(Tree<T>& tree) {
		for (auto const& entry : tree.next_by_value) { //TODO prevent loops
			next_by_value.insert(std::pair<T, Tree<T>*>(entry->first, new Tree<T>(entry->second)));
		}
	}
	Tree(Tree<T>* tree) {
		own_value = tree->own_value;
		for (auto const& entry : tree->next_by_value) { //TODO prevent loops
			next_by_value.insert(std::pair<T, Tree<T>*>(entry->first, new Tree<T>(entry->second)));
		}
	}
	inline Tree<T>* next(T& value) {
		return next_by_value.at(value);
	}
	Tree<T>* add(T& value) {
		Tree<T>* node = new Tree<T>();
		next_by_value.insert(std::pair<T, Tree<T>*>(value, node));
		return node;
	}
	void addPtr(T& value, Tree<T>* ptr) {
		next_by_value.insert(std::pair<T, Tree<T>*>(value, ptr));
	}
	inline std::map<T, Tree<T>*>& map() {
		return next_by_value;
	}

};