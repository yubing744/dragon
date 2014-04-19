#pragma once

#ifndef DG_ANDROID
#define DG_ANDROID

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

#endif