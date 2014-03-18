#ifndef _ENTITY_H_
#define _ENTITY_H_

typedef struct {
  float x, y, z;
} Vertex; 

typedef struct {
  Vertex v[3];
} polygon_t;

// don't want to use
typedef struct {
  int v[3];
} Face;

typedef struct {
  int nPolygons;
  polygon_t *pList;
} entity_t;

#endif