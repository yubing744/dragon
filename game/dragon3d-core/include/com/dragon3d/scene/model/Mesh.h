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


#ifndef Mesh_Model_Scene_Dragon3d_Com_H
#define Mesh_Model_Scene_Dragon3d_Com_H

#include <dragon/config.h>

BeginPackage4(com, dragon3d, scene, model)

Import com::dragon3d::scene::model;

class _DragonExport Mesh {
public:
	Mesh();
	virtual ~Mesh();

public:
	
protected:
	
};//Mesh

EndPackage4 //(com, dragon3d, scene, model)

#endif //Mesh_Model_Scene_Dragon3d_Com_H

/*

#pragma once

#include "dg_config.h"

#if !defined(DG_MESH)
#define DG_MESH

#include "dg_vector2.h"
#include "dg_vector3.h"
#include "dg_matrix4x4.h"

#include <string>
using std::string;


class DGMesh
{
public:
	DGMesh(void);
	DGMesh(const char* name);
	virtual ~DGMesh(void);

public:
	DGVector3* vertices; //顶点的数据
    DGVector2* uv; //材质坐标数据
    DGVector2* uv2; //二级材质坐标数据
    DGVector3* normals; //法向量数据
	DGuint vertexCount; //网格顶点个数


    DGuint* indices; //索引数据
    DGuint indexCount; //索引个数

	DGMatrix4x4 matrix; //Transformation matrix for mesh data

private:
	string name;
};

#endif

 */