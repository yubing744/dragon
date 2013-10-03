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


#ifndef InputManager_Input_Dragon3d_Com_H
#define InputManager_Input_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage3(com, dragon3d, input)

Import com::dragon3d::input;

class _DragonExport InputManager {
public:
	InputManager();
	virtual ~InputManager();

public:
	/**
	 * init input manager.
	 */
	virtual void init();
	
};//InputManager

EndPackage3 //(com, dragon3d, input)

#endif //InputManager_Input_Dragon3d_Com_H


/*

#pragma once

#include "dg_game.h"
#include "dg_game_object.h"
#include "dg_camera.h"
#include "dg_input.h"

#include <string>
#include <map>

using std::string;
using std::map;

#if !defined(DG_INPUT_MANAGER)
#define DG_INPUT_MANAGER

class DGInputManager
	:public DGInput
{
public:
	typedef struct _KeyMap {
		string axis;
		char primary;
		char secondary;
		string describe;

		_KeyMap(const char* axis, const char primary, const char* describe){
            this->axis = string(axis);
			this->primary = primary;
			this->describe = string(describe);
		};

        _KeyMap(const char* axis, const char primary, char secondary, const char* describe){
            this->axis = string(axis);
			this->primary = primary;
            this->secondary = secondary;
			this->describe = string(describe);
		};

	} KeyMap;

public:
	DGInputManager(void);

public:
	virtual ~DGInputManager(void);

public:
	void handleKeyDown(char keyCode);
	void handleKeyUp(char keyCode);

public:
	virtual DGboolean getKey(char keyCode);
	virtual void setKey(char keyCode, bool val);

	virtual DGboolean getAxis(const char* axis);

private:
	DGboolean keys[256];
	map<string, KeyMap*> axisMap;
};

#endif


 */