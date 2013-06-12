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

#include <dragon/lang/String.h>
#include <dragon/lang/Throwable.h>

Import dragon::lang;

Throwable::Throwable() {
	this->message = new String("");
	this->cause = null;
}

Throwable::Throwable(String* message){
	SafeDelete(this->message);
	this->message = new String(message);

	this->cause = null;
}

Throwable::Throwable(Throwable* cause){
	this->message = new String("");

	SafeDelete(this->cause);
	this->cause = cause;
}

Throwable::Throwable(String* message, Throwable* cause){
	SafeDelete(this->message);
	this->message = new String(message);

	SafeDelete(this->cause);
	this->cause = cause;
} 

Throwable::~Throwable(){
	SafeDelete(this->message);
	SafeDelete(this->cause);
}

String* Throwable::getMessage(){
	return new String(this->message);
}

String* Throwable::getLocalizedMessage(){
	return new String(this->message);
}

Throwable* Throwable::getCause(){
	return this->cause;
}

Throwable* Throwable::initCause(Throwable* cause)
{
	SafeDelete(this->cause);
	this->cause = cause;
	return cause;
}

String* Throwable::toString()
{
	return this->getMessage();
}

void Throwable::printStackTrace()
{

}