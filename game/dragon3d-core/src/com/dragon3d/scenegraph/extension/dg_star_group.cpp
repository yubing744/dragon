#include "dg_star_group.h"

DGStarGroup::DGStarGroup(void)
{
}


DGStarGroup::~DGStarGroup(void)
{
}

void DGStarGroup::start(){
	//载入纹理
	if (!loadGLTexture("Assets/Data/Star.bmp", &starTextures[0])) {
		throw new DGException("star group texture load faild!");
	}

	//初始化星星
	int loop;
	for (loop=0; loop<starNum; loop++) {
		stars[loop].angle = (loop * 1.0f/starNum) * 360.0f * 3;
		stars[loop].dist = (loop * 1.0f/starNum) * 5.0f;

		stars[loop].r = rand() % 256 * 1.0f / 256;
		stars[loop].g = rand() % 256 * 1.0f / 256;
		stars[loop].b = rand() % 256 * 1.0f / 256;
	}

	starZoom = 15.0f;
	starTilt = 30.0f;
	starSpin = 0.0f;
}

void DGStarGroup::draw(DGContext* ctx){
	//显示旋转的星星
	glBindTexture(GL_TEXTURE_2D, starTextures[0]);

	int loop;
	for (loop=0; loop<starNum; loop++) {
		Star* star = &stars[loop];

		glPushMatrix();
		
		glTranslatef(0.0f, 0.0f, -60.0f); 

		glRotatef(starTilt, 1.0f, 0.0f, 0.0f);
		glRotatef(starSpin + star->angle, 0.0f, 1.0f, 0.0f);

		glTranslatef(star->dist, 0.0f, 0.0f);

		glRotatef(-starSpin-star->angle, 0.0f, 1.0f, 1.0f);
		glRotatef(-starTilt, 1.0f, 0.0f, 0.0f);

		glColor3f(star->r, star->g, star->b);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 0.0f);
		glEnd();

		glPopMatrix();
	}
	
	starTilt+=0.02f;
	starSpin-=0.2f;
}

void DGStarGroup::update(DGContext* ctx){

}