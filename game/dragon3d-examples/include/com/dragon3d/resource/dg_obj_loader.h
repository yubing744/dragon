#pragma once

#include "dg_config.h"
#include "dg_model.h"
#include "dg_model_loader.h"

#include <vector>
using std::vector;

#if !defined(DG_OBJ_LOADER)
#define DG_OBJ_LOADER

class DGObjLoader :public DGModelLoader
{
public:
	DGObjLoader(void);
	virtual ~DGObjLoader(void);

public:
	//  将obj文件中的信息读入到模型中
	virtual bool importModel(t3DModel *pModel, char *strFileName);

private:
	// 读入对象，在ImportObj()中将调用该函数
	void ReadObjFile(t3DModel *pModel);

	// 读入顶点信息，在ReadObjFile()中调用该函数
	void ReadVertexInfo();

	// 读入面信息，在ReadObjFile()中调用该函数
	void ReadFaceInfo();

	// 完成面信息的读入之后调用该函数
	void FillInObjectInfo(t3DModel *pModel);

	// 计算顶点的法向量
	void ComputeNormals(t3DModel *pModel);

	// 由于在obj文件中没有纹理/材质名称，只能手动设置
	// materialID是在模型材质列表中的索引号
	void SetObjectMaterial(t3DModel *pModel, int whichObject, int materialID);

	//  添加材质
	void AddMaterial(t3DModel *pModel, char *strName, char *strFile, 
					 int r = 255,      int g = 255,   int b = 255);

private:

	// 需要读入的文件指针
	FILE *m_FilePointer;

	// 顶点链表
	vector<CVector3>  m_pVertices;

	// 面链表
	vector<tFace> m_pFaces;

	// UV坐标链表
	vector<CVector2>  m_pTextureCoords;

	// 当前对象是否具有纹理坐标
	bool m_bObjectHasUV;

	// 当前读入的对象是否是面
	bool m_bJustReadAFace;
};

#endif