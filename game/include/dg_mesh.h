#pragma once

#include "dg_config.h"

#if !defined(DG_MESH)
#define DG_MESH

#include "dg_vector2.h"
#include "dg_vector3.h"
#include "dg_matrix4x4.h"

#include <string>
using std::string;


class DGMesh
{
public:
	DGMesh(void);
	DGMesh(const char* name);
	virtual ~DGMesh(void);

public:
	DGVector3* vertices; //顶点的数据
    DGVector2* uv; //材质坐标数据
    DGVector2* uv2; //二级材质坐标数据
    DGVector3* normals; //法向量数据
	DGuint vertexCount; //网格顶点个数


    DGuint* indices; //索引数据
    DGuint indexCount; //索引个数

	DGMatrix4x4 matrix; //Transformation matrix for mesh data

private:
	string name;
};

#endif