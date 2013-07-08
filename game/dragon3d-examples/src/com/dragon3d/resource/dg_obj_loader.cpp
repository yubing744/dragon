#include "dg_obj_loader.h"


DGObjLoader::DGObjLoader(void)
{
}


DGObjLoader::~DGObjLoader(void)
{
}


//  下面的函数的功能是将obj文件的信息读入指定的模型中
bool DGObjLoader::importModel(t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};				// 用于显示错误信息

	// 判断是否是一个合法的模型和文件类型
	if(!pModel || !strFileName) return false;

	// 以只读方式打开文件，返回文件指针
	m_FilePointer = fopen(strFileName, "r");

	// 判断文件指针是否正确
	if(!m_FilePointer) {
		// 如果文件指针不正确，则显示错误信息
		sprintf(strMessage, "Unable to find or open the file: %s", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// 读入文件信息
	ReadObjFile(pModel);

	//让模型绕固定点旋转，比如绕模型的一个Z坐标最小的点旋转，
	//则要求出最小Z坐标，然后把模型所有的Z坐标都平移一下，再旋转即可
		

	// 计算顶点的法向量，用于光照
	ComputeNormals(pModel);

	// 关闭打开的文件
	fclose(m_FilePointer);

	return true;
}


//  读入obj文件中的对象到模型中
void DGObjLoader::ReadObjFile(t3DModel *pModel)
{
	char strLine[255]		= {0};
	char ch					= 0;

	while(!feof(m_FilePointer))
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;

		// 获得obj文件中的当前行的第一个字符
		ch = fgetc(m_FilePointer);
		switch(ch)
		{
		case 'v':						// 读入的是'v' (后续的数据可能是顶点/法向量/纹理坐标)
			
			// 如果在前面读入的是面的行，那么现在进入的是另一个对象，因此在读入下一个对象之前，
			//  需要将最后对象的数据写入到模型结构体中
			if(m_bJustReadAFace) 
			{
				// 将最后对象的信息保存到模型结构中
				FillInObjectInfo(pModel);
			}

			// 读入点的信息，要区分顶点 ("v")、法向量 ("vn")、纹理坐标 ("vt")
			ReadVertexInfo();
			break;

		case 'f':						// 读入的是'f'
			
			//  读入面的信息
			ReadFaceInfo();
			break;

		default:

			// 略过该行的内容
			fgets(strLine, 100, m_FilePointer);
			break;
		}
	}

	// 保存最后读入的对象
	FillInObjectInfo(pModel);
}


//  下面的函数读入顶点信息('v'是指顶点，'vt'指UV坐标)
void DGObjLoader::ReadVertexInfo()
{
	CVector3 vNewVertex		= {0};
	CVector2 vNewTexCoord	= {0};
	char strLine[255]		= {0};
	char ch = 0;

	// 读入第一个字符，判断读入的是否顶点/法向量/UV坐标
	ch = fgetc(m_FilePointer);

	if(ch == ' ')				// 如果是空格，则必是顶点("v")
	{
		// 读入顶点坐标，格式是"v x y z"
		fscanf(m_FilePointer, "%f %f %f", &vNewVertex.x, &vNewVertex.y, &vNewVertex.z);

		// 读入该行中余下的内容，则文件指针到下一行
		fgets(strLine, 100, m_FilePointer);

		// 添加一个新的顶点到顶点链表中
		m_pVertices.push_back(vNewVertex);
	}
	else if(ch == 't')			// 如果是't'，则必定是纹理坐标("vt")
	{
		// 读入纹理坐标，格式是"vt u v"
		fscanf(m_FilePointer, "%f %f", &vNewTexCoord.x, &vNewTexCoord.y);

		// 读入该行余下的内容，则文件指针指向下一行
		fgets(strLine, 100, m_FilePointer);

		// 添加一个新的纹理坐标到链表中
		m_pTextureCoords.push_back(vNewTexCoord);
		m_bObjectHasUV = true;
	}
	else						// 否则可能是法向量("vn")
	{
		// 由于在最后计算各点的法向量，在这里略过
		fgets(strLine, 100, m_FilePointer);
	}
}


