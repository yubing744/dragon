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


#ifndef Light_Light_Scene_Dragon3d_Com_H
#define Light_Light_Scene_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, scene, light)

Import com::dragon3d::scene::light;

class _DragonExport Light {
public:
	Light();
	virtual ~Light();

public:
	
protected:
	
};//Light

EndPackage4 //(com, dragon3d, scene, light)

#endif //Light_Light_Scene_Dragon3d_Com_H

/*
 
#pragma once

#include "dg_game.h"
#include "dg_game_object.h"

#if !defined(DG_LIGHT)
#define DG_LIGHT

class DGLight : public DGGameObject
{
public:
	DGLight(void);
	virtual ~DGLight(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw();
	
private:
	BOOL light;
	BOOL lp;
	BOOL fp;
};

#endif

 */