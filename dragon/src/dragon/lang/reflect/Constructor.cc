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
 * Created:     2013/07/25
 **********************************************************************/


#include <dragon/lang/reflect/Constructor.h>
#include <dragon/lang/internal/platform.h>

Import dragon::lang::reflect;
Import dragon::lang::internal;

typedef void (DRAGON_THISCALL *FnConstructor)(void* pThis);

Constructor::Constructor(const Class* clazz, const char* name, 
	void* procAddress, const Array<Type*>& parameterTypes) 
	:Member(clazz, name), procAddress(procAddress), parameterTypes(parameterTypes)  {
	//Nothing
}

Constructor::~Constructor() {

}

void* Constructor::newInstance() {
	void* class_mem = malloc(1024);
	void* self = Invoke<void*>(class_mem, this->procAddress);
	return self;
}

void* Constructor::newInstance(const Array<Object*>& args) {
	void* pThis = malloc(1024);

	Array<Type*> tps = this->parameterTypes;
	Array<Object*> args_in = args;

	void* ret = NULL;

	if (tps.size() == args_in.size()) {
		int argc = args_in.size();
		
		if (argc > 0) {
			ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * argc);

			for (int i = 0; i < argc; ++i) {
				Type* type = tps[i];
				void* obj = args_in[i];

				params[i] = ParamInfo(obj);
			}

			ret = Invoke(pThis, this->procAddress, params, argc);

			SafeDeleteArray(params);
		} else {
			ret = Invoke<void*>(pThis, this->procAddress);
		}
	}

	return ret;
}

const Array<Type*> Constructor::getParameterTypes() {
	return this->parameterTypes;
}
