/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/21
 **********************************************************************/

#ifndef Stack_Util_Dragon_H
#define Stack_Util_Dragon_H

#include "ArrayList.h"

BeginPackage2(dragon, util)

template<class E>
class Stack extends(ArrayList<E>)
{
public:
	Stack(){};
	virtual ~Stack(){};

public:
	virtual E* push(E* e);
	virtual E* pop();
	virtual E* peek();
	virtual bool empty();
	virtual int search(E* e);
};

//Implements Stack Interface

template<class E>
E* Stack<E>::push(E* e) {
	this->add(e);
	return e;
}

template<class E>
E* Stack<E>::pop() {
	int size = this->size();
	E* e = this->get(size - 1);
	this->remove(e);
	return e;
}

template<class E>
E* Stack<E>::peek() {
	int size = this->size();
	return this->get(size - 1);
}

template<class E>
bool Stack<E>::empty() {
	return this->isEmpty();
}

template<class E>
int Stack<E>::search(E* e) {
	Iterator<E>* it = this->iterator();
	
	int index=0;

	while(it->hasNext()) {
		index++;

		if(it->next() == e){
			break;
		}
	}

	SafeDelete(it);

	return index;
}

EndPackage2 //(dragon, util)

#endif //Stack_Util_Dragon_H