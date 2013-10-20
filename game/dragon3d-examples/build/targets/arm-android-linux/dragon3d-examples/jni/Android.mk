# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)
ENGINE_INCLUDE_PATH := $(LOCAL_PATH)/../../../Include
ENGINE_SRC_PATH := ../../../Source

include $(CLEAR_VARS)

APP_STL := stlport_static
LOCAL_MODULE    := dg_main_jni
#LOCAL_CFLAGS    := -Werror
LOCAL_C_INCLUDES:= $(ENGINE_INCLUDE_PATH)
LOCAL_LDLIBS    := -llog -landroid -lGLESv2 -lEGL

LOCAL_SRC_FILES := dg_main_jni.cpp
	
include $(BUILD_SHARED_LIBRARY)                 
                                                