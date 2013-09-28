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


#ifndef Material_Model_Scene_Dragon3d_Com_H
#define Material_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, scene, model)

Import com::dragon3d::scene::model;

class _DragonExport Material {
public:
	Material();
	virtual ~Material();

public:
	
protected:
	
};//Material

EndPackage4 //(com, dragon3d, scene, model)

#endif //Material_Model_Scene_Dragon3d_Com_H

/*

#pragma once

#include "dg_game.h"
#include "dg_texture.h"

#if !defined(DG_MATERIAL)
#define DG_MATERIAL

#include <string>
using std::string;

class DGMaterial
{
public:
	DGMaterial(void);
	DGMaterial(const DGColor& color);
	DGMaterial(const DGColor& color, DGTexture* mainTexture);

	virtual ~DGMaterial(void);

public:
	string name;
	DGColor color;
	DGTexture* mainTexture;

public:
	const static DGMaterial DEFAULT_MATERIAL;
};

#endif

 */