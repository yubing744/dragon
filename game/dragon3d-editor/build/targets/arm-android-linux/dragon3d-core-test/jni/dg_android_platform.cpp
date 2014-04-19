#include "dg_android_platform.h"
#include "dg_opengl_es_20_lib.h"
#include "dg_assert_resource.h"


DGAndroidPlatform::DGAndroidPlatform(JNIEnv * env, jobject platformObj, jobject assetManager){
	this->env = env;
	this->platformObj = platformObj;
	this->mgr = AAssetManager_fromJava(env, assetManager);
	
	DGPlatform::platform = this;
}

DGAndroidPlatform::~DGAndroidPlatform(void){
	//Release all DGLog
	map<string,DGLog*>::iterator it;
	
    for(it=logCache.begin();it!=logCache.end();++it) {
		DGLog* log = it->second;
		if (log) {
			dgDelete(log);
		}
	}
	
	logCache.clear();
}

void DGAndroidPlatform::setCallback(DGPlatformCallback* callback){
	this->callback = callback;
}

DGboolean DGAndroidPlatform::createWin(const char *title, DGuint width, DGuint height){
	// 1 Init Surface
	jclass objclass = env->GetObjectClass(platformObj);
	jmethodID methodId = env->GetMethodID(objclass, "createWin", "()V");
	env->CallObjectMethod(platformObj, methodId, NULL);
	
	// 2 Initialize OpenGL graphices library
	this->glib = new DGOpenGLES20Lib();
	
	return DG_TRUE;
}

void DGAndroidPlatform::showWin() {

}

DGGraphicsLib* DGAndroidPlatform::getGraphicsLib(){
	return this->glib;
}

DGLog* DGAndroidPlatform::getLogger(const char* tagName) {
	DGLog* log = NULL;
	
	map<string,DGLog*>::iterator it = logCache.find(tagName);
	if (it == logCache.end()) {
		log = new DGLog(tagName);
		logCache[tagName] = log;
	} else {
		log = it->second;
	}
	
	return log;
}

void DGAndroidPlatform::start(){
	if (callback) {
		callback->start();
	} 
}

void DGAndroidPlatform::draw(){
	if (callback) {
		callback->draw();
	}
}

void DGAndroidPlatform::resize(DGuint width, DGuint height){
	if (callback) {
		callback->resize(width, height);
	}
}

void DGAndroidPlatform::update(DGfloat deltaTime){
	if (callback) {
		callback->update(deltaTime);
	}
}

void DGAndroidPlatform::key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam){
	if (callback) {
		callback->key(charCode, pressed, wParam, lParam);
	}
}

DGResource* DGAndroidPlatform::openResource(const char* path){
	DGAssertResource* res = new DGAssertResource(this->mgr, path);
	if (res->open()) {
		return res;
	}

	return NULL;
}

void DGAndroidPlatform::closeResource(DGResource* resource){
	DGAssertResource* res = (DGAssertResource*)resource;
	if (res) {
		res->close();
	}
}

