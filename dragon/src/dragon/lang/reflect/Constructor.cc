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
	Array<Type*> tps = this->parameterTypes;
	int p_size = tps.size();

	for (int i = 0; i < p_size; ++i) {
		Type* type = tps[i];
		SafeDelete(type);
	}

	//REDO tps.release();
}

bool is_primitive_type(const Type* type);
ParamInfo unpack_to_param_info(Object* obj);

Object* Constructor::newInstance(const Array<Object*>& args) {
	void* obj = malloc(1024);

	Array<Type*> tps = this->parameterTypes;
	Array<Object*> args_in = args;

	Object* ret = NULL;

	if (tps.size() == args_in.size()) {
		int argc = args_in.size();

		void* pthis = (void*)obj;

		if (argc > 0) {
			ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * argc);

			for (int i = 0; i < argc; ++i) {
				Type* type = tps[i];

				if (is_primitive_type(type)) {
					params[i] = unpack_to_param_info(args_in[i]);
				} else {
					params[i] = ParamInfo(type->getName(), (void*)args_in[i]);
				}
			}

			Invoke(pthis, this->procAddress, params, argc);

			SafeDeleteArray(params);
		} else {
			Invoke(pthis, this->procAddress, NULL, 0);
		}

		ret = (Object*)pthis;
	}

	return ret;
}

Object* Constructor::newInstance() {
	Array<Object*> empty_array;
	return this->newInstance(empty_array);
}

const Array<Type*> Constructor::getParameterTypes() {
	return this->parameterTypes;
}
