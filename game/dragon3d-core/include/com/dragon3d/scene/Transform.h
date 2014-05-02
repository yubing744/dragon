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


#ifndef Transform_Scene_Dragon3d_Com_H
#define Transform_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/lang/String.h>
#include <dragon/util/List.h>
#include <com/dragon3d/scene/Component.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Quaternion.h>
#include <com/dragon3d/util/math/Matrix4x4.h>

BeginPackage3(com, dragon3d, scene)

Import dragon::lang;
Import dragon::util;
Import com::dragon3d::scene;
Import com::dragon3d::util::math;

/**
 * space
 */
enum Space {
    World,
    Self
};

/**
 * Position, rotation and scale of an object.
 */
class _DragonExport Transform
    extends(Component) {  
public:
    const static Type* TYPE;

public:
    Transform();
    virtual ~Transform();

public: //Property
    /**
     * position
     * 
     * @param p [description]
     */
    void setPosition(const Vector3& p);
    Vector3 getPosition();

    /**
     * rotation
     * 
     * @param r [description]
     */
    void setRotation(const Quaternion& r);
    Quaternion getRotation();

    /**
     * scale
     * 
     * @param scale [description]
     */
    void setScale(const Vector3& s);
    Vector3 getScale();

    /**
     * localPosition
     * 
     * @param p [description]
     */
    void setLocalPosition(const Vector3& p);
    Vector3 getLocalPosition();

    /**
     * localRotation
     * 
     * @param r [description]
     */
    void setLocalRotation(const Quaternion& r);
    Quaternion getLocalRotation();

    /**
     * localScale
     * 
     * @param localScale [description]
     */
    void setLocalScale(const Vector3& s);
    Vector3 getLocalScale();

    /**
     * The rotation as Euler angles in degrees.
     */
    Vector3 getEulerAngles();
    void setEulerAngles(const Vector3& angles);

    /**
     * The rotation as Euler angles in degrees relative to the parent transform's rotation.
     */
    Vector3 getLocalEulerAngles();
    void setLocalEulerAngles(const Vector3& angles);

    /**
     * Matrix that transforms a point from local space into world space
     */
    Matrix4x4 getWorldToLocalMatrix();
    void setWorldToLocalMatrix(const Matrix4x4& matrix);

    /**
     * Matrix that transforms a point from local space into world space
     */
    Matrix4x4 getLocalToWorldMatrix();   
    void setLocalToWorldMatrix(const Matrix4x4& matrix);

    /**
     * The parent of the transform.
     * 
     * @param parent [description]
     */
    void setParent(Transform* parent);
    Transform* getParent();

public:
    /**
     * Moves the transform in the direction and distance of translation.
     * 
     * @param translation [description]
     */
    void translate(const Vector3& translation);
    void translate(const Vector3& translation, Space relativeTo);

    /**
     * Applies a rotation of /eulerAngles.z/ degrees around the z axis, /eulerAngles.x/ degrees around the x axis, and /eulerAngles.y/ degrees around the y axis
     * 
     * @param eulerAngles [description]
     */
    void rotate(const Vector3& eulerAngles);
    void rotate(const Vector3& eulerAngles, Space relativeTo);

    /**
     * Applies a rotation of zAngle degrees around the z axis, xAngle degrees around the x axis, and yAngle degrees around the y axis (in that order).
     * 
     * @param xAngle [description]
     * @param yAngle [description]
     * @param zAngle [description]
     */
    void rotate(float xAngle, float yAngle, float zAngle);
    void rotate(float xAngle, float yAngle, float zAngle, Space relativeTo);

    /**
     * Returns the topmost transform in the hierarchy.
     * 
     * @return [description]
     */
    Transform* getRoot();

    /**
     * The green axis of the transform in world space.
     * 
     * @return [description]
     */
    Vector3 getUp();

    /**
     * The red axis of the transform in world space.
     * 
     * @return [description]
     */
    Vector3 getRight();

    /**
     * The blue axis of the transform in world space.
     * 
     * @return [description]
     */
    Vector3 getForward();

    /**
     * Unparents all children.
     * 
     */
    void detachChildren();

    /**
     * Returns a transform child by index.
     * 
     * @param  index [description]
     * @return       [description]
     */
    Transform* getChild(int index);

    /**
     * The number of children the Transform has.
     * 
     * @return [description]
     */
    int childCount();

    /**
     * Finds a child by name and returns it.
     * 
     * @param  name [description]
     * @return      [description]
     */
    Transform* find(const String& name);

    /**
     * Has the transform changed since the last time the flag was set to 'false'?
     * 
     * @return [description]
     */
    bool hasChanged();

protected:
    /**
     * find internal.
     * 
     * @param  path [description]
     * @return      [description]
     */
    Transform* internalRecursionFind(const String* path);

    /**
     * recalculate the matrix
     */
    void recalculatedMatrix();
    
protected:
    /**
     *  The parent of the transform.
     */
    Transform* parent;

    // transform in world space
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;

    // transform relative to the parent transform.
    Vector3 localPosition;
    Quaternion localRotation;
    Vector3 localScale;

    /**
     * Matrix that transforms a point from local space into world space 
     * and from world space to local space.
     * 
     */
    Matrix4x4 worldToLocalMatrix;
    Matrix4x4 localToWorldMatrix;

    /**
     * Has the transform changed since the last time the flag was set to 'false'?
     *
     * A change to the transform can be anything that causes its matrix to be recalculated: any adjustment to its position, rotation or scale.
     * 
     * @return [description]
     */
    bool changed;

    /**
     * the children Transform
     */
    List<Transform>* children;

};//Transform

EndPackage3 //(com, dragon3d, scene)

#endif //Transform_Scene_Dragon3d_Com_H
