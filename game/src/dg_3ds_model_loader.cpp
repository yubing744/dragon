#include "dg_3ds_model_loader.h"

DGLog* DG3DSModelLoader::LOG = new DGLog("dg_3ds_model_loader");

DG3DSModelLoader::DG3DSModelLoader(void)
{
}


DG3DSModelLoader::~DG3DSModelLoader(void)
{
}


DGboolean DG3DSModelLoader::loadModel(char *strFileName, DGModel* outModel) {
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


// ---------------------


CHUNK_3DS DG3DSModelLoader::readChunk(DGResource* res){
	CHUNK_3DS chunk;
	chunk.ID = readWord(res);
	chunk.length = readUint(res);
	return chunk;
}

WORD DG3DSModelLoader::readWord(DGResource* res){
	return readByte(res) + (readByte(res) << 8);
}

BYTE DG3DSModelLoader::readByte(DGResource* res){
	BYTE out;
	res->read(&out,1,1);
	return out;
}

UINT DG3DSModelLoader::readUint(DGResource* res){
	return readWord(res) + (readWord(res) << 16);
}

UINT DG3DSModelLoader::readString(DGResource* res, STRING_3DS &str){
	int i=0;
	while((str.string[i++]=readByte(res))!=0);
	return i;
}

float DG3DSModelLoader::readFloat(DGResource* res){
	float out;
	res->read(&out,sizeof(float),1);
	return out;
}

// ---------------------


DGboolean DG3DSModelLoader::loadModel(DGResource* res, DGModel* outModel) {
	CHUNK_3DS chunk;
	chunk = readChunk(res);

	if(chunk.ID != PRIM){
		return DG_FALSE;
	}

	readPrimary(res, outModel, chunk.length - 6);
	return DG_TRUE;
}


UINT DG3DSModelLoader::readPrimary(DGResource* res, DGModel* outModel, UINT n){
	UINT count=0;
	CHUNK_3DS chunk;

	while(count<n){
		chunk = readChunk(res);

		switch(chunk.ID){
		case PRIM_EDIT:
			readEdit(res, outModel, chunk.length-6);
			count+=chunk.length;
			break;
		case PRIM_KEY:
			readKeyframe(res, outModel, chunk.length-6);
			count+=chunk.length;
			break;
		default:
			count+=chunk.length;
			res->seek(chunk.length-6, SEEK_CUR);
			break;
		}
	}

	return count;
}


UINT DG3DSModelLoader::readEdit(DGResource* res, DGModel* outModel, UINT n){
	UINT count=0;
	CHUNK_3DS chunk;

	while(count<n){
		chunk = readChunk(res);

		switch(chunk.ID){
		case EDIT_MESH:
			readMesh(res, outModel, chunk.length-6);
			count+=chunk.length;
			break;
		case EDIT_MAT:
			readMaterial(res, outModel, chunk.length-6);
			count+=chunk.length;
			break;
		default:
			count+=chunk.length;
			res->seek(chunk.length-6, SEEK_CUR);
			break;
		}
	}

	return count;
}

UINT DG3DSModelLoader::readMesh(DGResource* res, DGModel* outModel, UINT n){
	UINT count=0;
	CHUNK_3DS chunk;

	STRING_3DS str;
	count+=readString(res, str);

	DGMesh* mesh = new DGMesh(str.string);

	while(count<n){
		chunk=readChunk(res);
		switch(chunk.ID){
		case MESH_INFO:
			readMeshInfo(res, mesh, chunk.length-6);
			count+=chunk.length;
			break;
		default:
			count+=chunk.length;
			res->seek(chunk.length-6, SEEK_CUR);
			break;
		}
	}

	outModel->addPart(mesh, NULL);

	return count;
}

UINT DG3DSModelLoader::readMeshInfo(DGResource* res, DGMesh* outMesh, UINT n){
	UINT count=0;
	CHUNK_3DS chunk;
	float f1,f2,f3;
	WORD w1,w2,w3;
	WORD t, i;

	DGVector3* vertices;
	DGVector2* uv;
	DGuint* indexes;

	while(count<n){
		chunk=readChunk(res);
		switch(chunk.ID){
		case MESH_VERTEX:
			t=readWord(res);//number of vertices in this mesh

			outMesh->vertexCount = t;
			vertices = (DGVector3*)malloc(sizeof(DGVector3) * t);
			res->read(vertices, sizeof(DGVector3), t);
			outMesh->vertices = vertices;

			count+=chunk.length;
			break;
		
		case MESH_FACET:
			//ReadFacetInfo(chunk.length-6);

			//number of facets in this mesh
			t=readWord(res);
			count+=2;

			outMesh->indexCount = t;
			indexes = (DGuint*)malloc(sizeof(DGuint) * t);

			i = 0;

			while(i < t){
				w1=readWord(res);//index pointed to vertex which is 1st corner in facet 
				count+=2;

				w2=readWord(res);//index pointed to vertex which is 2sd corner in facet 
				count+=2;

				w3=readWord(res);//index pointed to vertex which is 3th corner in facet 
				count+=2;

				indexes[i] = w1;
				indexes[i + 1] = w2;
				indexes[i + 2] = w3;

				readWord(res);//facet flag ,not used yet
				count+=2;

				i+=3;
			}

			outMesh->indices = indexes;

			count+=chunk.length;
			break;

		case MESH_MAPCOORD:
			t=readWord(res);//number of texcoords in this mesh

			uv = (DGVector2*)malloc(sizeof(DGVector2) * t);
			res->read(uv, sizeof(DGVector2), t);
			outMesh->uv = uv;

			count+=chunk.length;
			break;
		case MESH_LOCAL:
			//local transform matrix
			outMesh->matrix.identity();

			int i,j;
          
			for (i=0; i<4; i++) {
				for (j=0; j<3; j++) {
					outMesh->matrix.m[i][j] = readFloat(res);
				}
			}

			count+=chunk.length;
			break;

		default:
			count+=chunk.length;
			res->seek(chunk.length-6, SEEK_CUR);
			break;
		}
	}

	return count;
}

UINT DG3DSModelLoader::readMaterial(DGResource* res, DGModel* outModel, UINT n){
	UINT count=0;
	CHUNK_3DS chunk;
	STRING_3DS str;

	DGMaterial* material = new DGMaterial();

	while(count<n){
		chunk=readChunk(res);

		switch(chunk.ID){
		case MAT_NAME:
			readString(res, str);//name of material
			material->name = string(str.string);
			count+=chunk.length;
			break;
		case MAT_DIF:
			readMatDif(res, material, chunk.length-6);
			count+=chunk.length;
			break;
		case MAT_MAP:
			readMatMap(res, material, chunk.length-6);
			count+=chunk.length;
			break;
		default:
			count+=chunk.length;
			res->seek(chunk.length-6, SEEK_CUR);
			break;
		}
	}

	return count;
}

UINT DG3DSModelLoader::readMatDif(DGResource* res, DGMaterial* material, UINT n){
	UINT count=0;
	CHUNK_3DS chunk;
	BYTE b1,b2,b3;

	while(count<n){
		chunk=readChunk(res);
		switch(chunk.ID){
		case GLOBAL_RGB_BYTE://diffuse color of material 
			b1=readByte(res);//red
			b2=readByte(res);//green
			b3=readByte(res);//blue
			material->color = DGColor(b1, b2, b3);
			count+=chunk.length;
			break;
		case GLOBAL_RGB_BYTE_GAMMA://gamma of diffuse color of material 
			b1=readByte(res);//red
			b2=readByte(res);//green
			b3=readByte(res);//blue
			//UserMaterialDiffuseGamma(b1,b2,b3);
			count+=chunk.length;
		default:
			count+=chunk.length;
			res->seek(chunk.length-6, SEEK_CUR);
			break;
		}
	}

	return count;
}

UINT DG3DSModelLoader::readMatMap(DGResource* res, DGMaterial* material, UINT n){
	UINT count=0;
	STRING_3DS str;
	CHUNK_3DS chunk;
	while(count<n){
		chunk=readChunk(res);
		switch(chunk.ID){
		case MAP_NAME:
			readString(res, str);//name of texture map file
			//UserMaterialMapName(str.string);

			material->mainTexture = new DGTexture(str.string);

			count+=chunk.length;
			break;
		default:
			count+=chunk.length;
			res->seek(chunk.length-6, SEEK_CUR);
			break;
		}
	}
	return count;
}

UINT DG3DSModelLoader::readKeyframe(DGResource* res, DGModel* outModel, UINT n){
	UINT count=0;
	CHUNK_3DS chunk;
	UINT i1,i2;

	/*
	while(count<n){
		chunk=ReadChunk();
		switch(chunk.ID){
		case KEY_INFO:
			i1=ReadUint();//start frame 
			i2=ReadUint();//end frame
			UserKeyframeRange(i1,i2);
			count+=chunk.length;
			break;
		case KEY_MESH:
			ReadKeyMesh(chunk.length-6);
			count+=chunk.length;
			break;
		default:
			count+=chunk.length;
			fseek(pfile,chunk.length-6,SEEK_CUR);
			break;
		}
	}
	*/

	return count;
}
