#include "dg_opengl_v15_lib.h"

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

#include "dg_texture.h"

DGOpenGLV15Lib::DGOpenGLV15Lib(void){

}

DGOpenGLV15Lib::~DGOpenGLV15Lib(void){

}


DGboolean DGOpenGLV15Lib::config(HWND hWnd){
	HDC			hDC=NULL;		// Private GDI Device Context
	HGLRC		hRC=NULL;		// Permanent Rendering Context
	GLuint		PixelFormat;
	int         bits = 16;

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
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

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	this->hDC = hDC;

	return DG_TRUE;
}

DGboolean DGOpenGLV15Lib::init(){
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading

	DGColor c("#474747");
	glClearColor(c.r, c.g, c.b, 0.5f);				    // Black Background

	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	return TRUE;										// Initialization Went OK
}

void DGOpenGLV15Lib::reset(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
}

void DGOpenGLV15Lib::setColor(const DGColor& c){
	glColor3f(c.r, c.g, c.b);
}

void DGOpenGLV15Lib::drawLine(const DGVector3& startV, const DGVector3& endV){
	glBegin(GL_LINES);
		glVertex3f(startV.x, startV.y, startV.z);
		glVertex3f(endV.x, endV.y, endV.z);
	glEnd();
}

void DGOpenGLV15Lib::drawMesh(DGMesh* mesh){
	DGuint vCount = mesh->indexCount;

	if (mesh->uv || mesh->uv2) {
		glEnable(GL_TEXTURE_2D);
	}

	glBegin(GL_TRIANGLES);

		for (DGuint i=0; i< vCount; i++) {
			DGuint pos = mesh->indices[i];

			//set texCoord
			if (mesh->uv) {
				DGVector2* uv = &mesh->uv[pos];
				glTexCoord2f(uv->x, uv->y);
			}

			//set vertext
			if (mesh->vertices) {
				DGVector3* v = &mesh->vertices[pos];
				glVertex3f(v->x, v->y, v->z);
			}
		}

	glEnd();

	if (mesh->uv || mesh->uv2) {
		glDisable(GL_TEXTURE_2D);
	}
}

void DGOpenGLV15Lib::viewport(DGint x, DGint y, DGsizei width, DGsizei height){
	glViewport(x, y, width, height);
}

void DGOpenGLV15Lib::perspective(DGfloat fovy, DGfloat aspect, DGfloat zNear, DGfloat zFar){
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluPerspective(fovy, aspect, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void DGOpenGLV15Lib::swapBuffers(){
	SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
}

void DGOpenGLV15Lib::translate(DGfloat x, DGfloat y, DGfloat z){
	glTranslatef(x, y, z);
}

void DGOpenGLV15Lib::rotate(DGfloat angle, DGfloat x, DGfloat y, DGfloat z){
	glRotatef(angle, x, y, z);
}

void DGOpenGLV15Lib::scale(DGfloat x, DGfloat y, DGfloat z){
	glScalef(x, y, z);
}

void DGOpenGLV15Lib::multMatrix(const DGMatrix4x4& matrix) {
	glMultMatrixf((DGfloat *)matrix.m);
}

void DGOpenGLV15Lib::pushMatrix(){
	glPushMatrix();
}

void DGOpenGLV15Lib::popMatrix(){
	glPopMatrix();
}

void DGOpenGLV15Lib::lookAt(DGfloat eyex, DGfloat eyey, DGfloat eyez, DGfloat centerx,
		  DGfloat centery, DGfloat centerz, DGfloat upx, DGfloat upy,
		  DGfloat upz) {
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void DGOpenGLV15Lib::initTexture(DGTexture* texture) {
	glGenTextures(1, &texture->nativeTextureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture->nativeTextureID);
	
	int textureType = GL_RGB;
	
	if(texture->channels == 4)
		textureType = GL_RGBA;
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, texture->channels, texture->width, 
		texture->height, textureType, GL_UNSIGNED_BYTE, texture->data);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);							
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


void DGOpenGLV15Lib::setTexture(DGTexture* texture){
	glBindTexture(GL_TEXTURE_2D, texture->nativeTextureID);
}

void DGOpenGLV15Lib::destroyTexture(DGTexture* texture){

}
