#include <stdlib.h>

#include "dg_game.h"
#include "dg_engine.h"
#include "dg_android_platform.h"
#include "dg_opengl_es_20_lib.h"
#include "dg_application.h"

#include "dg_android.h"

extern "C" {
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonInit(JNIEnv * env, jobject obj, jobject platformObj, jobject assetManager);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonDestroy(JNIEnv * env, jobject obj);

    JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_start(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resize(JNIEnv * env, jobject obj, jint width, jint height);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_draw(JNIEnv * env, jobject obj, jlong deltaTime);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_pause(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resume(JNIEnv * env, jobject obj);
};

DGEngine* engine = NULL;
DGAndroidPlatform* platform = NULL;
DGApplication* app = NULL;

DGLog* LOG = new DGLog("dg_main_jni");

//Dragon Init
JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonInit(JNIEnv * env, jobject obj, jobject platformObj, jobject assetManager) {
	LOG->info("init ...");

  	platform = new DGAndroidPlatform(env, platformObj, assetManager);
	engine = new DGEngine();
	app = new DGApplication();
	
	if (engine->init(platform, "Dragon Game Android", 480, 320)) {
		app->startup(engine);
		
		LOG->info("init ok.");
	}
}

//Dragon Destroy
JNIEXPORT void JNICALL Java_com_yubing_dragongame_MainActivity_dragonDestroy(JNIEnv * env, jobject obj) {
	LOG->info("destroyed"); 

	app->end(engine);
	
	dgDelete(app);
    dgDelete(engine);
	dgDelete(platform);
	
	dgDelete(LOG);
}

//Start Window
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_start(JNIEnv * env, jobject obj){
	LOG->info("start ..."); 
	platform->start();
	LOG->info("start ok."); 
}

//Screen Size changed
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resize(JNIEnv * env, jobject obj, jint width, jint height){
	LOG->info("resize %d %d", width, height);
	platform->resize(width, height);
}

//Draw Frame
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_draw(JNIEnv * env, jobject obj, jlong deltaTime){
	//LOG->debug("start draw");
	platform->draw();
	platform->update((float)(deltaTime)/1000.0f);
	//LOG->debug("end draw");
}

//Pause
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_pause(JNIEnv * env, jobject obj){
	LOG->info("pause");
}

//Resume
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resume(JNIEnv * env, jobject obj){
	LOG->info("resume");
}

