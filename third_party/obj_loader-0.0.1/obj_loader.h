#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <stdio.h>
#include "entity.h"

/*
 * variables
 */
float value;

/*
 * structures
 */
typedef enum {
  NULL_T,
  VERTEX_T,
  FACE_T,
  FLOAT_T,
  INT_T,
  COMMENT_T,
  MAT_T,
  OBJNAME_T,
  VERTEX_NORM_T,
  GROUP_NAME_T,
  USEMAT_T
} token_t;

/*
 * public prototypes
 */
int obj_load(char *filename, entity_t *);

/*
 * private prototypes
 */
void _getVertex(Vertex *v);
void _getFace(int *, int *, int *);
token_t _getToken(FILE *);
token_t _getFloat(FILE *);
float   _getValue(void);

#endif 
