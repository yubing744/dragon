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

#include <com/dragon3d/util/math/Vector2.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Vector4.h>
#include <com/dragon3d/util/math/Color32.h>

#include <com/dragon3d/scene/model/Material.h>
 
BeginPackage4(com, dragon3d, scene, model)

Import com::dragon3d::util::math;
Import com::dragon3d::scene::model;

/**
 * A class that allows creating or modifying meshes from scripts.
 */
class _DragonExport Mesh {
public:
	Mesh();
	virtual ~Mesh();

public:
    /**
     * return the indices buffer of sub mesh
     * @param  submesh [description]
     * @return         [description]
     */
    int* getIndices(int submesh);

public:
    Vector3* vertices; // Returns a copy of the vertex positions or assigns a new vertex positions array.
    int vertexCount; //Returns the number of vertices in the mesh (Read Only).

    Vector2* uv; //The base texture coordinates of the mesh.
    Vector2* uv2; //The second texture coordinate set of the mesh, if present.
    Vector3* normals; // The normals of the mesh.
    Vector4* tangents; // The tangents of the mesh.
    Color32* colors; //Vertex colors of the mesh.

    int* triangles; //An array containing all triangles in the mesh.
    int triangleIndexCount; //index count

    int subMeshCount; //The number of submeshes. Every material has a separate triangle list.

};//Mesh

EndPackage4 //(com, dragon3d, scene, model)

#endif //Mesh_Model_Scene_Dragon3d_Com_H
