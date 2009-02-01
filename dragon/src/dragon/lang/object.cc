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
 * Created:     2013/03/31
 **********************************************************************/

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>
#include <dragon/lang/Class.h>

Import dragon::lang;

Object::Object()
{
	this->clazz = null;
}

Object::~Object()
{
	finalize();
}

Class<Object>* Object::getClass()
{
	if(this->clazz==null)
	{
		return new Class<Object>(&typeid(*this));
	}

	return this->clazz;
}

void Object::setClass(Class<Object>* clazz)
{
	this->clazz = clazz;
}

bool Object::equals(Object* obj)
{
	return false;
}

int Object::hashCode()
{
	return  (int)this;
}

String Object::toString()
{
	return String::format(L"@%d",this);
}

void Object::finalize() throw(Throwable)
{
	SafeDelete(this->clazz);
}