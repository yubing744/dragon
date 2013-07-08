#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

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
