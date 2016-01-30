#include "GLight.h"
#include <gl/glew.h>

using namespace std;

GLight::GLight() {
	GLfloat ambientLight[] = { 0.6f, 0.6f, 0.6f, 0.6f };//白色主光源环境光  
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//白色主光源漫反射  
	GLfloat specularLight[] = { 0.3f, 0.3f, 0.3f, 0.3f };//白色主光源镜面光  

	GLfloat lightPos[] = { 0.0f, 10.0f, 3.0f, 1.0f };  //光源位置  

	glEnable(GL_LIGHTING);                          //启用光照  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //设置环境光源  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //设置漫反射光源  
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //设置镜面光源  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //设置灯光位置  
	glEnable(GL_LIGHT0);                            //打开白色主光源  

	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat direction[] = { 0.0f, -1.0f, 0.0f };
	GLfloat spotPos[] = { 0.0f, 10.0f, -8.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, spotPos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, specular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 5.0f);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);                        //启用材质的颜色跟踪  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   //指定材料着色的面  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);   //指定材料对镜面光的反应  
	glMateriali(GL_FRONT, GL_SHININESS, 100);             //指定反射系数  
}