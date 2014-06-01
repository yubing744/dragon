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
 * Created:     2014/02/15
 **********************************************************************/

#include <jni.h>
#include <android/log.h>

#include <assert.h>
#include <jni.h>
#include <string.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <com/dragon3d/util/assets/AssetsManager.h>

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

static jstring APPPATH = NULL;
static JavaVM* JAVAVM = NULL;

//Dragon Init
JNIEXPORT void JNICALL Java_com_dragon3d_util_assets_AssetsManager_nativeSetAppPath(JNIEnv * env, jobject* jstr) {
    APPPATH = *(jstring*)jstr;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JAVAVM = vm;
    return JNI_VERSION_1_4;
}

static bool getEnv(JNIEnv **env) {
    bool bRet = false;

    do {
        if (JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4) != JNI_OK) {
            LOGD("Failed to get the environment using GetEnv()");
            break;
        }

        if (JAVAVM->AttachCurrentThread(env, 0) < 0) {
            LOGD("Failed to get the environment using AttachCurrentThread()");
            break;
        }

        bRet = true;
    } while (0);        

    return bRet;
}

String* AssetsManager::getAppPath() {
    jstring jstr = APPPATH;
    if (jstr == NULL) {
        return null;
    }

    JNIEnv *env = 0;

    if (!getEnv(&env)) {
        return 0;
    }

    jboolean rtn = false;
    const char* chars = env->GetStringUTFChars(jstr, &rtn);
    int size = strlen(chars);
    String* ret = new String(Array<byte>(chars, size, false), 0, size, "UTF-8");
    env->ReleaseStringUTFChars(jstr, chars);

    return ret;
}