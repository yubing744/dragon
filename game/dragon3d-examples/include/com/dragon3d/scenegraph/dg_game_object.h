#pragma once

#include "dg_transform.h"
#include "dg_component.h"

#include <vector>
using std::vector;

#if !defined(DG_GAME_OBJECT)
#define DG_GAME_OBJECT

class DGGameObject
{
protected:
	//顶点
	typedef struct tagVERTEX {
		DGfloat x, y, z;
		DGfloat u, v;
	} VERTEX;

	//三角形
	typedef struct tagTRIANGLE {
		VERTEX vertexs[3];
	} TRIANGLE;

	//区段
	typedef struct tagSECTOR {
		int numTriangles;
		TRIANGLE* triangle;
	} SECTOR;

public:
	DGGameObject(void);

	DGGameObject(DGTransform* transform);

	virtual ~DGGameObject(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

	virtual void addChild(DGGameObject* child);
	virtual void addComponent(DGComponent* component);

	virtual DGComponent* findComponent(const char* name);


public:
	DGTransform* transform; //位置、方向、缩放

private:
	vector<DGGameObject*> children; //孩子对象
	vector<DGComponent*> components; //组件
};

#endif