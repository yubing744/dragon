#include "dg_win_platform.h"
#include "dg_opengl_v15_lib.h"
#include "dg_file_resource.h"

#include <string.h>
using std::string;

DGWinPlatform::DGWinPlatform(void){
	this->hWnd = NULL;
	this->glib = NULL;
	DGPlatform::platform = this;
}

DGWinPlatform::~DGWinPlatform(void){
	dgDelete(this->glib);
}

///
//  ESWindowProc()
//
//      Main window procedure
//
LRESULT WINAPI ESWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
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
            DGWinPlatform* winPlatform = (DGWinPlatform*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
            
            GetCursorPos(&point);

            if (winPlatform) {
	            winPlatform->key((unsigned char) wParam, DG_TRUE,
		                             (int) point.x, (int) point.y );
			}
		 }
		 break;
	case WM_KEYUP:								// Has A Key Been Released?
		 {
            POINT      point;
            DGWinPlatform* winPlatform = (DGWinPlatform*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
            
            GetCursorPos(&point);

            if (winPlatform) {
	            winPlatform->key((unsigned char) wParam, DG_FALSE,
		                             (int) point.x, (int) point.y );
			}
		 }
		 break;
      case WM_SIZE:								// Resize The OpenGL Window
		{
            DGWinPlatform* winPlatform = (DGWinPlatform*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);

            if (winPlatform) {
	            winPlatform->resize(LOWORD(lParam),HIWORD(lParam));
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


///
//  winLoop()
//
//      Start main windows loop
//
void WinLoop(DGWinPlatform* winPlatform){
   MSG msg = { 0 };
   int done = 0;
   DWORD lastTime = GetTickCount();
   
   while (!done){
      int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);

      DWORD curTime = GetTickCount();
      float deltaTime = (float)( curTime - lastTime ) / 1000.0f;
      lastTime = curTime;

      if (gotMsg){
         if (msg.message==WM_QUIT){
             done = 1; 
         } else {
             TranslateMessage(&msg); 
             DispatchMessage(&msg); 
         }
      } else {
		  winPlatform->draw();
	  }

      winPlatform->update(deltaTime);
   }
}

DGboolean DGWinPlatform::createWin(const char *title, DGuint width, DGuint height){
   // 1 Create Windows
   HWND     hWnd = NULL;
   WNDCLASS wndclass = {0}; 
   DWORD    wStyle   = 0;
   RECT     windowRect;
   HINSTANCE hInstance = GetModuleHandle(NULL);


   wndclass.style         = CS_OWNDC;
   wndclass.lpfnWndProc   = (WNDPROC)ESWindowProc; 
   wndclass.hInstance     = hInstance; 
   wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); 
   wndclass.lpszClassName = "dragon_game_win"; 

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

   // Set the ESContext* to the GWL_USERDATA so that it is available to the 
   // ESWindowProc
   SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)(LONG_PTR)this);

   this->hWnd = hWnd;

   // 2 Initialize OpenGL graphices library
   if (!createGraphicsLib()) {
	   return DG_FALSE;
   }

   return DG_TRUE;
}

DGboolean DGWinPlatform::createGraphicsLib(){
   DGOpenGLV15Lib* glib = new DGOpenGLV15Lib();
   if (!glib->config(hWnd)){
	   return DG_FALSE;
   }

   this->glib = glib;

   return DG_TRUE;
}

DGGraphicsLib* DGWinPlatform::getGraphicsLib(){
	return this->glib;
}

DGLog* DGWinPlatform::getLogger(const char* tagName) {
	return new DGLog(tagName);
}

void DGWinPlatform::setCallback(DGPlatformCallback* callback) {
	this->callback = callback;
}

void DGWinPlatform::draw(){
	if (this->callback) {
		this->callback->draw();
		this->glib->swapBuffers();
	}
}

void DGWinPlatform::resize(DGuint width, DGuint height){
	if (this->callback) {
		this->callback->resize(width, height);
	}
}

void DGWinPlatform::update(DGfloat deltaTime){
	if (this->callback) {
		this->callback->update(deltaTime);
	}
}

void DGWinPlatform::key(DGubyte charCode, DGboolean pressed, DGuint wParam, DGuint lParam){
	if (this->callback) {
		this->callback->key(charCode, pressed, wParam, lParam);
	}
}

void DGWinPlatform::showWin(){
	WinLoop(this);
}


DGResource* DGWinPlatform::openResource(const char* path) {
	string basePath;
	basePath.append("Assets/").append(path);

	DGFileResource* res = new DGFileResource(basePath.data());
	if (res->open()) {
		return res;
	}

	return NULL;
}

void DGWinPlatform::closeResource(DGResource* resource){
	DGFileResource* res = (DGFileResource*)resource;
	if (res) {
		res->close();
	}
}
