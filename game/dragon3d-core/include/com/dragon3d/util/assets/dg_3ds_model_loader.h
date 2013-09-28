#pragma once

#if !defined(DG_3DS_MODEL_LOADER)
#define DG_3DS_MODEL_LOADER

#include "dg_game.h"
#include "dg_texture.h"
#include "dg_material.h"
#include "dg_model_loader.h"

#include <map>
#include <string>

using std::map;
using std::string;


#define  BYTE unsigned char
#define  WORD unsigned short 
#define  UINT unsigned int

//begin primary chunk
const WORD PRIM =0x4D4D;
	//begin edit chunk
	const WORD PRIM_EDIT =0x3D3D;
		//begin mesh chunk
		 const WORD EDIT_MESH =0x4000;
			 const WORD MESH_INFO =0x4100;
				 const WORD MESH_VERTEX =0x4110;
				 const WORD MESH_FACET  =0x4120;
					 const WORD FACET_MAT=0x4130;
					 const WORD FACET_SMOOTH =0x4150;
				 const WORD MESH_MAPCOORD =0x4140;
				 const WORD MESH_COLOR    =0x4165;
				 const WORD MESH_LOCAL    =0x4160;
		//end mesh chunk

		//begin material chunk
		const WORD EDIT_MAT =0xafff;
			const WORD MAT_NAME =0xa000;
			const WORD MAT_AMB  =0xa010;
			const WORD MAT_DIF  =0xa020;
			const WORD MAT_SPE  =0xa030;
			const WORD MAT_MAP  =0xa200;
				const WORD MAP_NAME =0xa300;
		//end material chunk

	//end edit chunk

	//begin keyframe chunk
	const WORD PRIM_KEY =0xB000;
		 const WORD KEY_INFO =0xB008;
		 const WORD KEY_MESH =0xB002;
			 const WORD KEYF_HIERARCY =0xB010;
			 const WORD KEYF_DUMMY    =0xB011;
			 const WORD KEYF_PIVOT    =0xB013;
			 const WORD TRACK_POS     =0xB020;
			 const WORD TRACK_ROT     =0xB021;
			 const WORD TRACK_SCL     =0xB022;
			 const WORD KEYF_NODEID   =0xB030;
	//end keyframe chunk

	//some chunks in all others
	const WORD GLOBAL_RGB_FLOAT       =0x0010;
	const WORD GLOBAL_RGB_BYTE        =0x0011;
	const WORD GLOBAL_RGB_BYTE_GAMMA  =0x0012;
	const WORD GLOBAL_RGB_FLOAT_GAMMA =0x0013;
	const WORD GLOBAL_PER_WORD        =0x0030;
	const WORD GLOBAL_PER_FLOAT       =0x0031;
//end primary chunk

struct STRING_3DS{
	char string[128];
};

struct CHUNK_3DS{
	WORD ID;
	UINT length;
};

class DG3DSModelLoader
	:public DGModelLoader
{
public:
	DG3DSModelLoader(void);
	virtual ~DG3DSModelLoader(void);

public:
	virtual DGboolean loadModel(char *strFileName, DGModel* outModel);

private:
	WORD readWord(DGResource* res);
	UINT readUint(DGResource* res);
	BYTE readByte(DGResource* res);
	UINT readString(DGResource* res, STRING_3DS &str);
	float readFloat(DGResource* res);

	DGboolean loadModel(DGResource* res, DGModel* outModel);
	CHUNK_3DS readChunk(DGResource* res);
	UINT readPrimary(DGResource* res, DGModel* outModel, UINT n);
	UINT readEdit(DGResource* res, DGModel* outModel, UINT n);
	UINT readKeyframe(DGResource* res, DGModel* outModel, UINT n);
	UINT readMesh(DGResource* res, DGModel* outModel, UINT n);
	UINT readMeshInfo(DGResource* res, DGMesh* outMesh, UINT n);
	UINT readMaterial(DGResource* res, DGModel* outModel, UINT n);
	UINT readMatDif(DGResource* res, DGMaterial* material, UINT n);
	UINT readMatMap(DGResource* res, DGMaterial* material, UINT n);

private:
	static DGLog* LOG;
};

#endif