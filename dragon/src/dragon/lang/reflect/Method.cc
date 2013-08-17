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


#include <dragon/lang/reflect/Method.h>
#include <dragon/lang/internal/platform.h>
#include <dragon/lang/help_func.h>

#include <dragon/lang/Short.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Long.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/Double.h>

Import dragon::lang; 
Import dragon::lang::reflect; 
Import dragon::lang::internal; 

Method::Method(const Class* clazz, const char* name, 
	void* procAddress, const Array<Type*>& parameterTypes) 
	:Member(clazz, name), procAddress(procAddress), parameterTypes(parameterTypes)  {
	//Nothing
}

Method::~Method() {
	Array<Type*> tps = this->parameterTypes;
	int p_size = tps.size();

	for (int i = 0; i < p_size; ++i) {
		Type* type = tps[i];
		SafeDelete(type);
	}

	tps.release();
}

const Array<Type*> Method::getParameterTypes() {
	return this->parameterTypes;
}

//---------------------------------------------------------------
// invoke
// 
bool is_primitive_type(const Type* type) {
	const char* type_name = type->getName();

	return strcmp(type_name, "short") == 0x0
		|| strcmp(type_name, "int") == 0x0
		|| strcmp(type_name, "long") == 0x0
		|| strcmp(type_name, "float") == 0x0
		|| strcmp(type_name, "double") == 0x0
		|| strcmp(type_name, "bool") == 0x0
		|| strcmp(type_name, "char") == 0x0

		|| strcmp(type_name, "dg_short") == 0x0
		|| strcmp(type_name, "dg_int") == 0x0
		|| strcmp(type_name, "dg_long") == 0x0
		|| strcmp(type_name, "dg_float") == 0x0
		|| strcmp(type_name, "dg_double") == 0x0
		|| strcmp(type_name, "dg_bool") == 0x0
		|| strcmp(type_name, "dg_char") == 0x0;
}

ParamInfo unpack_to_param_info(Object* obj) {
	if (InstanceOf<Short>(obj)) {
		Short* number = dynamic_cast<Short*>(obj);
		return ParamInfo(number->shortValue());
	} else if (InstanceOf<Integer>(obj)) {
		Integer* number = dynamic_cast<Integer*>(obj);
		return ParamInfo(number->intValue());
	} else if (InstanceOf<Long>(obj)) {
		Long* number = dynamic_cast<Long*>(obj);
		return ParamInfo(number->longValue());
	} else if (InstanceOf<Float>(obj)) {
		Float* number = dynamic_cast<Float*>(obj);
		return ParamInfo(number->floatValue());
	} else if (InstanceOf<Double>(obj)) {
		Double* number = dynamic_cast<Double*>(obj);
		return ParamInfo(number->doubleValue());
	} else {
		return ParamInfo(obj);
	}
}

Object* pack_primitive_type(const Type* type, void* obj) {
	const char* type_name = type->getName();

	if (strcmp(type_name, "dg_short") == 0x0 
		|| strcmp(type_name, "short") == 0x0) {
		return new Short(void_cast<dg_short>(obj));
	} else if (strcmp(type_name, "dg_int") == 0x0 
		|| strcmp(type_name, "int") == 0x0) {
		return new Integer(void_cast<dg_int>(obj));
	} else if (strcmp(type_name, "dg_long") == 0x0 
		|| strcmp(type_name, "long") == 0x0) {
		return new Long(void_cast<dg_short>(obj));
	} else if (strcmp(type_name, "dg_float") == 0x0 
		|| strcmp(type_name, "float") == 0x0) {
		return new Float(void_cast<dg_short>(obj));
	} else if (strcmp(type_name, "dg_double") == 0x0 
		|| strcmp(type_name, "double") == 0x0) {
		return new Double(void_cast<dg_short>(obj));
	} else {
		return NULL;
	}
}

Object* Method::invoke(Object* obj, const Type* returnType, const Array<Object*>& args) {
	Array<Type*> tps = this->parameterTypes;
	Array<Object*> args_in = args;

	Object* ret = NULL;

	if (tps.size() == args_in.size()) {
		int argc = args_in.size();

		void* pthis = (void*)obj;
		ReturnInfo* retInfo = new ReturnInfo(returnType->getName());

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

			Invoke(pthis, this->procAddress, retInfo, params, argc);

			SafeFree(params);
		} else {
			Invoke(pthis, this->procAddress, retInfo, NULL, 0);
		}

		if (is_primitive_type(returnType)) {
			ret = pack_primitive_type(returnType, retInfo->value);
		} else {
			ret = (Object*)retInfo->value;
		}

		SafeDelete(retInfo);
	}

	return ret;
}

Object* Method::invoke(Object* obj, const Type* returnType) {
	Array<Object*> empty_array;
	return this->invoke(obj, returnType, empty_array);
}
