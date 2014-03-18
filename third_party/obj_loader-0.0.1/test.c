#include <stdio.h>
#include <stdlib.h>
#include "obj_loader.h"

int main(int argc, char *argv[])
{
  char *filename = argv[1];
  printf("opening: %s\n", filename);

  printf("alloc vertices\n");
  entity_t *entity;
  entity = malloc(sizeof(entity_t));

  printf("loading object\n");
  if(obj_load(filename, entity) == -1) {
    fprintf(stderr, "Couldn't load object: %s\n", filename);
    exit(-1);
  }

  free(entity);
}
