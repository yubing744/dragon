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

BeginPackage2(dragon, lang)

class _DragonExport System 
{
public:
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
};

EndPackage2//(dragon, lang)

#endif
