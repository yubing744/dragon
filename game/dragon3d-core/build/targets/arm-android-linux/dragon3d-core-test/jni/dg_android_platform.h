#pragma once

#include "dg_config.h"

#ifndef DG_ANDROID_PLATFORM
#define DG_ANDROID_PLATFORM

#include <string>
#include <map>

#include "dg_log.h"
#include "dg_android.h"
#include "dg_platform.h"
#include "dg_opengl_es_20_lib.h"

using std::map;

class DGAndroidPlatform
	:public DGPlatform
{
public:
	DGAndroidPlatform(JNIEnv * env, jobject platformObj, jobject assetManager);
	virtual ~DGAndroidPlatform(void);

public: // Implements Interface DGPlatform
	virtual void setCallback(DGPlatformCallback* callback);
	
	virtual DGboolean createWin(const char *title, DGuint width, DGuint height);
	virtual void showWin();
	
	virtual DGResource* openResource(const char* path);
	virtual void closeResource(DGResource* resource);
	
	virtual DGGraphicsLib* getGraphicsLib();
	virtual DGLog* getLogger(const char* tagName);
	
public:
	void start();
	void draw();
	void resize(DGuint width, DGuint height);
	void update(DGfloat deltaTime);
	void key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam);

private:
	DGOpenGLES20Lib* glib;
	DGPlatformCallback* callback;
	
	JNIEnv * env;
	AAssetManager* mgr;
	
	jobject platformObj;
	map<string, DGLog*> logCache;
};

#endif
