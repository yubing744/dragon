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
 * Created:     2013/09/28
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include <com/dragon3d/launcher/AppLauncher.h>
#include <com/dragon3d/examples/helloworld/HelloWorld.h>

Import com::dragon3d::examples::helloworld;

#pragma warning (disable: 4996)
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main(int argc, char *argv[]) {
	HelloWorld* helloworld = new HelloWorld();
    Dragon3DLaunchApp(helloworld);
	SafeDelete(helloworld);
}