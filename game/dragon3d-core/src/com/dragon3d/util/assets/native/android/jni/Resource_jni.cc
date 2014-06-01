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

static AAssetManager* AAsetsMgr;

//Dragon Init
JNIEXPORT void JNICALL Java_com_dragon3d_util_assets_Resource_nativeSetAssetManager(JNIEnv * env, jobject assetManager) {
    AAsetsMgr = AAssetManager_fromJava(env, assetManager);
}

