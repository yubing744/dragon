/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/


#include <com/dragon3d/scene/light/Light.h>

Import com::dragon3d::scene::light;

Light::Light() {

}

Light::~Light() {

}


/*

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

 */