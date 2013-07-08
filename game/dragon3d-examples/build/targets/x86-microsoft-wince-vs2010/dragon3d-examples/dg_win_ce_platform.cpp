#include "dg_win_ce_platform.h"
#include "dg_opengl_es_20_lib.h"

DGWinCEPlatform::DGWinCEPlatform(void){
	DGPlatform::platform = this;
}

DGWinCEPlatform::~DGWinCEPlatform(void){

}

DGboolean DGWinCEPlatform::createGraphicsLib(){
   DGOpenGLES20Lib* glib = new DGOpenGLES20Lib();
   if (!glib->config(hWnd)){
	   return DG_FALSE;
   }

   this->glib = glib;

   return DG_TRUE;
}