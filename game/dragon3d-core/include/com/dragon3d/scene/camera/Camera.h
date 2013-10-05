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

#include <com/dragon3d/util/math/Color.h>
#include <com/dragon3d/util/math/Rect.h>
#include <com/dragon3d/util/math/Ray3.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/math/Matrix4x4.h>
#include <com/dragon3d/scene/model/RenderTexture.h>
#include <com/dragon3d/scene/Behaviour.h>

BeginPackage4(com, dragon3d, scene, camera)

Import com::dragon3d::util::math;
Import com::dragon3d::scene;
Import com::dragon3d::scene::camera;
Import com::dragon3d::scene::model;

/**
 * A Camera is a device through which the player views the world.
 * 
 */
class _DragonExport Camera 
	extends(Behaviour) {
public:
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
public:
	Camera();
	virtual ~Camera();

public:
	/**
	 * Makes this camera's settings match other camera.
	 * 
	 * @param other [description]
	 */
	void copyFrom(Camera* other);

	/**
	 * Revert the aspect ratio to the screen's aspect ratio.
	 */
	void resetAspect();

	/**
	 * How tall is the camera in pixels (Read Only).
	 */
	float pixelHeight(); 

	/**
	 * How wide is the camera in pixels (Read Only).
	 */
	float pixelWidth(); 

	/**
	 * Make the projection reflect normal camera's parameters.
	 */
	void resetProjectionMatrix();

	/**
	 * Make the rendering position reflect the camera's position in the scene.
	 */
	void resetWorldToCameraMatrix();

	/**
	 * Returns a ray going from camera through a screen point.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	Ray3* screenPointToRay(Vector3 position);

	/**
	 * ransforms position from screen space into viewport space.
	 * Screenspace is defined in pixels. The bottom-left of the screen is (0,0); 
	 * the right-top is (pixelWidth,pixelHeight). The z position is in world 
	 * units from the camera.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	Vector3 screenToViewportPoint(Vector3 position);

	/**
	 * Transforms position from screen space into world space.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	Vector3 screenToWorldPoint(Vector3 position);

	/**
	 * Returns a ray going from camera through a viewport point.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	Ray3* viewportPointToRay(Vector3 position);

	/**
	 * Transforms position from viewport space into screen space.
	 * Viewport space is normalized and relative to the camera. The bottom-left of the camera is (0,0); 
	 * the top-right is (1,1). The z position is in world units from the camera.
	 * @param  position [description]
	 * @return          [description]
	 */
	Vector3 viewportToScreenPoint(Vector3 position);

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
	Vector3 viewportToWorldPoint(Vector3 position);

	/**
	 * Transforms position from world space into screen space.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	Vector3 worldToScreenPoint(Vector3 position);

	/**
	 * Transforms position from world space into viewport space.
	 * 
	 * @param  position [description]
	 * @return          [description]
	 */
	Vector3 worldToViewportPoint(Vector3 position);

public:
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

	/**
	 * The aspect ratio (width divided by height).
	 */
	float aspect; 

	/**
	 * The color with which the screen will be cleared.
	 */
	Color backgroundColor;

	/**
	 * Matrix that transforms from camera space to world space (Read Only)
	 */
	Matrix4x4 cameraToWorldMatrix;

	/**
	 * How the camera clears the background.
	 */
	CameraClearFlags clearFlags;

	/**
	 * This is used to render parts of the scene selectively.
	 */
	int cullingMask; 

	/**
	 * Camera's depth in the camera rendering order.
	 */
	float depth; 

	/**
	 * How and if camera generates a depth texture.
	 */
	DepthTextureMode depthTextureMode;

	/**
	 * Mask to select which layers can trigger events on the camera.
	 */
	int eventMask;

	/**
	 * The near clipping plane distance.
	 */
	float nearClipPlane;

	/**
	 * The far clipping plane distance.
	 */
	float farClipPlane;

	/**
	 * The field of view of the camera in degrees.
	 */
	float fieldOfView;

	/**
	 * High dynamic range rendering.
	 */
	bool hdr;

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
	 * Where on the screen is the camera rendered in pixel coordinates.
	 */
	Rect pixelRect;

	/**
	 * Set a custom projection matrix.
	 */
	Matrix4x4 projectionMatrix;

	/**
	 * Where on the screen is the camera rendered in normalized coordinates.
	 */
	Rect rect;

	/**
	 * Rendering path.
	 */
	RenderingPath renderingPath;

	/**
	 * Whether or not the Camera will use occlusion culling during rendering.
	 */
	bool useOcclusionCulling;

	/**
	 * Get the world-space speed of the camera (Read Only).
	 */
	Vector3 velocity; 

	/**
	 * Destination render texture.
	 * 
	 */
	RenderTexture* targetTexture;

};//Camera

EndPackage4 //(com, dragon3d, scene, camera)

#endif //Camera_Camera_Scene_Dragon3d_Com_H
