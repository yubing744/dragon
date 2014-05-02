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

#ifndef System_Lang_Dragon_H
#define System_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/Array.h>

BeginPackage2(dragon, lang)

class String;

class _DragonExport System 
{
public:
	/**
	 * load library by modual inner address.
	 * 
	 * @param libpath [description]
	 */
	static void loadLibrary(void* address);

	/**
	 * load system library with libname.
	 * 
	 * @param libname [description]
	 */
	static void loadLibrary(const char* libname);


	/**
	 * get the current time with ms
	 * 
	 * @return [description]
	 */
	static dg_long currentTimeMillis();

	/**
	 * get precision system time
	 * 
	 * @return [description]
	 */
	static dg_long nanoTime();

	/**
	 * exit app
	 * 
	 * @param code [description]
	 */
	static void exit(int code);

	/**
	 * get sys property.
	 * 
	 * @param  name [description]
	 * @return      [description]
	 */
	static const String* getProperty(const char* name);

	/**
	 * copy array data
	 * 
	 * @param  name [description]
	 * @return      [description]
	 */
	static native void arraycopy(const byte* src, int srcPos,
                                        const byte* dest, int destPos,
                                        int length);

	/**
	 * copy array data
	 * 
	 * @param  name [description]
	 * @return      [description]
	 */
	static native void arraycopy(const Array<byte> src, int srcPos,
                                        const Array<byte> dest, int destPos,
                                        int length);
};

EndPackage2//(dragon, lang)

#endif
