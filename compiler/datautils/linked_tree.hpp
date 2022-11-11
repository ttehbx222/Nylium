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
#include <vector>

template<class T>
class Node {
public:
	virtual ~Node() {}
	virtual std::map<T, Node<T>*>& map() = 0;
};

template <class T, class V>
class Tree : public Node<T>{
private:
	std::map<T, Node<T>*> next_by_value;
	std::vector<Node<T>*> owned;
	V& f_value;
public:
	Tree(V& value){
		this->value = value;
	}
	~Tree() {
		for (Node* node: owned) {
			delete node;
		}
	}
	template<class V2>
	Node<T>* add(T& key, V2& value) {
		Node<T>* node = new Tree<T, V2>(value);
		owned.push_back(node);
		next_by_value.insert(std::pair<T, Node<T>*>(key, node));
		return node;
	}
	void link(T& key, Node<T>* node) {
		next_by_value.insert(std::pair<T, Node<T>*>(key, node));
	}
	std::map<T, Node<T>*>& map() {
		return next_by_value;
	}
	inline V& value() { return f_value; }
};