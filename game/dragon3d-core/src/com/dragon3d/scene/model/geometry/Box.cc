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
 * Created:     2013/10/04
 **********************************************************************/


#include <com/dragon3d/scene/model/geometry/Box.h>

#include <stdlib.h>
#include <string.h>

Import com::dragon3d::scene::model::geometry;

Box::Box() {

   
    float cubeVerts[] =
    {
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f, -0.5f,

      -0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,

      -0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f, 0.5f,
      -0.5f,  0.5f, 0.5f,
      0.5f,  0.5f, 0.5f, 
      0.5f, -0.5f, 0.5f,

      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
   };

   float cubeNormals[] =
   {
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
   };

   float cubeTex[] =
   {
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
      0.0f, 0.0f,
      0.0f, 1.0f,
      1.0f, 1.0f,
      1.0f, 0.0f,
    };

    unsigned short cubeIndices[] =
    {
        0, 2, 1,
        0, 3, 2, 
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11, 
        12, 15, 14,
        12, 14, 13, 
        16, 17, 18,
        16, 18, 19, 
        20, 23, 22,
        20, 22, 21
    };

    this->mesh = new Mesh();
    this->material = new Material(Color::GREEN);
    
    int numVertices = 24;
    int numIndices = 36;
    
    this->mesh->vertexCount = numVertices;

    //Copy vertices data
    this->mesh->vertices = new Vector3[numVertices];

    for (int i=0; i<numVertices; i++) {
        this->mesh->vertices[i].x = cubeVerts[i * 3];
        this->mesh->vertices[i].y = cubeVerts[i * 3 + 1];
        this->mesh->vertices[i].z = cubeVerts[i * 3 + 2];
    }

    //Copy normals data
    this->mesh->normals = new Vector3[numVertices];

    for (int i=0; i<numVertices; i++) {
        this->mesh->normals[i].x = cubeNormals[i * 3];
        this->mesh->normals[i].y = cubeNormals[i * 3 + 1];
        this->mesh->normals[i].z = cubeNormals[i * 3 + 2];
    }

    //Copy uv data
    this->mesh->uv = new Vector2[numVertices];

    for (int i=0; i<numVertices; i++) {
        this->mesh->uv[i].x = cubeTex[i * 2];
        this->mesh->uv[i].y = cubeTex[i * 2 + 1];
    }

    //Copy indices data
    int* triangles = new int[numIndices];

    for (int i=0; i<numIndices; i++) {
        triangles[i] = cubeIndices[i];
    }

    this->mesh->setTriangles(Array<int>(triangles, numIndices, false));
}

Box::~Box() {

}