#include "dg_lib_3ds_model_loader.h"

#include <lib3ds/file.h>
#include <lib3ds/io.h>
#include <lib3ds/camera.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/vector.h>
#include <lib3ds/light.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "dg_mesh_renderer.h"


DGLog* DGLib3DSModelLoader::LOG = new DGLog("dg_lib_3ds_model_loader");


DGLib3DSModelLoader::DGLib3DSModelLoader(void)
{
}


DGLib3DSModelLoader::~DGLib3DSModelLoader(void)
{
}


DGboolean DGLib3DSModelLoader::loadModel(char *strFileName, DGModel* outModel) {
	DGPlatform* platform = DGPlatform::getCurrent();

	DGResource* res = NULL;
	if((res = platform->openResource(strFileName)) == NULL){
		LOG->error("Can't open model file %s", strFileName);
		return DG_FALSE;
	}

	if (!loadModel(res, outModel)) {
		LOG->error("Can't load model file %s", strFileName);
		platform->closeResource(res);
		return DG_FALSE;
	}

	platform->closeResource(res);
	return DG_TRUE;
}

// lib3ds file

static Lib3dsBool
dg_fileio_error_func(void *self)
{
  return DG_FALSE;
}


static long
dg_fileio_seek_func(void *self, long offset, Lib3dsIoSeek origin)
{
  DGResource* res = (DGResource*)self;

  int o;
  switch (origin) {
    case LIB3DS_SEEK_SET:
      o = SEEK_SET;
      break;
    case LIB3DS_SEEK_CUR:
      o = SEEK_CUR;
      break;
    case LIB3DS_SEEK_END:
      o = SEEK_END;
      break;
    default:
      ASSERT(0);
      return(0);
  }

  return (res->seek(offset, o));
}


static long
dg_fileio_tell_func(void *self)
{
	DGResource* res = (DGResource*)self;
	return(res->tell());
}


static size_t
dg_fileio_read_func(void *self, void *buffer, size_t size)
{
  DGResource* res = (DGResource*)self;
  return(res->read(buffer, 1, size));
}


static size_t
dg_fileio_write_func(void *self, const void *buffer, size_t size)
{
    //FILE *f = (FILE*)self;
    //return(fwrite(buffer, 1, size, f));
	return 0;
}

Lib3dsFile* dg_lib3ds_file_load(DGResource* res) {
	Lib3dsFile *file;
	Lib3dsIo *io;

	file = lib3ds_file_new();
	if (!file) {
		return(0);
	}
  
	io = lib3ds_io_new(
		res, 
		dg_fileio_error_func,
		dg_fileio_seek_func,
		dg_fileio_tell_func,
		dg_fileio_read_func,
		dg_fileio_write_func
	);

	if (!io) {
	lib3ds_file_free(file);
		return(0);
	}

	if (!lib3ds_file_read(file, io)) {
		free(file);
		lib3ds_io_free(io);
		return(0);
	}

	lib3ds_io_free(io);

	return(file);
}

// ------------

DGboolean loadSubModel(Lib3dsFile *file, Lib3dsNode *node, DGGameObject* parent, int depth) {
	DGGameObject* subModel = new DGGameObject();
	parent->addChild(subModel);

	Lib3dsNode *p;
    for (p=node->childs; p!=0; p=p->next) {
		loadSubModel(file, p, subModel, depth++);
    }

	if (node->type==LIB3DS_OBJECT_NODE) {

		DGLib3DSModelLoader::LOG->debug("load model '%s' depth %d", node->name, depth);

		Lib3dsMesh *mesh;
		Lib3dsMaterial *mat;

		if (strcmp(node->name,"$$$DUMMY")==0) {
			return DG_FALSE;
		}

		mesh = lib3ds_file_mesh_by_name(file, node->data.object.morph);
		if( mesh == NULL )
			mesh = lib3ds_file_mesh_by_name(file, node->name);

		DGMesh* m = new DGMesh(mesh->name);
		DGMaterial* material = NULL;

		Lib3dsObjectData *d = &node->data.object;

		Lib3dsMatrix M;
        lib3ds_matrix_copy(M, node->matrix);
		//lib3ds_matrix_translate_xyz(M, d->pivot[0], d->pivot[1], d->pivot[2]);
        lib3ds_matrix_inv(M);
		m->matrix = DGMatrix4x4((DGfloat*)M);

		DGLib3DSModelLoader::LOG->info("%s %s", node->name, m->matrix.toString().data());

		// 顶点坐标
		m->vertexCount = mesh->points;
		m->vertices = (DGVector3*)mesh->pointL;

		// 顶点材质坐标
		m->uv = (DGVector2*)mesh->texelL;

		// 三角形索引
		m->indexCount = mesh->faces * 3;
		m->indices = (DGuint*)malloc(sizeof(DGuint) * m->indexCount);

		for (DGuint p=0; p<mesh->faces; ++p) {
			Lib3dsFace *f = &mesh->faceL[p];

			m->indices[p * 3] = f->points[0];
			m->indices[p * 3 + 1] = f->points[1];
			m->indices[p * 3 + 2] = f->points[2];
		} 

		// 面法向量
		Lib3dsVector *normalL = (Lib3dsVector *)malloc(3*sizeof(Lib3dsVector)*mesh->faces);
		lib3ds_mesh_calculate_normals(mesh, normalL);
		m->normals = (DGVector3*)normalL;

		// 面材质
		Lib3dsFace *f = &mesh->faceL[0];
		if (f->material[0]) {
			mat = lib3ds_file_material_by_name(file, f->material);

			if (mat) {
				material = new DGMaterial();

				material->color = DGColor(mat->diffuse[0], mat->diffuse[1], mat->diffuse[2], mat->diffuse[3]);

				if (mat->texture1_map.name[0]) {		/* texture map? */
					Lib3dsTextureMap *tex = &mat->texture1_map;
					material->mainTexture = new DGTexture(tex->name);	
				}
			}
		}

		DGMeshRenderer* renderer = new DGMeshRenderer(m);
		renderer->material = material;

		subModel->addComponent(renderer);
	}

	return DG_TRUE;
}


DGboolean DGLib3DSModelLoader::loadModel(DGResource* res, DGModel* outModel) {
	Lib3dsFile *file;
	Lib3dsIo *io;

	file = dg_lib3ds_file_load(res);
	if (!file) {
		LOG->error("3dsplayer: Error: Loading 3DS file failed.\n");
		return DG_FALSE;
	}

	/* No nodes?  Fabricate nodes to display all the meshes. */
	if( !file->nodes )
	{
		Lib3dsMesh *mesh;
		Lib3dsNode *node;

		for(mesh = file->meshes; mesh != NULL; mesh = mesh->next)
		{
			node = lib3ds_node_new_object();
			strcpy(node->name, mesh->name);
			node->parent_id = LIB3DS_NO_PARENT;
			lib3ds_file_insert_node(file, node);
		}
	}

	lib3ds_file_eval(file, 1.0f);


	// 构建模型
	for (Lib3dsNode *p=file->nodes; p!=0; p=p->next) {
		loadSubModel(file, p, outModel, 0);
    }

	return DG_TRUE;
}