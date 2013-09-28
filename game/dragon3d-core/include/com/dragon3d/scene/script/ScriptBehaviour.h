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


#ifndef ScriptBehaviour_Script_Scene_Dragon3d_Com_H
#define ScriptBehaviour_Script_Scene_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, scene, script)

Import com::dragon3d::scene::script;

class _DragonExport ScriptBehaviour {
public:
	ScriptBehaviour();
	virtual ~ScriptBehaviour();

public:
	
protected:
	
};//ScriptBehaviour

EndPackage4 //(com, dragon3d, scene, script)

#endif //ScriptBehaviour_Script_Scene_Dragon3d_Com_H


/*

#pragma once

#include "dg_config.h"

#if !defined(DG_Script_Behaviour)
#define DG_Script_Behaviour

#include "dg_behaviour.h"

class DGScriptBehaviour
	:public DGBehaviour
{
public:
	DGScriptBehaviour(void);
	~DGScriptBehaviour(void);

public:
	virtual void init(DGGameObject* gameObject, DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
    virtual void start();

private:
	static DGLog* LOG;
};

#endif

 */