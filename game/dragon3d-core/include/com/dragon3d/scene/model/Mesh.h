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
#include <dragon/util/List.h>

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
        String* materialName; //material
        MeshTopology topology; //the topology of a submesh.
        Array<int> indices; //An array containing all triangles in the mesh.
        int indexCount; //index count
    };

public:
    /**
     * vertices
     * 
     * @param vertices [description]
     */
    void setVertices(List<Vector3>* vertices);
    void setVertexArray(Array<Vector3> vertices);
    void setFloatVertices(Array<float> vertices);

    void appendVertices(List<Vector3>* vertices);
    void appendVertexArray(Array<Vector3> vertices);
    void appendFloatVertices(Array<float> vertices);

    List<Vector3>* getVertices();
    Array<Vector3> getVertexArray();
    Array<float> getFloatVertices();

    /**
     * uvs
     * 
     * @param uvs [description]
     */
    void setUVs(List<Vector2>* uvs);
    void setUVArray(Array<Vector2> uvs);
    void setFloatUVs(Array<float> uvs);

    void appendUVs(List<Vector2>* uvs);
    void appendUVArray(Array<Vector2> uvs);
    void appendFloatUVs(Array<float> uvs);

    List<Vector2>* getUVs();
    Array<Vector2> getUVArray();
    Array<float> getFloatUVs();

    /**
     * uv2s
     * 
     * @param uv2s [description]
     */
    void setUV2s(List<Vector2>* uv2s);
    void setUV2Array(Array<Vector2> uv2s);
    void setFloatUV2s(Array<float> uv2s);

    void appendUV2s(List<Vector2>* uv2s);
    void appendUV2Array(Array<Vector2> uv2s);
    void appendFloatUV2s(Array<float> uv2s);

    List<Vector2>* getUV2s();
    Array<Vector2> getUV2Array();
    Array<float> getFloatUV2s();

    /**
     * normals
     * 
     * @param normals [description]
     */
    void setNormals(List<Vector3>* normals);
    void setNormalArray(Array<Vector3> normals);
    void setFloatNormals(Array<float> normals);

    void appendNormals(List<Vector3>* normals);
    void appendNormalArray(Array<Vector3> normals);
    void appendFloatNormals(Array<float> normals);

    List<Vector3>* getNormals();
    Array<Vector3> getNormalArray();
    Array<float> getFloatNormals();

    /**
     * tangents
     * 
     * @param tangents [description]
     */
    void setTangents(List<Vector4>* tangents);
    void setTangentArray(Array<Vector4> tangents);
    void setFloatTangents(Array<float> tangents);

    void appendTangents(List<Vector4>* tangents);
    void appendTangentArray(Array<Vector4> tangents);
    void appendFloatTangents(Array<float> tangents);

    List<Vector4>* getTangents();
    Array<Vector4> getTangentArray();
    Array<float> getFloatTangents();

    /**
     * colors32
     * 
     * @param colors32 [description]
     */
    void setColors32(List<Color32>* colors32);
    void setColors32Array(Array<Color32> colors32);
    void setByteColors32(Array<byte> colors32);

    void appendColors32(List<Color32>* colors32);
    void appendColors32Array(Array<Color32> colors32);
    void appendByteColors32(Array<byte> colors32);

    List<Color32>* getColors32();
    Array<Color32> getColors32Array();
    Array<byte> getByteColors32();

    /**
     * colors
     * 
     * @param colors [description]
     */
    void setColors(List<Color>* colors);
    void setColorArray(Array<Color> colors);
    void setFloatColors(Array<float> colors);

    void appendColors(List<Color>* colors);
    void appendColorArray(Array<Color> colors);
    void appendFloatColors(Array<float> colors);

    List<Color>* getColors();
    Array<Color> getColorArray();
    Array<float> getFloatColors();

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
    void setTriangles(Array<int> triangles, int submesh);
    void setIndices(Array<int> indices, MeshTopology topology, int submesh);

    void appendTriangles(Array<int> triangles);
    void appendTriangles(Array<int> triangles, int submesh);
    void appendIndices(Array<int> indices, MeshTopology topology, int submesh);

    Array<int> getTriangles();
    Array<int> getIndices(int submesh);
    Array<unsigned short> getShortIndices(int submesh);

    /**
     * get material name by submesh index.
     * 
     * @param  submesh [description]
     * @return         [description]
     */
    String* getMaterialName(int submesh);

    /**
     * get vertex count
     * 
     * @return [description]
     */
    int getVertexCount();

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

    /**
     * check if has uv
     * 
     * @return [description]
     */
    bool hasUV();

    /**
     * check if has uv2
     * 
     * @return [description]
     */
    bool hasUV2();

    /**
     * check if has vertices
     * 
     * @return [description]
     */
    bool hasVertices();

protected:
    /**
     * get sub mesh data
     * 
     * @param  submesh [description]
     * @return         [description]
     */
    MeshData getSubMeshData(int submesh);

protected:
    Array<float> vertices; // Returns a copy of the vertex positions or assigns a new vertex positions array.
    int vertexCount; //Returns the number of vertices in the mesh (Read Only).

    Array<float> uv; //The base texture coordinates of the mesh.
    Array<float> uv2; //The second texture coordinate set of the mesh, if present.
    Array<float> normals; // The normals of the mesh.
    Array<float> tangents; // The tangents of the mesh.
    Array<float> colors; //Vertex colors of the mesh.
    Array<byte> colors32; //Vertex colors of the mesh.

    MeshData* subMeshs;
    int subMeshCount;
};//Mesh

EndPackage4 //(com, dragon3d, scene, model)

#endif //Mesh_Model_Scene_Dragon3d_Com_H
