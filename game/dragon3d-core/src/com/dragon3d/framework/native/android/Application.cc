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
 * Created:     2013/09/15
 **********************************************************************/


#include <dragon.h>

#include <dragon/lang/String.h>

#include <dragon/lang/Class.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Void.h>

#include <dragon/lang/internal/SystemClassLoader.h>
#include <dragon/lang/internal/platform.h>

#include <com/dragon3d/util/Timer.h>
#include <com/dragon3d/framework/native/android/Application.h>

Import dragon::lang;
Import dragon::lang::internal;

Import com::dragon3d::framework;

#include <stdio.h>
#include <stdlib.h>

/*
#include "dg_game.h"
#include "dg_engine.h"
#include "dg_android_platform.h"
#include "dg_opengl_es_20_lib.h"
#include "dg_application.h"
*/

#include <jni.h>
#include <android/log.h>

#include <assert.h>
#include <jni.h>
#include <string.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#define  LOG_TAG    "libgl2jni"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" {
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonInit(JNIEnv * env, jobject obj, jobject platformObj, jobject assetManager);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonDestroy(JNIEnv * env, jobject obj);

    JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_start(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resize(JNIEnv * env, jobject obj, jint width, jint height);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_draw(JNIEnv * env, jobject obj, jlong deltaTime);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_pause(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resume(JNIEnv * env, jobject obj);
};

/*
DGEngine* engine = NULL;
DGAndroidPlatform* platform = NULL;
DGApplication* app = NULL;

DGLog* LOG = new DGLog("dg_main_jni");
*/

Application* app = NULL;

//Dragon Init
JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonInit(JNIEnv * env, jobject obj, jobject platformObj, jobject assetManager) {
	/*
	LOG->info("init ...");

  	platform = new DGAndroidPlatform(env, platformObj, assetManager);
	engine = new DGEngine();
	app = new DGApplication();
	
	if (engine->init(platform, "Dragon Game Android", 480, 320)) {
		app->startup(engine);
		
		LOG->info("init ok.");
	}
	*/

	/*
	String* o = new String();
	SafeDelete(o);

	ClassLoader* loader = ClassLoader::getSystemClassLoader();
	Class* clazz = loader->loadClass("dragon::lang::internal::SymTestBean");
	Object* tb = clazz->newInstance();

	Array<Type*> types(1);
	types[0] = new Type("int");
	Method* setTestValMethod = clazz->getMethod("setTestVal", types);

	Array<Object*> args(1);
	args[0] = new Integer(888);
	setTestValMethod->invoke(tb, Void::TYPE, args);

	LOGD("%s", "tb->get");
	*/

	app = new Application();
	
	app->startup();
}

//Dragon Destroy
JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonDestroy(JNIEnv * env, jobject obj) {
	//LOG->info("destroyed"); 

	/*
	app->end(engine);
	
	dgDelete(app);
    dgDelete(engine);
	dgDelete(platform);
	
	dgDelete(LOG);
	*/

	SafeDelete(app);
}

//Start Window
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_start(JNIEnv * env, jobject obj){
	//LOG->info("start ..."); 
	//platform->start();
	//LOG->info("start ok."); 
}

//Screen Size changed
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resize(JNIEnv * env, jobject obj, jint width, jint height){
	//LOG->info("resize %d %d", width, height);
	//platform->resize(width, height);
}

//Draw Frame
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_draw(JNIEnv * env, jobject obj, jlong deltaTime){
	//LOG->debug("start draw");
	//platform->draw();
	//platform->update((float)(deltaTime)/1000.0f);
	//LOG->debug("end draw");
}

//Pause
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_pause(JNIEnv * env, jobject obj){
	//LOG->info("pause");
}

//Resume
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resume(JNIEnv * env, jobject obj){
	//LOG->info("resume");
}

