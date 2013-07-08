#include "dg_light.h"

GLfloat lightAmbient[] = {0.5, 0.5f, 0.5f, 1.0f}; //环境光
GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; //漫射光
GLfloat lightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //光源位置

DGLight::DGLight(void)
{

}


DGLight::~DGLight(void)
{
}

void DGLight::start(){
	//初始化光源
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient); //设置环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse); //漫射光
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition); //光源位置

	glEnable(GL_LIGHT1);
}

void DGLight::draw(){

}

void DGLight::update(DGContext* ctx){
	DGInput* input = ctx->getInput();

	if (input->getKey('L') && !lp) {
		lp = TRUE;

		light = !light;

		if (!light) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}
	}

	if (!input->getKey('L')) {
		lp = FALSE;
	}
}