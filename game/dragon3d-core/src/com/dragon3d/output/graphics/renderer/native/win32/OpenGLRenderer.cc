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

#define NOMINMAX
#include <windows.h>

#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

#include <com/dragon3d/output/graphics/renderer/OpenGLRenderer.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>

#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::renderer::OpenGLRenderer#win32", INFO);

typedef struct {
	HWND hWnd;
	HDC	hDC;
    int width;
    int height;
} NativeData;

bool OpenGLRendererConfig(HWND hWnd, HDC* pHdc){
	HDC			hDC=NULL;		// Private GDI Device Context
	HGLRC		hRC=NULL;		// Permanent Rendering Context
	GLuint		PixelFormat;
	int         bits = 16;

	// pfd Tells Windows How We Want Things To Be
	static	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	// Did We Get A Device Context?
	if (!(hDC=GetDC(hWnd))) {
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	// Did Windows Find A Matching Pixel Format?
	if (!(PixelFormat=ChoosePixelFormat(hDC, &pfd))) {
		MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	// Are We Able To Set The Pixel Format?
	if(!SetPixelFormat(hDC,PixelFormat, &pfd)) {
		MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	// Are We Able To Get A Rendering Context?
	if (!(hRC=wglCreateContext(hDC))) {
		MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	// Try To Activate The Rendering Context
	if(!wglMakeCurrent(hDC, hRC)) {
		MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	*pHdc = hDC;

	return true;
}


void OpenGLRendererNativeInit(GraphicsDevice* graphicsDevice) {
	logger->debug("native init");

	NativeData* data = (NativeData*)graphicsDevice->getNativeData();

	if (!OpenGLRendererConfig(data->hWnd, &data->hDC)) {
		MessageBox(NULL, L"Config OpenGL fail!", L"ERROR", MB_OK|MB_ICONEXCLAMATION);
	}
}


void OpenGLRenderer::flushBuffer() {
    logger->debug("flush buffer");

    NativeData* data = (NativeData*)this->graphicsDevice->getNativeData();
    SwapBuffers(data->hDC); // Swap Buffers (Double Buffering)
}

// include commons
#include "../../OpenGLRenderer.cc"

