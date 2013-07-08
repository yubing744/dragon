#include "dg_yramid.h"
#include "dg_exception.h"

DGYramid::DGYramid(void)
{
}


DGYramid::~DGYramid(void)
{
}


void DGYramid::start(){
	//载入纹理
	if (!loadGLTexture("Assets/Data/texture_desktop.bmp", &texture[0])) {
		throw new DGException("yramid texture load faild!");
	}

	//初始化混合
	//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	rotTriangle = 0.0f;

	blend = FALSE;
	bp = FALSE;

    this->transform->position = DGVector3(0, -2.0f, 2.0f);

	DGGameObject::start();
}

void DGYramid::draw(DGContext* ctx){
	glTranslatef(0.0f, 0.0f, -6.0f);

	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(rotTriangle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);

		//面1
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);


		//面2
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);


		//面3
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		//面4
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	rotTriangle+=0.05f;
}

void DGYramid::update(DGContext* ctx){
	DGInput* input = ctx->getInput();

	if (input->getKey('B') && !bp)				// B 健按下且bp为 FALSE么?
	{
		bp=TRUE;				// 若是， bp 设为 TRUE
		blend = !blend;				// 切换混合选项的 TRUE / FALSE

		if(blend)				// 混合打开了么?
		{
			glEnable(GL_BLEND);		// 打开混合
			glDisable(GL_DEPTH_TEST);	// 关闭深度测试
		}
		else					// 否则
		{
			glDisable(GL_BLEND);		// 关闭混合
			glEnable(GL_DEPTH_TEST);	// 打开深度测试
		}
	}

	if (!input->getKey('B'))		//  B 键松开了么?
	{
		bp=FALSE;				// 若是， bp设为 FALSE
	}
}