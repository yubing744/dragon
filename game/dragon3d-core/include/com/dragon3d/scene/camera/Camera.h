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


#ifndef Camera_Camera_Scene_Dragon3d_Com_H
#define Camera_Camera_Scene_Dragon3d_Com_H

#include <dragon/config.h>

#include <dragon/util/List.h>
#include <dragon/lang/reflect/Type.h>

#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Rect.h>
#include <com/dragon3d/util/math/Ray3.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Matrix4x4.h>

#include <com/dragon3d/scene/Bounds.h>
#include <com/dragon3d/scene/texture/RenderTexture.h>
#include <com/dragon3d/scene/Behaviour.h>

#include <com/dragon3d/framework/Scene.h>

#include <com/dragon3d/scene/camera/Frustum.h>

BeginPackage4(com, dragon3d, scene, camera)

Import dragon::util;
Import dragon::lang::reflect;

Import com::dragon3d::framework;
Import com::dragon3d::scene;
Import com::dragon3d::scene::camera;
Import com::dragon3d::scene::texture;
Import com::dragon3d::util::math;

/**
 * Values for Camera.clearFlags, determining what to clear when rendering a Camera.
 */
enum CameraClearFlags {  
	Skybox, //Clear with the skybox.
	SolidColor, //Clear with a background color.
	DepthBuffer, //Clear only the depth buffer.
	Nothing //Don't clear anything.
};

/**
 * Depth texture generation mode for Camera.
 */
enum DepthTextureMode {
	None, //Do not generate depth texture (Default).
	DepthTexture, //Generate a depth texture.
	DepthNormals //Generate a depth + normals texture.
};

/**
 * Rendering path of a Camera.
 */
enum RenderingPath {
	UsePlayerSettings, //Use Player Settings.
	VertexLit, //Vertex Lit.
	Forward, //Forward Rendering.
	DeferredLighting //Deferred Lighting.
};

/**
 * Transparent object sorting mode of a Camera.
 *
 * By default, perspective cameras sort objects based on distance from camera position 
 * to the object center; and orthographic cameras sort based on distance along the view direction. 
 * If you're making a 2D game with a perspective camera, you might want to use 
 * TransparencySortMode.Orthographic sort mode so that objects are sorted based on distance along 
 * the camera's view.
 */
enum TransparencySortMode {
	Default, //Default sorting mode.
	Perspective, //Perspective sorting mode.
	Orthographic  //Orthographic sorting mode.
};

/**
 * the frustum intersect
 */
enum FrustumIntersect {
    /**
     * Object being compared to the frustum is completely outside of the frustum.
     */
    Outside,

    /**
     * Object being compared to the frustum is completely inside of the frustum.
     */
    Inside,

    /**
     * Object being compared to the frustum intersects one of the frustum planes and is thus both inside and outside
     * of the frustum.
     */
    Intersects
};

/**
 * A Camera is a device through which the player views the world.
 * 
 */
