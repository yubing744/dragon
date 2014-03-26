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
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>

#include <com/dragon3d/util/math/Vector2.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Vector4.h>
#include <com/dragon3d/util/math/Color32.h>

#include <com/dragon3d/scene/model/Material.h>
 
BeginPackage4(com, dragon3d, scene, model)

Import dragon::lang;

Import com::dragon3d::util::math;
Import com::dragon3d::scene::model;

/**
 * A class that allows creating or modifying meshes from scripts.
 */
class _DragonExport Mesh extends(Object) {
public:
	Mesh();
	virtual ~Mesh();

public:
    enum MeshTopology {
        Triangles, //Mesh is made from triangles.
        Quads, //Mesh is made from quads.
        Lines, //Mesh is made from lines.
        LineStrip, //Mesh is a line strip.
        Points  //Mesh is made from points.
    };

    struct MeshData {
        Material* material; //material
        MeshTopology topology; //the topology of a submesh.
        int* indices; //An array containing all triangles in the mesh.
        int indexCount; //index count
    };

public:
    /**
     * Sets the triangle list for the 0 submesh.
     *
     * A submesh is simply a separate triangle list. When the mesh renderer uses multiple materials, 
     * you should ensure that there are as many submeshes as materials.
     *
     * It is recommended to assign a the triangle array after assigning the vertex array in order to avoid out of bounds errors.
     * 
     * @param triangles [description]
     * @param submesh   [description]
     */
    void setTriangles(Array<int> triangles);

    /**
     * Sets the triangle list for the submesh.
     *
     * A submesh is simply a separate triangle list. When the mesh renderer uses multiple materials, 
     * you should ensure that there are as many submeshes as materials.
     *
     * It is recommended to assign a the triangle array after assigning the vertex array in order to avoid out of bounds errors.
     * 
     * @param triangles [description]
     * @param submesh   [description]
     */
    void setTriangles(Array<int> triangles, int submesh);

    /**
     * Sets the triangle list for the submesh.
     * 
     * Sets the index buffer for the submesh.
     * 
     * @param indices  [description]
     * @param topology [description]
     * @param submesh  [description]
     */
    void setIndices(Array<int> indices, MeshTopology topology, int submesh);

    /**
     * get triangles of submesh
     *
     * @param submesh  [description]
     */
    Array<int> getTriangles();

    /**
     * Returns the index buffer for the submesh.
     * 
     * @param  submesh [description]
     * @return         [description]
     */
    Array<int> getIndices(int submesh);

    /**
     * Returns the index buffer for the submesh.
     * 
     * @param  submesh [description]
     * @return         [description]
     */
    Array<unsigned short> getShortIndices(int submesh);

    /**
     * Clears all vertex data and all triangle indices.
     * 
     */
    void clear();

    /**
     * [getSubMeshCount description]
     * @return [description]
     */
    int getSubMeshCount();

protected:
    MeshData getSubMeshData(int submesh);

public:
    Vector3* vertices; // Returns a copy of the vertex positions or assigns a new vertex positions array.
    int vertexCount; //Returns the number of vertices in the mesh (Read Only).

    Vector2* uv; //The base texture coordinates of the mesh.
    Vector2* uv2; //The second texture coordinate set of the mesh, if present.
    Vector3* normals; // The normals of the mesh.
    Vector4* tangents; // The tangents of the mesh.
    Color32* colors; //Vertex colors of the mesh.

protected:
    MeshData* subMeshs;
    int subMeshCount;
};//Mesh

EndPackage4 //(com, dragon3d, scene, model)

#endif //Mesh_Model_Scene_Dragon3d_Com_H
