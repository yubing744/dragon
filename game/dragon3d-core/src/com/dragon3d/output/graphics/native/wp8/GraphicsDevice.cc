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

#include <com/dragon3d/output/graphics/GraphicsDevice.h>

#include <dragon/util/logging/Logger.h>

Import com::dragon3d::output::graphics;
Import dragon::util::logging;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::GraphicsDevice#win32", INFO);

// mine thread handle
typedef struct {
	HWND hWnd;
	HDC	hDC;
    int width;
    int height;
} NativeData;


///
//  ESWindowProc()
//
//      Main window procedure
//
LRESULT WINAPI GraphicsDeviceWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   LRESULT  lRet = 1; 

   switch (uMsg) 
   { 
      case WM_CREATE:
         break;

      case WM_DESTROY:
         PostQuitMessage(0);             
         break; 
	case WM_KEYDOWN:							// Is A Key Being Held Down?
		 {
            POINT      point;

            /*
            DGWinPlatform* winPlatform = (DGWinPlatform*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
            
            GetCursorPos(&point);

            if (winPlatform) {
	            winPlatform->key((unsigned char) wParam, DG_TRUE,
		                             (int) point.x, (int) point.y );
			}
			*/
		 }
		 break;
	case WM_KEYUP:								// Has A Key Been Released?
		 {
            POINT      point;

            /*
            DGWinPlatform* winPlatform = (DGWinPlatform*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
            
            GetCursorPos(&point);

            if (winPlatform) {
	            winPlatform->key((unsigned char) wParam, DG_FALSE,
		                             (int) point.x, (int) point.y );
			}
			*/

		 }
		 break;
      case WM_SIZE:								// Resize The OpenGL Window
		{

            NativeData* data = (NativeData*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);

            if (data) {
	            data->width = LOWORD(lParam);
	            data->height = HIWORD(lParam);
			}

			return 0;								// Jump Back
		}
		break;
      default: 
         lRet = DefWindowProc(hWnd, uMsg, wParam, lParam); 
         break;
   } 

   return lRet; 
}

/**
 * Create a Win32 Window
 */
HWND GraphicsDeviceCreateWin(const wchar_t *title, int width, int height){
   // 1 Create Windows
   HWND     hWnd = NULL;
   WNDCLASS wndclass = {0}; 
   DWORD    wStyle   = 0;
   RECT     windowRect;
   HINSTANCE hInstance = GetModuleHandle(NULL);

   wndclass.style         = CS_OWNDC;
   wndclass.lpfnWndProc   = (WNDPROC)GraphicsDeviceWindowProc; 
   wndclass.hInstance     = hInstance; 
   wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); 
   wndclass.lpszClassName = L"dragon3d"; 

   if (!RegisterClass (&wndclass) ) 
      return FALSE; 

   wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;
   
   // Adjust the window rectangle so that the client area has
   // the correct number of pixels
   windowRect.left = 0;
   windowRect.top = 0;
   windowRect.right = width;
   windowRect.bottom = height;

   AdjustWindowRect (&windowRect, wStyle, FALSE);

   hWnd = CreateWindow(wndclass.lpszClassName,
                        title,
                        wStyle,
                        0,
                        0,
                        windowRect.right - windowRect.left,
                        windowRect.bottom - windowRect.top,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

   ShowWindow(hWnd, TRUE);



   return hWnd;
}

void GraphicsDevice::init() {
	logger->info("init");

	NativeData* data = new NativeData();

	int initWidth = 320;
	int initHeight = 480;

	HWND hWnd = GraphicsDeviceCreateWin(L"dragon3d", initWidth, initHeight);

	data->width = initWidth;
	data->height = initHeight;
	data->hWnd = hWnd;

	// Set the ESContext* to the GWL_USERDATA so that it is available to the 
    SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)(LONG_PTR)data);

    this->nativeData = data;

    // init the controller
    this->controller->init();
}

void GraphicsDevice::destroy() {
	logger->info("destroy");

	// init the controller
    this->controller->destroy();
}
