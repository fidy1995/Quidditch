#include "GLight.h"
#include <gl/glew.h>

using namespace std;

GLight::GLight() {
	GLfloat ambientLight[] = { 0.6f, 0.6f, 0.6f, 0.6f };//��ɫ����Դ������  
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };//��ɫ����Դ������  
	GLfloat specularLight[] = { 0.3f, 0.3f, 0.3f, 0.3f };//��ɫ����Դ�����  

	GLfloat lightPos[] = { 0.0f, 10.0f, 3.0f, 1.0f };  //��Դλ��  

	glEnable(GL_LIGHTING);                          //���ù���  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //���û�����Դ  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   //�����������Դ  
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); //���þ����Դ  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      //���õƹ�λ��  
	glEnable(GL_LIGHT0);                            //�򿪰�ɫ����Դ  

	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat direction[] = { 0.0f, -1.0f, 0.0f };
	GLfloat spotPos[] = { 0.0f, 10.0f, -8.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, spotPos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, specular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 5.0f);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);                        //���ò��ʵ���ɫ����  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);   //ָ��������ɫ����  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);   //ָ�����϶Ծ����ķ�Ӧ  
	glMateriali(GL_FRONT, GL_SHININESS, 100);             //ָ������ϵ��  
}