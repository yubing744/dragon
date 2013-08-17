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

LOCAL_SRC_FILES := dg_android_log.cpp dg_android_platform.cpp dg_main_jni.cpp \
	dg_assert_resource.cpp                            \
	$(ENGINE_SRC_PATH)/dg_texture.cpp                 \
	$(ENGINE_SRC_PATH)/dg_material.cpp                \
	$(ENGINE_SRC_PATH)/dg_camera.cpp                  \
	$(ENGINE_SRC_PATH)/dg_first_person_controller.cpp \
	$(ENGINE_SRC_PATH)/dg_horizon_grid.cpp          \
	$(ENGINE_SRC_PATH)/dg_opengl_es_20_lib.cpp      \
    $(ENGINE_SRC_PATH)/dg_vector3.cpp               \
    $(ENGINE_SRC_PATH)/dg_vector2.cpp               \
    $(ENGINE_SRC_PATH)/dg_utils.cpp                 \
    $(ENGINE_SRC_PATH)/dg_transform.cpp             \
    $(ENGINE_SRC_PATH)/dg_screen.cpp                \
    $(ENGINE_SRC_PATH)/dg_scene.cpp                 \
    $(ENGINE_SRC_PATH)/dg_renderer.cpp              \
    $(ENGINE_SRC_PATH)/dg_quaternion.cpp            \
    $(ENGINE_SRC_PATH)/dg_platform_callback.cpp     \
    $(ENGINE_SRC_PATH)/dg_platform.cpp              \
    $(ENGINE_SRC_PATH)/dg_mesh_renderer.cpp         \
    $(ENGINE_SRC_PATH)/dg_mesh.cpp                  \
    $(ENGINE_SRC_PATH)/dg_matrix4x4.cpp             \
    $(ENGINE_SRC_PATH)/dg_mathf.cpp                 \
    $(ENGINE_SRC_PATH)/dg_input_manager.cpp         \
    $(ENGINE_SRC_PATH)/dg_input.cpp                 \
    $(ENGINE_SRC_PATH)/dg_graphics_lib.cpp          \
    $(ENGINE_SRC_PATH)/dg_game_object.cpp           \
    $(ENGINE_SRC_PATH)/dg_exception.cpp             \
    $(ENGINE_SRC_PATH)/dg_engine.cpp                \
    $(ENGINE_SRC_PATH)/dg_cuboid.cpp                \
    $(ENGINE_SRC_PATH)/dg_context.cpp               \
    $(ENGINE_SRC_PATH)/dg_component.cpp             \
    $(ENGINE_SRC_PATH)/dg_color.cpp                 \
    $(ENGINE_SRC_PATH)/dg_behaviour.cpp             \
    $(ENGINE_SRC_PATH)/dg_application.cpp           \
	
include $(BUILD_SHARED_LIBRARY)                 
                                                