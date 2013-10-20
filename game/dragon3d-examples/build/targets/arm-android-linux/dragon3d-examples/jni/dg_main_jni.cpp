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

#include <jni.h>

#include <com/dragon3d/launcher/AppLauncher.h>
#include <com/dragon3d/examples/helloworld/HelloWorld.h>

Import com::dragon3d::examples::helloworld;

extern "C" {
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonInit(JNIEnv * env, jobject obj, jobject platformObj, jobject assetManager);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonDestroy(JNIEnv * env, jobject obj);
};

static HelloWorld* helloworld = null;

//Dragon Init
JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonInit(JNIEnv * env, jobject obj, jobject platformObj, jobject assetManager) {
	helloworld = new HelloWorld();
    Dragon3DLaunchApp(helloworld);
}

//Dragon Destroy
JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonDestroy(JNIEnv * env, jobject obj) {
	Dragon3DTerminateApp(helloworld);
}
