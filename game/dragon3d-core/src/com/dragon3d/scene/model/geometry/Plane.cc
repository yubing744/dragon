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
 * Created:     2014/03/30
 **********************************************************************/


#include <com/dragon3d/scene/model/geometry/Plane.h>
#include <dragon/util/logging/Logger.h>

Import com::dragon3d::scene::model::geometry;
Import dragon::util::logging;

const Type* com::dragon3d::scene::model::geometry::Plane::TYPE = TypeOf<com::dragon3d::scene::model::geometry::Plane>();
static Logger* logger = Logger::getLogger(com::dragon3d::scene::model::geometry::Plane::TYPE, ERROR);

com::dragon3d::scene::model::geometry::Plane::Plane() {
    float cubeVerts[] =
    {
      -1.0f,  -1.0f, 1.0f,
      1.0f,  -1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      -1.0f,  1.0f, 1.0f,
       -1.0f,  -1.0f, 1.0f
   };

   float cubeNormals[] =
   {
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
   };

   float cubeTex[] =
   {
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,
      1.0f, 1.0f,
      0.0f, 1.0f,
      0.0f, 0.0f,
    };   

    unsigned short cubeIndices[] =
    {
        0, 1, 2,
        3, 4, 5
    };

    this->mesh = new Mesh();
    this->material = new Material(Color::GREEN);
    
    int numVertices = 6;
    int numIndices = 6;
    
    this->mesh->setFloatVertices(Array<float>(cubeVerts, numVertices * 3, false));
    this->mesh->setFloatNormals(Array<float>(cubeNormals, numVertices * 3, false));
    this->mesh->setFloatUVs(Array<float>(cubeTex, numVertices * 2, false));

    //Copy indices data
    int* triangles = new int[numIndices];

    for (int i=0; i<numIndices; i++) {
        triangles[i] = cubeIndices[i];
    }

    this->mesh->setTriangles(Array<int>(triangles, numIndices, false));
}

com::dragon3d::scene::model::geometry::Plane::~Plane() {

}