class _DragonExport Camera 
	extends(Behaviour) {
public:
	const static Type* TYPE;

public:
	Camera();
	Camera(int width, int height);
	virtual ~Camera();

public:
	virtual void init();
	virtual void update(Input* input, ReadOnlyTimer* timer);
	virtual void destroy();
	
public:
	/**
     * the component is type of type.
     * 
     * @param  type [description]
     * @return      [description]
     */
    virtual bool isTypeOf(const Type* type);

	/**
	 * Makes this camera's settings match other camera.
	 * 
	 * @param other [description]
	 */
	virtual void copyFrom(Camera* other);

	/**
	 * Revert the aspect ratio to the screen's aspect ratio.
	 */
	virtual void resetAspect();

	/**
	 * Make the projection reflect normal camera's parameters.
	 */
	virtual void resetProjectionMatrix();

	/**
	 * Make the rendering position reflect the camera's position in the scene.
	 */
	virtual void resetWorldToCameraMatrix();

	/**
	 * Returns a ray going from camera through a screen point.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Ray3* screenPointToRay(Vector3 position);

	/**
	 * ransforms position from screen space into viewport space.
	 * Screenspace is defined in pixels. The bottom-left of the screen is (0,0); 
	 * the right-top is (pixelWidth,pixelHeight). The z position is in world 
	 * units from the camera.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Vector3 screenToViewportPoint(Vector3 position);

	/**
	 * Transforms position from screen space into world space.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Vector3 screenToWorldPoint(Vector3 position);

	/**
	 * Returns a ray going from camera through a viewport point.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Ray3* viewportPointToRay(Vector3 position);

	/**
	 * Transforms position from viewport space into screen space.
	 * Viewport space is normalized and relative to the camera. The bottom-left of the camera is (0,0); 
	 * the top-right is (1,1). The z position is in world units from the camera.
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Vector3 viewportToScreenPoint(Vector3 position);

	/**
	 * Transforms position from viewport space into world space.
	 * 
	 * Viewport space is normalized and relative to the camera. The bottom-left of the camera is (0,0); the top-right is (1,1). 
	 * The z position is in world units from the camera.
	 *
	 * Note that it transforms a x-y screen position, into a x-y-z position in 3D space. 
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Vector3 viewportToWorldPoint(Vector3 position);

	/**
	 * Transforms position from world space into screen space.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Vector3 worldToScreenPoint(Vector3 position);

	/**
	 * Transforms position from world space into viewport space.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	virtual Vector3 worldToViewportPoint(Vector3 position);

public:
	/**
	 * A convenience method for auto-setting the frame based on a world position the user desires the camera to look at.
	 * It points the camera towards the given position using the difference between that position and the current camera
	 * location as a direction vector and the general worldUpVector to compute up and left camera vectors.
	 * 
	 * @param pos
	 *            where to look at in terms of world coordinates
	 * @param worldUpVector
	 *            a normalized vector indicating the up direction of the world. (often {@link Vector3#UNIT_Y} or
	 *            {@link Vector3#UNIT_Z})
	 */
	void lookAt(const Vector3& pos, const Vector3& worldUpVector);

	/**
	 * A convenience method for auto-setting the frame based on a world position the user desires the camera to look at.
	 * It points the camera towards the given position using the difference between that position and the current camera
	 * location as a direction vector and the general worldUpVector to compute up and left camera vectors.
	 * 
	 * @param x
	 *            where to look at in terms of world coordinates (x)
	 * @param y
	 *            where to look at in terms of world coordinates (y)
	 * @param z
	 *            where to look at in terms of world coordinates (z)
	 * @param worldUpVector
	 *            a normalized vector indicating the up direction of the world. (often {@link Vector3#UNIT_Y} or
	 *            {@link Vector3#UNIT_Z})
	 */
	void lookAt(float x, float y, float z, const Vector3& worldUpVector);

public:
	/**
	 * How tall is the camera in pixels (Read Only).
	 */
	virtual float pixelHeight(); 

	/**
	 * How wide is the camera in pixels (Read Only).
	 */
	virtual float pixelWidth(); 

	/**
	 * set the pixel rect
	 * @param rect [description]
	 */
	virtual void setPixelRect(const Rect& rect);

	/**
	 * set the pixel rect width.
	 * 
	 * @param width [description]
	 */
	virtual void setPixelWidth(float width);

	/**
	 * set the pixel rect height.
	 * 
	 * @param height [description]
	 */
	virtual void setPixelHeight(float height);

	/**
	 * Resizes this camera's view with the given width and height.
	 * 
	 * @param width  [description]
	 * @param height [description]
	 */
	virtual void resize(float width, float height);

	/**
	 * set the rect.
	 * 
	 * @param rect [description]
	 */
	virtual void setRect(const Rect& rect);

	/**
	 * get the view port rect.
	 * 
	 * @return [description]
	 */
	virtual Rect getViewPortRect();

public:
	/**
	 * check if the camera contains bounds
	 * 
	 * @param  renderable [description]
	 * @return            [description]
	 */
	virtual FrustumIntersect contains(Bounds* bounds);

public: // get matrix
	virtual Matrix4x4 getModelViewMatrix();
	virtual Matrix4x4 getProjectionMatrix();
	virtual Matrix4x4 getModelViewProjectionMatrix();
	virtual Matrix4x4 getModelViewProjectionInverseMatrix();

protected:// update matrix
    virtual void checkModelView();
	virtual void checkProjection();
	virtual void checkModelViewProjection();
	virtual void checkInverseModelViewProjection();

	virtual void updateProjectionMatrix();
	virtual void updateModelViewMatrix();
	virtual void updateModelViewProjectionMatrix() ;
	virtual void updateInverseModelViewProjectionMatrix();

protected:
	/**
	 * Updates internal frustum coefficient values to reflect the current frustum plane values.
	 * 
	 * @return [description]
	 */
	virtual void onFrustumChange();

	/**
	 * Updates the values of view port.
	 */
	virtual void onViewPortChange();

	/**
	 * Updates the values of the world planes associated with this camera.
	 */
	virtual void onFrameChange();

protected://---------------------------------------------------------------------------
	/**
	 * Is the camera orthographic (true) or perspective (false)?
	 *
	 * When ortho is true, camera's viewing volume is defined by orthographicSize.
     * When orthographic is false, camera's viewing volume is defined by fieldOfView.
	 */
	bool orthographic;

	/**
	 * Camera's half-size when in orthographic mode.
	 *
	 * This is half of the vertical size of the viewing volume. Horizontal viewing size varies 
	 * depending on viewport's aspect ratio. Orthographic size is ignored when camera is not 
	 * orthographic (see orthographic). 
	 */
	float orthographicSize; 

protected:
	/**
	 * The color with which the screen will be cleared.
	 */
	Color backgroundColor;

	/**
	 * How the camera clears the background.
	 */
	CameraClearFlags clearFlags;

protected:
	/**
	 * This is used to render parts of the scene selectively.
	 */
	int cullingMask; 

	/**
	 * Mask to select which layers can trigger events on the camera.
	 */
	int eventMask;

protected:
	/**
	 * Camera's depth in the camera rendering order.
	 */
	float depth; 

	/**
	 * How and if camera generates a depth texture.
	 */
	DepthTextureMode depthTextureMode;

protected:
	/**
	 * High dynamic range rendering.
	 */
	bool hdr;

protected:
	/**
	 * Per-layer culling distances.
	 */
	float* layerCullDistances;

	/**
	 * layer culling count
	 */
	int layerCount;

	/**
	 * How to perform per-layer culling for a Camera.
	 */
	bool layerCullSpherical;

	/**
	 * Whether or not the Camera will use occlusion culling during rendering.
	 */
	bool useOcclusionCulling;


protected:
	/**
	 * Where on the screen is the camera rendered in pixel coordinates.
	 */
	Rect pixelRect;

	/**
	 * Where on the screen is the camera rendered in normalized coordinates.
	 */
	Rect rect;

protected:
	/**
	 * Rendering path.
	 */
	RenderingPath renderingPath;

	/**
	 * Destination render texture.
	 * 
	 */
	RenderTexture* targetTexture;

protected:
	/**
	 * Get the world-space speed of the camera (Read Only).
	 */
	Vector3 velocity; 

protected:
	/**
	 * The field of view of the camera in degrees.
	 */
	float fieldOfView;

	/**
	 * The aspect ratio (width divided by height).
	 */
	float aspect; 

	/**
	 * The near clipping plane distance.
	 */
	float nearClipPlane;

	/**
	 * The far clipping plane distance.
	 */
	float farClipPlane;

	/**
	 * the frustum.
	 */
	Frustum* frustum;

protected: // camare matrix
    bool updateMVMatrix;
    bool updatePMatrix;
   	bool updateMVPMatrix;
    bool updateInverseMVPMatrix;

	Matrix4x4 modelViewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 modelViewProjectionMatrix;
	Matrix4x4 modelViewProjectionInverseMatrix;

    bool depthRangeDirty;
    bool frustumDirty;
    bool viewPortDirty;
    bool frameDirty;
};//Camera

EndPackage4 //(com, dragon3d, scene, camera)

#endif //Camera_Camera_Scene_Dragon3d_Com_H
