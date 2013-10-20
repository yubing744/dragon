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

// Implements AppLauncher 
#include <jni.h>
#include <android/log.h>

#include <assert.h>
#include <jni.h>
#include <string.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <com/dragon3d/launcher/AppLauncher.h>

#include <com/dragon3d/framework/Application.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::framework;
Import com::dragon3d::input;
Import com::dragon3d::output;
Import com::dragon3d::output::graphics;

static Logger* logger = Logger::getLogger("com::dragon3d::launcher::AppLauncher#android", INFO);

static Application* _app = null;
static GraphicsDevice* graphicsDevice = null;

void Dragon3DLaunchApp(Application* app) {
    logger->info("launch app");

    // input
    InputManager* inputManager = new InputManager(); 
    app->setInputManager(inputManager);

    // ouput
    OutputManager* outputManager = new OutputManager();

    {
        // add graphics device
        graphicsDevice = new GraphicsDevice();
        outputManager->registerDevice(graphicsDevice);
    }

    app->setOutputManager(outputManager);

    _app = app;
}

/**
 * terminate a app.
 * 
 * @param app [description]
 */
void Dragon3DTerminateApp(Application* app) {
    logger->info("terminate app");

    if (app != null) {
        app->onStop();
    }
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_start(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resize(JNIEnv * env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_draw(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_pause(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resume(JNIEnv * env, jobject obj);
};

//Start Window
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_start(JNIEnv * env, jobject obj){
    logger->info("start");

    if (_app != null) {
        _app->onStart();
    }
}

//Screen Size changed
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resize(JNIEnv * env, jobject obj, jint width, jint height){
    logger->info("resize %d %d", width, height);
    
    graphicsDevice->width = width;
    graphicsDevice->height = height;
}

//Draw Frame
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_draw(JNIEnv * env, jobject obj){
    logger->debug("draw");

    if (_app != null) {
        _app->runLoop();
    }
}

//Pause
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_pause(JNIEnv * env, jobject obj){
    logger->info("pause");

    if (_app != null) {
        _app->onPause();
    }
}

//Resume
JNIEXPORT void JNICALL Java_com_yubing_dragongame_DGAndroidPlatfom_resume(JNIEnv * env, jobject obj){
    logger->info("resume");

    if (_app != null) {
        _app->onResume();
    }
}
