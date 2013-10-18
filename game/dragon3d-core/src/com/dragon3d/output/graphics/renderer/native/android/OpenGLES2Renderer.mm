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

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <com/dragon3d/output/graphics/renderer/OpenGLES2Renderer.h>

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::renderer::OpenGLES2Renderer#android", INFO);

// include commons
#include "../../OpenGLES2Renderer.cc"

// native implements
void OpenGLES2Renderer::init() {
    EAGLContext* context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        
    if (!context || ![EAGLContext setCurrentContext:context]) {
        logger->error("init the EAGLContext fail!");
        return;
    }

    GLuint defaultFramebuffer, colorRenderbuffer;

    // Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
    glGenFramebuffers(1, &defaultFramebuffer);
    glGenRenderbuffers(1, &colorRenderbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
}



/*

#pragma once

#include "dg_config.h"

#ifndef DG_OPENGL_ES_20_LIB
#define DG_OPENGL_ES_20_LIB

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "dg_log.h"
#include "dg_platform.h"
#include "dg_vector3.h"
#include "dg_matrix4x4.h"
#include "dg_graphics_lib.h"

#define GL_MODELVIEW                  0x0001
#define GL_PROJECTION                 0x0002

#include <stack>
using std::stack;

class DGOpenGLES20Lib
  :public DGGraphicsLib
{
public:
  struct Context {
    GLuint programObject;

    // Matrix Stack
    DGMatrix4x4 mvpMatrix;
    DGMatrix4x4 modelViewMatrix;
    DGMatrix4x4 perspectiveMatrix;
    DGMatrix4x4* currentMatrix;
    
    // Sampler location
      GLint samplerLoc;

    // Color
    DGColor color;

    // Attribute locations
    GLint  mvpLoc;
      GLint  positionLoc;
      GLint  texCoordLoc;
    GLint  colorLoc;

    // Sampler locations
      GLint baseMapLoc;
      GLint lightMapLoc;

      // Texture handle
      GLuint baseMapTexId;
      GLuint lightMapTexId;

    // Matrix Stack
    stack<DGMatrix4x4> modelViewMatrixStack;
    stack<DGMatrix4x4> perspectiveMatrixStack;
    stack<DGMatrix4x4>* currentMatrixStack;
  };

public:
  DGOpenGLES20Lib();
  ~DGOpenGLES20Lib(void);

public: // Implements Interface DGGraphicsLib
  virtual void viewport(DGint x, DGint y, DGsizei width, DGsizei height);
    virtual void perspective(DGfloat fovy, DGfloat aspect, DGfloat zNear, DGfloat zFar);

  virtual DGboolean init();
  virtual void reset();
  virtual void setColor(const DGColor& color);
  virtual void drawLine(const DGVector3& startV, const DGVector3& endV);
  virtual void drawMesh(DGMesh* mesh);
  virtual void swapBuffers();

  virtual void translate(DGfloat x, DGfloat y, DGfloat z);
  virtual void rotate(DGfloat angle, DGfloat x, DGfloat y, DGfloat z);
  virtual void scale(DGfloat x, DGfloat y, DGfloat z);

  virtual void multMatrix(const DGMatrix4x4& matrix);
  virtual void pushMatrix();
  virtual void popMatrix();

  virtual void initTexture(DGTexture* texture);
  virtual void setTexture(DGTexture* texture);
  virtual void destroyTexture(DGTexture* texture);

public: // Implements OpenGL ES 1.1 Fixed Function Vertex Pipeline
  void matrixMode(GLenum mode);
  void loadIdentity();
  void frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
  void ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);

public: // Implements OpenGL glu Function
  virtual void lookAt(DGfloat eyex, DGfloat eyey, DGfloat eyez, DGfloat centerx,
    DGfloat centery, DGfloat centerz, DGfloat upx, DGfloat upy,
    DGfloat upz);



public:
  virtual DGboolean config(EGLNativeWindowType winType);
  virtual void makeMvpMatrix();

private:
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;

  Context ctx;

public:
  DGLog* log; //Out Variable
};

#endif

 */

/*

#include "dg_opengl_es_20_lib.h"

#include "dg_utils.h"
#include "dg_mathf.h"

#include "dg_texture.h"

#include <math.h>

/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1 
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2 
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8

#define TOLERANCE 0.0001

///
// CreateEGLContext()
//
//    Creates an EGL rendering context and all associated elements
//
EGLBoolean dgCreateEGLContext(EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
                              EGLContext* eglContext, EGLSurface* eglSurface,
                              EGLint attribList[])
{
   EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLDisplay display;
   EGLContext context;
   EGLSurface surface;
   EGLConfig config;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Get Display
   display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   if (display == EGL_NO_DISPLAY){
      return EGL_FALSE;
   }

   // Initialize EGL
   if (!eglInitialize(display, &majorVersion, &minorVersion)){
      return EGL_FALSE;
   }

   // Get configs
   if (!eglGetConfigs(display, NULL, 0, &numConfigs)){
      return EGL_FALSE;
   }

   // Choose config
   if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs)){
      return EGL_FALSE;
   }

   // Create a surface
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
   if (surface == EGL_NO_SURFACE){
      return EGL_FALSE;
   }

   // Create a GL context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
   if (context == EGL_NO_CONTEXT){
      return EGL_FALSE;
   }   
   
   // Make the context current
   if (!eglMakeCurrent(display, surface, surface, context)){
      return EGL_FALSE;
   }
   
   *eglDisplay = display;
   *eglSurface = surface;
   *eglContext = context;

   return EGL_TRUE;
} 

//
///
/// \brief Load a shader, check for compile errors, print error messages to output log
/// \param type Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
/// \param shaderSrc Shader source string
/// \return A new shader object on success, 0 on failure
//
GLuint dgLoadShader(GLenum type, const char *shaderSrc)
{
   GLuint shader;
   GLint compiled;
   
   // Create the shader object
   shader = glCreateShader ( type );

   if (shader == 0)
   	return 0;

   // Load the shader source
   glShaderSource(shader, 1, &shaderSrc, NULL);
   
   // Compile the shader
   glCompileShader(shader);

   // Check the compile status
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

   if (!compiled) {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      
      if (infoLen > 1){
         char* infoLog = (char*)malloc(sizeof(char) * infoLen );

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         dgLogMessage ( "Error compiling shader:\n%s\n", infoLog );            
         
         free(infoLog);
      }

      glDeleteShader(shader);

      return 0;
   }

   return shader;
}


//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
GLuint dgLoadProgram(const char *vertShaderSrc, const char *fragShaderSrc)
{
   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = dgLoadShader(GL_VERTEX_SHADER, vertShaderSrc);
   if ( vertexShader == 0 )
      return 0;

   fragmentShader = dgLoadShader(GL_FRAGMENT_SHADER, fragShaderSrc);
   if (fragmentShader == 0){
      glDeleteShader(vertexShader);
      return 0;
   }

   // Create the program object
   programObject = glCreateProgram();
   
   if (programObject == 0)
      return 0;

   glAttachShader(programObject, vertexShader);
   glAttachShader(programObject, fragmentShader);

   glBindAttribLocation(programObject, 0, "a_position" );
   glBindAttribLocation(programObject, 1, "a_texCoord" );

   // Link the program
   glLinkProgram(programObject);

   // Check the link status
   glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

   if (!linked){
      GLint infoLen = 0;

      glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
      
      if (infoLen > 1){
         char* infoLog = (char* )malloc (sizeof(char) * infoLen );

         glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
         dgLogMessage("Error linking program:\n%s\n", infoLog);            
         
         free(infoLog);
      }

      glDeleteProgram ( programObject );
      return 0;
   }

   // Free up no longer needed shader resources
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   return programObject;
}



DGOpenGLES20Lib::DGOpenGLES20Lib(){
   this->log = DGPlatform::getCurrent()->getLogger("dg_opengl_es_20_lib");
}

DGOpenGLES20Lib::~DGOpenGLES20Lib(void){

}

DGboolean DGOpenGLES20Lib::config(EGLNativeWindowType winType){
  GLuint flags = ES_WINDOW_RGB;

   EGLint attribList[] = {
       EGL_RED_SIZE,       5,
       EGL_GREEN_SIZE,     6,
       EGL_BLUE_SIZE,      5,
       EGL_ALPHA_SIZE,     (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
       EGL_DEPTH_SIZE,     (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
       EGL_STENCIL_SIZE,   (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
       EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
       EGL_NONE
   };
   
   if (!dgCreateEGLContext(winType,
                            &this->display,
                            &this->context,
                            &this->surface,
                            attribList)){
        return DG_FALSE;
   }

   return DG_TRUE;
}

/*
///
// Load texture from disk
//
GLuint dgLoadTexture ( char *fileName )
{
   int width,
       height;
   char *buffer = esLoadTGA ( fileName, &width, &height );
   GLuint texId;

   if ( buffer == NULL )
   {
      esLogMessage ( "Error loading (%s) image.\n", fileName );
      return 0;
   }

   glGenTextures ( 1, &texId );
   glBindTexture ( GL_TEXTURE_2D, texId );

   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

   free ( buffer );

   return texId;
}
*/

/*
DGboolean DGOpenGLES20Lib::init(){

	char vShaderStr[] =  
      "uniform mat4 mvp_matrix;                    \n"
      "attribute vec4 a_position;                  \n"
	  //"attribute vec4 a_color;                     \n"
	  //"varying vec4 v_out_color;                    \n"
	  "attribute vec2 a_texCoord;                  \n"
      "varying vec2 v_texCoord;                    \n"

      "void main()                                 \n"
      "{                                           \n"
	  //"   v_out_color = a_color;                   \n"
      "   gl_Position = mvp_matrix * a_position;   \n"
      "   v_texCoord = a_texCoord;                 \n"
      "}                                           \n";

   //gl_Position = u_mvpMatrix * a_position; 
    char fShaderStr[] =  
      "precision mediump float;                     \n"
	  //"varying vec4 v_out_color;                    \n"
	  "uniform vec4 u_color;                        \n"

      "varying vec2 v_texCoord;                     \n"
      "uniform sampler2D s_texture;                 \n"

      "void main()                                  \n"
      "{                                            \n"
      //"  gl_FragColor = u_color;                    \n"
	  //"  gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 ); \n"
	  "  gl_FragColor = u_color * texture2D( s_texture, v_texCoord);\n"
      "}                                            \n";

	/*
   char fShaderStr[] =  
      "precision mediump float;                            \n"
      "varying vec2 v_texCoord;                            \n"
      "uniform sampler2D s_baseMap;                        \n"
      "uniform sampler2D s_lightMap;                       \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  vec4 baseColor;                                   \n"
      "  vec4 lightColor;                                  \n"
      "                                                    \n"
      "  baseColor = texture2D( s_baseMap, v_texCoord );   \n"
      "  lightColor = texture2D( s_lightMap, v_texCoord ); \n"
      "  gl_FragColor = baseColor * (lightColor + 0.25);   \n"
      "}                                                   \n";
    */
/*
    // Load the shaders and get a linked program object
    ctx.programObject = dgLoadProgram(vShaderStr, fShaderStr);

    // Get the attribute locations
    ctx.positionLoc = glGetAttribLocation(ctx.programObject, "a_position");
    ctx.mvpLoc = glGetUniformLocation(ctx.programObject, "mvp_matrix" );
	ctx.colorLoc = glGetUniformLocation(ctx.programObject, "u_color");

	ctx.texCoordLoc = glGetAttribLocation(ctx.programObject, "a_texCoord");
    ctx.samplerLoc = glGetUniformLocation(ctx.programObject, "s_texture");


   // Get the sampler location
   //ctx.baseMapLoc = glGetUniformLocation (ctx.programObject, "s_baseMap" );
   //ctx.lightMapLoc = glGetUniformLocation (ctx.programObject, "s_lightMap" );

   // Load the textures
   //ctx.baseMapTexId = dgLoadTexture ( "Assets/Textures/basemap.tga" );
   //ctx.lightMapTexId = dgLoadTexture ( "Assets/Textures/lightmap.tga" );


    DGOpenGLES20Lib* gl = this;

	gl->matrixMode(GL_PROJECTION);
	gl->loadIdentity();

	gl->matrixMode(GL_MODELVIEW);
	gl->loadIdentity();

	DGColor c("#474747");
	glClearColor(c.r, c.g, c.b, 0.5f);				    // Black Background

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	return GL_TRUE;
}

void DGOpenGLES20Lib::reset(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

    DGOpenGLES20Lib* gl = this;

	gl->matrixMode(GL_MODELVIEW);
	gl->loadIdentity();
}

void DGOpenGLES20Lib::makeMvpMatrix(){
	ctx.mvpMatrix = DGMatrix4x4::Multiply(ctx.modelViewMatrix, ctx.perspectiveMatrix);
}

// Start Implements Interface DGGraphicsLib

void DGOpenGLES20Lib::viewport(DGint x, DGint y, DGsizei width, DGsizei height){
	glViewport(x, y, width, height);
}

void DGOpenGLES20Lib::setColor(const DGColor& c){
	ctx.color = c;
}

void DGOpenGLES20Lib::drawLine(const DGVector3& startV, const DGVector3& endV){
	// Use the program object
	glUseProgram(ctx.programObject);

	DGVector3 vertices[] = {startV, endV};

	// Load the vertex data
	glVertexAttribPointer(ctx.positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(DGVector3), vertices);
	glEnableVertexAttribArray(ctx.positionLoc);

    this->makeMvpMatrix();
	glUniformMatrix4fv(ctx.mvpLoc, 1, GL_FALSE, (GLfloat*) &ctx.mvpMatrix.m[0][0]);

	// Set Draw Color
	glUniform4fv(ctx.colorLoc, 1, (GLfloat*)&ctx.color);

	glDrawArrays(GL_LINES, 0, 2); 
}

void DGOpenGLES20Lib::drawMesh(DGMesh* mesh){
	// Enable Texture 2D
	if (mesh->uv || mesh->uv2) {
		glEnable(GL_TEXTURE_2D);
	}

	// Use the program object
	glUseProgram(ctx.programObject);

	// Load the vertex data
	if (mesh->vertices) {
		glVertexAttribPointer(ctx.positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(DGVector3), mesh->vertices);
		glEnableVertexAttribArray(ctx.positionLoc);
	}

	// Load the texture coordinate
	if (mesh->uv) {
		glVertexAttribPointer(ctx.texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(DGVector2), mesh->uv);
		glEnableVertexAttribArray(ctx.texCoordLoc);
	}

	// Calculate perspective
    this->makeMvpMatrix();
	glUniformMatrix4fv(ctx.mvpLoc, 1, GL_FALSE, (GLfloat*) &ctx.mvpMatrix.m[0][0]);

	// Set Draw Color
	glUniform4fv(ctx.colorLoc, 1, (GLfloat*)&ctx.color);
	
	// Draw Elements
	if (mesh->indexCount > 0 && mesh->indices) {
		glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, mesh->indices);
	}

	// Disable Texture 2D
	if (mesh->uv || mesh->uv2) {
		glDisable(GL_TEXTURE_2D);
	}


   GLfloat vVertices[] = { -0.5f,  0.5f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                           -0.5f, -0.5f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            0.5f, -0.5f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            0.5f,  0.5f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram (ctx.programObject );

   // Load the vertex position
   glVertexAttribPointer (ctx.positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 5 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer (ctx.texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );

   glEnableVertexAttribArray (ctx.positionLoc );
   glEnableVertexAttribArray (ctx.texCoordLoc );

   // Bind the base map
   //glActiveTexture ( GL_TEXTURE0 );
   //glBindTexture ( GL_TEXTURE_2D, ctx.baseMapTexId);

   // Set the base map sampler to texture unit to 0
   //glUniform1i (ctx.samplerLoc, 0 );

   // Bind the light map
   //glActiveTexture ( GL_TEXTURE1 );
   //glBindTexture ( GL_TEXTURE_2D, ctx.lightMapTexId);
   
   // Set the light map sampler to texture unit 1
   //glUniform1i (ctx.lightMapLoc, 1 );

   //glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
   
}

void DGOpenGLES20Lib::swapBuffers(){
	eglSwapBuffers(this->display, this->surface);
}

// End Implements Interface DGGraphicsLib


// Start Implements OpenGL ES 1.1 Fixed Function Vertex Pipeline
void DGOpenGLES20Lib::matrixMode(GLenum mode){
	if (GL_MODELVIEW == mode) {
		ctx.currentMatrix = &ctx.modelViewMatrix;
		ctx.currentMatrixStack = &ctx.modelViewMatrixStack;
	} else if (GL_PROJECTION == mode){
		ctx.currentMatrix = &ctx.perspectiveMatrix;
		ctx.currentMatrixStack = &ctx.perspectiveMatrixStack;
	}
}

void DGOpenGLES20Lib::loadIdentity(){
	DGMatrix4x4* result = ctx.currentMatrix;
	result->identity();
}

void DGOpenGLES20Lib::multMatrix(const DGMatrix4x4& matrix){
	*ctx.currentMatrix = DGMatrix4x4::Multiply(matrix, *ctx.currentMatrix);
}

void DGOpenGLES20Lib::translate(DGfloat tx, DGfloat ty, DGfloat tz){
	DGMatrix4x4* result = ctx.currentMatrix;

    result->m[3][0] += (result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz);
    result->m[3][1] += (result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz);
    result->m[3][2] += (result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz);
    result->m[3][3] += (result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz);	
}

void DGOpenGLES20Lib::rotate(DGfloat angle, DGfloat x, DGfloat y, DGfloat z){
   GLfloat sinAngle, cosAngle;
   GLfloat mag = sqrtf(x * x + y * y + z * z);
      
   sinAngle = sinf(angle * DGMathf::PI / 180.0f);
   cosAngle = cosf(angle * DGMathf::PI / 180.0f);

   if (mag > 0.0f){
      GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
      GLfloat oneMinusCos;
      DGMatrix4x4 rotMat;
   
      x /= mag;
      y /= mag;
      z /= mag;

      xx = x * x;
      yy = y * y;
      zz = z * z;
      xy = x * y;
      yz = y * z;
      zx = z * x;
      xs = x * sinAngle;
      ys = y * sinAngle;
      zs = z * sinAngle;
      oneMinusCos = 1.0f - cosAngle;

      rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
      rotMat.m[0][1] = (oneMinusCos * xy) - zs;
      rotMat.m[0][2] = (oneMinusCos * zx) + ys;
      rotMat.m[0][3] = 0.0F; 

      rotMat.m[1][0] = (oneMinusCos * xy) + zs;
      rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
      rotMat.m[1][2] = (oneMinusCos * yz) - xs;
      rotMat.m[1][3] = 0.0F;

      rotMat.m[2][0] = (oneMinusCos * zx) - ys;
      rotMat.m[2][1] = (oneMinusCos * yz) + xs;
      rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
      rotMat.m[2][3] = 0.0F; 

      rotMat.m[3][0] = 0.0F;
      rotMat.m[3][1] = 0.0F;
      rotMat.m[3][2] = 0.0F;
      rotMat.m[3][3] = 1.0F;

      multMatrix(rotMat);
   }
}

void DGOpenGLES20Lib::scale(DGfloat sx, DGfloat sy, DGfloat sz){
	DGMatrix4x4* result = ctx.currentMatrix;

    result->m[0][0] *= sx;
    result->m[0][1] *= sx;
    result->m[0][2] *= sx;
    result->m[0][3] *= sx;

    result->m[1][0] *= sy;
    result->m[1][1] *= sy;
    result->m[1][2] *= sy;
    result->m[1][3] *= sy;

    result->m[2][0] *= sz;
    result->m[2][1] *= sz;
    result->m[2][2] *= sz;
    result->m[2][3] *= sz;
}


void DGOpenGLES20Lib::frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearZ, GLfloat farZ){
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;

    DGMatrix4x4 frust;

    if ((nearZ <= 0.0f) || (farZ <= 0.0f) ||
         (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f))
         return;

    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0f;

    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

    matrixMode(GL_PROJECTION);
	loadIdentity();
	multMatrix(frust);
    matrixMode(GL_MODELVIEW);
}

void DGOpenGLES20Lib::perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar){
   GLfloat frustumW, frustumH;
   
   //log->debug("perspective: %.2f, %.2f, %.2f, %.2f", fovy, aspect, zNear, zFar);

   frustumH = tanf(fovy / 360.0f * DGMathf::PI) * zNear;
   frustumW = frustumH * aspect;

   frustum(-frustumW, frustumW, -frustumH, frustumH, zNear, zFar);

   //log->debug(ctx.perspectiveMatrix.toString().data());
}

void DGOpenGLES20Lib::ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearZ, GLfloat farZ){
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;

    DGMatrix4x4 ortho;

    if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f))
        return;

	memset(&ortho, 0x0, sizeof(DGMatrix4x4));

    ortho.m[0][0] = 1.0f;
    ortho.m[1][1] = 1.0f;
    ortho.m[2][2] = 1.0f;
    ortho.m[3][3] = 1.0f;

    ortho.m[0][0] = 2.0f / deltaX;
    ortho.m[3][0] = -(right + left) / deltaX;
    ortho.m[1][1] = 2.0f / deltaY;
    ortho.m[3][1] = -(top + bottom) / deltaY;
    ortho.m[2][2] = -2.0f / deltaZ;
    ortho.m[3][2] = -(nearZ + farZ) / deltaZ;

    matrixMode(GL_PROJECTION);
	multMatrix(ortho);
    matrixMode(GL_MODELVIEW);
}

// End Implements OpenGL ES 1.1 Fixed Function Vertex Pipeline

// Start Implements OpenGL glu Function
static void normalize(float vec[3]) {
	float size = (float)sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);

	if(size < TOLERANCE){
		return;
	} else {
		vec[0] = vec[0]/size;
		vec[1] = vec[1]/size;
		vec[2] = vec[2]/size;
	}
}

static void cross(float v1[3], float v2[3], float result[3]){
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

void DGOpenGLES20Lib::lookAt(DGfloat eyex, DGfloat eyey, DGfloat eyez, DGfloat centerx,
	  DGfloat centery, DGfloat centerz, DGfloat upx, DGfloat upy,
	  DGfloat upz)
{
    float forward[3], side[3], up[3];
	DGMatrix4x4 view;

    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;

    up[0] = upx;
    up[1] = upy;
    up[2] = upz;

    normalize(forward);

    // Side = forward x up
    cross(forward, up, side);
    normalize(side);

    // Recompute up as: up = side x forward
    cross(side, forward, up);

	view.identity();

    view.m[0][0] = side[0];
    view.m[1][0] = side[1];
    view.m[2][0] = side[2];

    view.m[0][1] = up[0];
    view.m[1][1] = up[1];
    view.m[2][1] = up[2];

    view.m[0][2] = -forward[0];
    view.m[1][2] = -forward[1];
    view.m[2][2] = -forward[2];

	multMatrix(view);
    translate(-eyex, -eyey, -eyez);
}

//End Implements OpenGL glu Function


void DGOpenGLES20Lib::pushMatrix(){
	DGMatrix4x4* pMatrix = ctx.currentMatrix;
	stack<DGMatrix4x4>* pPatrixStack = ctx.currentMatrixStack;

	if (pPatrixStack && pMatrix) {
		pPatrixStack->push(*pMatrix);
	}
}

void DGOpenGLES20Lib::popMatrix(){
	DGMatrix4x4* pMatrix = ctx.currentMatrix;
	stack<DGMatrix4x4>* pPatrixStack = ctx.currentMatrixStack;

	if (pPatrixStack && pMatrix && pPatrixStack->size() > 0) {
		*pMatrix = pPatrixStack->top();
		pPatrixStack->pop();
	}
}

void DGOpenGLES20Lib::initTexture(DGTexture* texture){
	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &texture->nativeTextureID);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture->nativeTextureID);

	int textureType = GL_RGB;
	
	if(texture->channels == 4)
		textureType = GL_RGBA;

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, textureType, texture->width, 
		texture->height, 0, textureType, GL_UNSIGNED_BYTE, texture->data);

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void DGOpenGLES20Lib::setTexture(DGTexture* texture){
	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->nativeTextureID);

	// Set the sampler texture unit to 0
    glUniform1i(ctx.samplerLoc, 0);
}


void  DGOpenGLES20Lib::destroyTexture(DGTexture* texture){
	// Delete texture object
	glDeleteTextures(1, &texture->nativeTextureID);
}
 */



/*

#include "dg_mesh_renderer.h"


DGMeshRenderer::DGMeshRenderer(void){

}

DGMeshRenderer::DGMeshRenderer(DGMesh* mesh){
  this->mesh = mesh;
}

DGMeshRenderer::~DGMeshRenderer(void){

}

void DGMeshRenderer::init(DGGameObject* gameObject, DGContext* ctx){
    DGRenderer::init(gameObject, ctx);
}

void DGMeshRenderer::update(DGContext* ctx){
  DGRenderer::update(ctx);
}

void DGMeshRenderer::draw(DGContext* ctx){
  DGGraphicsLib* gl = ctx->getGraphicsLib();

  if (this->material) {
    gl->setColor(this->material->color);

    if (this->material && this->material->mainTexture) {
      gl->setTexture(this->material->mainTexture);
    }
  }

  gl->pushMatrix();

  gl->multMatrix(this->mesh->matrix);
  gl->drawMesh(this->mesh);

  gl->popMatrix();

  DGRenderer::draw(ctx);
}

void DGMeshRenderer::destroy(){
  DGRenderer::destroy();
}



 */