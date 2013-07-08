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
 * Description: base config for all other classes
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/07/08
 **********************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <dragon/config.h>

/*-------------------------------------------------------------------------
 * Data type definitions
 *-----------------------------------------------------------------------*/
typedef unsigned int DGenum;
typedef unsigned char DGboolean;
typedef unsigned int DGbitfield;
typedef signed char DGbyte;
typedef short DGshort;
typedef int DGint;
typedef int DGsizei;
typedef unsigned char DGubyte;
typedef unsigned short DGushort;
typedef unsigned int DGuint;
typedef float DGfloat;
typedef float DGclampf;
typedef double DGdouble;
typedef double DGclampd;
typedef void DGvoid;

/* Boolean */
#define DG_FALSE 0
#define DG_TRUE 1

/* Commons macro */
#define dgDelete(p) if (p) {delete p; p=NULL;}
#define dgDeletes(p) if (p) {delete [] p; p=NULL;}
#define dgFree(p) if (p) {free(p); p=NULL;}
