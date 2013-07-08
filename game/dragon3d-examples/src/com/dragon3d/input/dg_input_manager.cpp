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
