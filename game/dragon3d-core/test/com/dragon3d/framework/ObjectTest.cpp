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
 * Created:     2013/07/02
 **********************************************************************/

#include <gtest/gtest.h>
 
#include <dragon3d-core.h>

#include <dragon/lang/String.h>
#include <com/dragon3d/framework/Object.h>

Import dragon::lang;
Import com::dragon3d::framework;

TEST(Com_Dragon3D_Framework_ObjectTest, New) {
	com::dragon3d::framework::Object* o = new com::dragon3d::framework::Object();
	SafeDelete(o);
}

TEST(Com_Dragon3D_Framework_ObjectTest, NewString) {
	String* o = new String();
	SafeDelete(o);
}