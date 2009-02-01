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

#ifndef Throwable_Lang_H
#define Throwable_Lang_H

#include <dragon/config.h>

#include "Object.h"

BeginPackage2(dragon, lang)

class String;

class _DragonExport Throwable :public Object
{
public:
	Throwable();
	Throwable(const String& message);
	Throwable(Throwable* cause);
	Throwable(const String& message, Throwable* cause);
	virtual ~Throwable();

public:
	virtual String getMessage();
	virtual String getLocalizedMessage();
	virtual Throwable* getCause();
	virtual Throwable* initCause(Throwable* cause);
	virtual String toString();
	virtual void printStackTrace();

protected:
	String* message;
	Throwable* cause;
};

EndPackage2 // (dragon, lang)

#endif // Throwable_Lang_H