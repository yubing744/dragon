#include "dg_banner.h"
#include <math.h>

DGBanner::DGBanner(void)
{
}


DGBanner::~DGBanner(void)
{
}

void DGBanner::start(){
	wiggle_count = 0;

	//载入纹理
	if (!loadGLTexture("Assets/Textures/Tim.bmp", &texture[0])) {
		throw new DGException("yramid texture load faild!");
	}

	glPolygonMode(GL_BACK, GL_FILL); // 后表面完全填充
	glPolygonMode(GL_FRONT, GL_LINE); // 前表面使用线条绘制

	//初始化网格上的点
	for (int x=0; x<45; x++) {
		for (int y=0; y<45; y++) {
			this->points[x][y].x = x/5.0f - 4.5f;
			this->points[x][y].y = y/5.0f - 4.5f;
			this->points[x][y].z = sin((((x/5.0f)*40.0f)/360.0f)* DGMathf::PI *2.0f);
		}
	}

	this->transform->position = DGVector3(0, 2.0f, 4.0f);
	this->transform->rotation = DGQuaternion(90.0f, 0, 0, 0);
}

void DGBanner::update(DGContext* ctx){
	if( wiggle_count == 2 ){
		for(int y = 0; y < 45; y++ )			// 沿Y平面循环
		{
			hold = points[0][y].z;			// 存储当前左侧波浪值
			for(int x = 0; x < 44; x++)		// 沿X平面循环
			{
				// 当前波浪值等于其右侧的波浪值
				points[x][y].z = points[x+1][y].z;
			}
			points[44][y].z=hold;			// 刚才的值成为最左侧的波浪值
		}

		wiggle_count = 0;				// 计数器清零
	}

	wiggle_count++;
}

void DGBanner::draw(DGContext* ctx){
	DGGameObject::draw(ctx);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	int x, y;	
	float float_x, float_y, float_xb, float_yb;

	glBegin(GL_QUADS);

	for (int x=0; x<44; x++) {
		for (int y=0; y<44; y++) {
			float_x = float(x)/44.0f;		// 生成X浮点值
			float_y = float(y)/44.0f;		// 生成Y浮点值
			float_xb = float(x+1)/44.0f;		// X浮点值+0.0227f
			float_yb = float(y+1)/44.0f;		// Y浮点值+0.0227f

			glTexCoord2f(float_x, float_y);	// 第一个纹理坐标 (左下角)
			glVertex3f(points[x][y].x, points[x][y].y, points[x][y].z);

			glTexCoord2f(float_x, float_yb);	// 第二个纹理坐标 (左上角)
			glVertex3f(points[x][y+1].x, points[x][y+1].y, points[x][y+1].z);

			glTexCoord2f( float_xb, float_yb);	// 第三个纹理坐标 (右上角)
			glVertex3f(points[x+1][y+1].x, points[x+1][y+1].y, points[x+1][y+1].z);

			glTexCoord2f( float_xb, float_y);	// 第四个纹理坐标 (右下角)
			glVertex3f(points[x+1][y].x, points[x+1][y].y, points[x+1][y].z);
		}
	}

	glEnd();
}