//  下面的函数读入面信息
void DGObjLoader::ReadFaceInfo()
{
	tFace newFace			= {0};
	char strLine[255]		= {0};

	// 判断对象是否具有纹理坐标
	if(m_bObjectHasUV )
	{
		// 读入对象的顶点和纹理坐标索引，格式是"顶点1/纹理坐标1 顶点2/纹理坐标2 顶点3/纹理坐标3"
		fscanf(m_FilePointer, "%d/%d %d/%d %d/%d", &newFace.vertIndex[0], &newFace.coordIndex[0],
												   &newFace.vertIndex[1], &newFace.coordIndex[1],
												   &newFace.vertIndex[2], &newFace.coordIndex[2]);				
	}
	else										// 对象无纹理坐标
	{
		// 读入对象的顶点索引，格式是"顶点1 顶点2 顶点3"
		fscanf(m_FilePointer, "%d %d %d", &newFace.vertIndex[0],
										  &newFace.vertIndex[1],
										  &newFace.vertIndex[2]);				
	}

	// 读入该行余下的内容，则文件指针指向下一行
	fgets(strLine, 100, m_FilePointer);
				
	// 添加一个新面到面链表中
	m_pFaces.push_back(newFace);

	//  设置刚才读入的是面
	m_bJustReadAFace = true;
}


//  下面的函数将读入对象的信息写入模型结构体中
void DGObjLoader::FillInObjectInfo(t3DModel *pModel)
{
	t3DObject newObject = {0};
	int textureOffset = 0, vertexOffset = 0;
	int i = 0;

	// 模型中对象计数器递增
	pModel->numOfObjects++;

	// 添加一个新对象到模型的对象链表中
	pModel->pObject.push_back(newObject);

	// 获得当前对象的指针
	t3DObject *pObject = &(pModel->pObject[pModel->numOfObjects - 1]);

	// 获得面的数量、顶点的数量和纹理坐标的数量
	pObject->numOfFaces   = m_pFaces.size();
	pObject->numOfVerts   = m_pVertices.size();
	pObject->numTexVertex = m_pTextureCoords.size();

	// 如果读入了面
	if(pObject->numOfFaces) 
	{

		// 分配保存面的存储空间
		pObject->pFaces = new tFace [pObject->numOfFaces];
	}

	// 如果读入了点
	if(pObject->numOfVerts) {

		// 分配保存点的存储空间
		pObject->pVerts = new CVector3 [pObject->numOfVerts];
	}	

	// 如果读入了纹理坐标
	if(pObject->numTexVertex) {
		pObject->pTexVerts = new CVector2 [pObject->numTexVertex];
		pObject->bHasTexture = true;
	}	

	// 遍历所有的面
	for(i = 0; i < pObject->numOfFaces; i++)
	{
		// 拷贝临时的面链表到模型链表中
		pObject->pFaces[i] = m_pFaces[i];

		// 判断是否是对象的第一个面
		if(i == 0) 
		{
			// 如果第一索引不是1，则必须略过第一个对象
			if(pObject->pFaces[0].vertIndex[0] != 1) {

				vertexOffset = pObject->pFaces[0].vertIndex[0] - 1;

				// 对于纹理坐标，也进行同样的操作
				if(pObject->numTexVertex > 0) {

					// 当前的索引剪去1
					textureOffset = pObject->pFaces[0].coordIndex[0] - 1;
				}
			}					
		}

		for(int j = 0; j < 3; j++)
		{
			//  对于每一个索引，必须将其减去1
			pObject->pFaces[i].vertIndex[j]  -= 1 + vertexOffset;
			pObject->pFaces[i].coordIndex[j] -= 1 + textureOffset;
		}
	}

	// 遍历对象中的所有点
	for(i = 0; i < pObject->numOfVerts; i++)
	{
		// 将当前的顶点从临时链表中拷贝到模型链表中
		pObject->pVerts[i] = m_pVertices[i];
	}

	// 遍历对象中所有的纹理坐标
	for(i = 0; i < pObject->numTexVertex; i++)
	{
		// 将当前的纹理坐标从临时链表中拷贝到模型链表中
		pObject->pTexVerts[i] = m_pTextureCoords[i];
	}

	//  由于OBJ文件中没有材质，因此将materialID设置为-1，必须手动设置材质
	pObject->materialID = -1;

	//  清除所有的临时链表
	m_pVertices.clear();
	m_pFaces.clear();
	m_pTextureCoords.clear();

	// 设置所有的布尔值为false
	m_bObjectHasUV   = false;
	m_bJustReadAFace = false;
}


