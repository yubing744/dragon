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
