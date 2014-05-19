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
 * Created:     2014/05/01
 **********************************************************************/


#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/scene/camera/Frustum.h>

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::scene::camera;

const Type* Frustum::TYPE = TypeOf<Frustum>();
static Logger* logger = Logger::getLogger(Frustum::TYPE, INFO);

Frustum::Frustum() 
    :planes(FRUSTUM_PLANES) {
    for (int i=0; i<FRUSTUM_PLANES; i++) {
        this->planes[i] = new Plane();
    }
}

Frustum::~Frustum() {
    for (int i=0; i<FRUSTUM_PLANES; i++) {
        SafeRelease(this->planes[i]);
    }
}

void Frustum::update(float screenDepth, const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix) {
    float zMinimum, r;
    Matrix4x4 matrix;

    Matrix4x4 innnerProjection = projectionMatrix;
    
    // Calculate the minimum Z distance in the frustum.
    zMinimum = -innnerProjection.m[4][3] / innnerProjection.m[3][3];
    r = screenDepth / (screenDepth - zMinimum);
    innnerProjection.m[3][3] = r;
    innnerProjection.m[4][3] = -r * zMinimum;

    // Create the frustum matrix from the view matrix and updated projection matrix.
    matrix = Matrix4x4::multiply(viewMatrix, innnerProjection);

    // Calculate left plane of frustum.
    this->planes[LEFT_PLANE]->setNormalAndDistance(
        Vector3(
            matrix.m[1][4] + matrix.m[1][1],
            matrix.m[2][4] + matrix.m[2][1],
            matrix.m[3][4] + matrix.m[3][1]
        ),
        matrix.m[4][4] + matrix.m[4][1]
    );

    // Calculate right plane of frustum.
    this->planes[RIGHT_PLANE]->setNormalAndDistance(
        Vector3(
            matrix.m[1][4] + matrix.m[1][1],
            matrix.m[2][4] + matrix.m[2][1],
            matrix.m[3][4] + matrix.m[3][1]
        ),
        matrix.m[4][4] + matrix.m[4][1]
    );

    // Calculate bottom plane of frustum.
    this->planes[BOTTOM_PLANE]->setNormalAndDistance(
        Vector3(
            matrix.m[1][4] + matrix.m[1][2],
            matrix.m[2][4] + matrix.m[2][2],
            matrix.m[3][4] + matrix.m[3][2]
        ),
        matrix.m[4][4] + matrix.m[4][2]
    );

    // Calculate top plane of frustum.
    this->planes[TOP_PLANE]->setNormalAndDistance(
        Vector3(
            matrix.m[1][4] + matrix.m[1][2],
            matrix.m[2][4] + matrix.m[2][2],
            matrix.m[3][4] + matrix.m[3][2]
        ),
        matrix.m[4][4] + matrix.m[4][2]
    );

    // Calculate far plane of frustum.
    this->planes[FAR_PLANE]->setNormalAndDistance(
        Vector3(
            matrix.m[1][4] + matrix.m[1][3],
            matrix.m[2][4] + matrix.m[2][3],
            matrix.m[3][4] + matrix.m[3][3]
        ),
        matrix.m[4][4] + matrix.m[4][3]
    );

    // Calculate near plane of frustum.
    this->planes[NEAR_PLANE]->setNormalAndDistance(
        Vector3(
            matrix.m[1][4] + matrix.m[1][3],
            matrix.m[2][4] + matrix.m[2][3],
            matrix.m[3][4] + matrix.m[3][3]
        ),
        matrix.m[4][4] + matrix.m[4][3]
    );

    logger->info("the frustum update");
}

int Frustum::checkBounds(Bounds* bounds) {
    int c;
    int c2 = 0;

    const Array<Vector3> corners = bounds->getCorners();

    // Check if any of the 6 planes of the rectangle are inside the view frustum.
    for(int i=0; i<FRUSTUM_PLANES; i++) {
        Plane* plane = this->planes[i];

        c = 0;

        for (int j=0; j<corners.size(); j++) {
            Vector3 p = corners[i];

            float distance = plane->getDistanceToPoint(p);
            
            if(distance >= 0.0f) {
                c++;
            }
        }

        if(c == 0) {
           return -1;
        }

        if(c == 8) {
            c2++;
        }
    }

    return (c2 == 6) ? 1 : 0;
}