//  下面的函数为对象序列中的对象赋予具体的材质
void DGObjLoader::SetObjectMaterial(t3DModel *pModel, int whichObject, int materialID)
{
	// 确保模型合法
	if(!pModel) return;

	// 确保对象合法
	if(whichObject >= pModel->numOfObjects) return;

	// 给对象赋予材质ID
	pModel->pObject[whichObject].materialID = materialID;
}


//  下面的函数给模型手动添加材质
void DGObjLoader::AddMaterial(t3DModel *pModel, char *strName, char *strFile, int r, int g, int b)
{
	tMaterialInfo newMaterial = {0};

	// 设置材质的RGB值[0 - RED		1 - GREEN	2 - BLUE]
	newMaterial.color[0] = r; newMaterial.color[1] = g; newMaterial.color[2] = b;

	// 如果具有文件名称，则将其拷贝到材质结构体中
	if(strFile) {
		strcpy(newMaterial.strFile, strFile);
	}

	// 如果具有材质名称，则将其拷贝到材质结构体中
	if(strName) {
		strcpy(newMaterial.strName, strName);
	}

	//  将材质加入到模型链表中
	pModel->pMaterials.push_back(newMaterial);

	// 材质数量递增
	pModel->numOfMaterials++;
}



//  下面的函数用于计算对象的法向量
void DGObjLoader::ComputeNormals(t3DModel *pModel)
{
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	// 如果模型中没有对象，则返回
	if(pModel->numOfObjects <= 0)
		return;

	// 遍历模型中所有的对象
	for(int index = 0; index < pModel->numOfObjects; index++)
	{
		// 获得当前的对象
		t3DObject *pObject = &(pModel->pObject[index]);

		// 分配需要的存储空间
		CVector3 *pNormals		= new CVector3 [pObject->numOfFaces];
		CVector3 *pTempNormals	= new CVector3 [pObject->numOfFaces];
		pObject->pNormals		= new CVector3 [pObject->numOfVerts];

		// 遍历对象的所有面
		for(int i=0; i < pObject->numOfFaces; i++)
		{												
			vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

			// 计算面的法向量

			vVector1 = Vector(vPoly[0], vPoly[2]);		// 获得多边形的矢量
			vVector2 = Vector(vPoly[2], vPoly[1]);		// 获得多边形的第二个矢量

			vNormal  = Cross(vVector1, vVector2);		// 获得两个矢量的叉积
			pTempNormals[i] = vNormal;					// 保存非规范化法向量
			vNormal  = Normalize(vNormal);				// 规范化获得的叉积

			pNormals[i] = vNormal;						// 将法向量添加到法向量列表中
		}

		//  下面求顶点法向量
		CVector3 vSum = {0.0, 0.0, 0.0};
		CVector3 vZero = vSum;
		int shared=0;
		// 遍历所有的顶点
		for (int i = 0; i < pObject->numOfVerts; i++)			
		{
			for (int j = 0; j < pObject->numOfFaces; j++)	// 遍历所有的三角形面
			{												// 判断该点是否与其它的面共享
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{
					vSum = AddVector(vSum, pTempNormals[j]);
					shared++;								
				}
			}      
			
			pObject->pNormals[i] = DivideVectorByScaler(vSum, float(-shared));

			// 规范化最后的顶点法向
			pObject->pNormals[i] = Normalize(pObject->pNormals[i]);	

			vSum = vZero;								
			shared = 0;										
		}
	
		// 释放存储空间，开始下一个对象
		delete [] pTempNormals;
		delete [] pNormals;
	}
}
