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


#include <com/dragon3d/input/InputManager.h>

#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::input;

static Logger* logger = Logger::getLogger("com::dragon3d::input::InputManager", INFO);

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

void InputManager::init() {
	logger->info("init");
}

void InputManager::destroy() {
	logger->info("destroy");
}

int InputManager::queryStatus(Type* deviceType, int statusType) {
	return -1;
}

/*

#include "dg_input_manager.h"

DGInputManager::DGInputManager(void){
	//初始化键位
	int size = sizeof(this->keys);
	for(int i=0; i<size; i++) {
		this->keys[i] = false;
	}

	//添加行为映射
	axisMap["Forward"] = new KeyMap("Forward", 'W', "前进");
	axisMap["Back"] = new KeyMap("Back", 'S', "后退");
	axisMap["Right"] = new KeyMap("Right", 'D', "右转");
	axisMap["Left"] = new KeyMap("Left", 'A', "左转");
}


DGInputManager::~DGInputManager(void){
	map<string,KeyMap*>::iterator it;
    for(it=axisMap.begin();it!=axisMap.end();++it) {
		KeyMap* axisMap = it->second;
		if (axisMap) {
			delete axisMap;
			axisMap = NULL;
		}
	}
	axisMap.clear();
}

void DGInputManager::handleKeyDown(char keyCode){
	keys[keyCode] = DG_TRUE;
}

void DGInputManager::handleKeyUp(char keyCode){
	keys[keyCode] = DG_FALSE;
}


DGboolean DGInputManager::getKey(char keyCode){
	return keys[keyCode];
}

void DGInputManager::setKey(char keyCode, bool val){
	keys[keyCode] = val;
}

DGboolean DGInputManager::getAxis(const char* axis){
	map<string,KeyMap*>::iterator it = axisMap.find(axis);

	if (it!=axisMap.end()) {
		KeyMap* axisMap = it->second;
		if (axisMap && (keys[axisMap->primary] || keys[axisMap->secondary])) {
			return DG_TRUE;
		}
	}

	return DG_FALSE;
}

 */