#include <stdlib.h>
#include <esUtil.h>
#include "dg_config.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

typedef struct {
   GLuint programObject; // Handle to a program object
} UserData;

///
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint LoadShader(GLenum type, const char *shaderSrc){
   GLuint shader;
   GLint compiled;
   
   // Create the shader object
   shader = glCreateShader(type);

   if (shader == 0)
		return 0;

   // Load the shader source
   glShaderSource(shader, 1, &shaderSrc, NULL);
   
   // Compile the shader
   glCompileShader(shader);

   // Check the compile status
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

   if (!compiled){
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen);
      
      if (infoLen > 1){
         char* infoLog = (char*)malloc(sizeof(char) * infoLen);

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog);
         esLogMessage("Error compiling shader:\n%s\n", infoLog);            
         
         free (infoLog);
      }

      glDeleteShader(shader);
      return 0;
   }

   return shader;
}

///
// Initialize the shader and program object
//
int Init(ESContext *esCtx)
{
   UserData* userData = (UserData*)esCtx->userData;

   char vShaderStr[] =  
      "attribute vec4 vPosition;    \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = vPosition;  \n"
      "}                            \n";
   
   char fShaderStr[] =  
      "precision mediump float;\n"\
      "void main()                                  \n"
      "{                                            \n"
      "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
      "}                                            \n";

   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
   fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

   // Create the program object
   programObject = glCreateProgram();
   
   if (programObject == 0)
      return 0;

   glAttachShader(programObject, vertexShader);
   glAttachShader(programObject, fragmentShader);

   // Bind vPosition to attribute 0   
   glBindAttribLocation(programObject, 0, "vPosition");

   // Link the program
   glLinkProgram(programObject);

   // Check the link status
   glGetProgramiv (programObject, GL_LINK_STATUS, &linked);

   if (!linked){
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      
      if (infoLen > 1){
         char* infoLog = (char*)malloc(sizeof(char) * infoLen);

         glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
         esLogMessage ( "Error linking program:\n%s\n", infoLog );            
         
         free ( infoLog );
      }

      glDeleteProgram(programObject);
      return FALSE;
   }

   // Store the program object
   userData->programObject = programObject;

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(ESContext *esContext)
{
   UserData *userData = (UserData *)esContext->userData;
   GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f, 
                           -0.5f, -0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f };
      
   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear(GL_COLOR_BUFFER_BIT);

   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex data
   glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
   glEnableVertexAttribArray ( 0 );

   glDrawArrays ( GL_TRIANGLES, 0, 3 );

   eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}


int main(int argc, char *argv[]){
   ESContext esContext;
   UserData userData;

   esInitContext(&esContext);
   esContext.userData = &userData;

   esCreateWindow(&esContext, "Dragon Game", 640, 480, ES_WINDOW_RGB);
   
   if (!Init( &esContext))
      return 0;

   esRegisterDrawFunc(&esContext, Draw);
   
   esMainLoop (&esContext);
}
