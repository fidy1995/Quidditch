#include "GTex.h"

#include <fstream>
using namespace std;

AUX_RGBImageRec *GTex::LoadBMP(char *Filename) {
	// ȷ���ļ������ṩ
	if (!Filename) {
		return NULL;								// ���û�ṩ������ NULL
	}

	ifstream ifs(Filename);							// ���Դ��ļ�

	// �ļ�����ô?
	if (!ifs.bad() && !ifs.fail()) {
		ifs.close();								// �رվ��
		return auxDIBImageLoad(Filename);			// ����λͼ������ָ��
	}

	// ����ʧ��
	return NULL;
}

// ����λͼ��ת��������
int GTex::LoadGLTextures(char *textureName, int index) {
	int Status = FALSE;								// ״ָ̬ʾ��
	AUX_RGBImageRec *TextureImage[1];				// ��������Ĵ洢�ռ�
	memset(TextureImage, 0, sizeof(void *)* 1);		// ��ָ����Ϊ NULL

	// ����λͼ��������޴������λͼû�ҵ����˳�
	if (TextureImage[0] = LoadBMP(textureName)) {
		Status = TRUE;								// �� Status ��Ϊ TRUE
														

		// ���������˲�����
		glBindTexture(GL_TEXTURE_2D, texture[index]);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			GL_LINEAR);									// �����˲�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_LINEAR);									// �����˲�
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX,
			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
			TextureImage[0]->data);

		//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	}
	if (TextureImage[0])							// �����Ƿ����
	{
		// ����ͼ���Ƿ����
		if (TextureImage[0]->data) {
			free(TextureImage[0]->data);			// �ͷ�����ͼ��ռ�õ��ڴ�
		}
		free(TextureImage[0]);						// �ͷ�ͼ��ṹ
	}
	if (!Status) {
		exit(index);
	}
	return Status;									// ���� Status
}

GTex::GTex() {
	for (int i = 0; i < 20; i++) {
		texture[i] = 0;
	}
	init();
}

void GTex::init() {
	glGenTextures(20, texture); // ��������	
	if (   !LoadGLTextures("ctexture.bmp", 0)		// ĸ���������0
		|| !LoadGLTextures("qtexture.bmp", 1)		// �����������1
		|| !LoadGLTextures("ntexture.bmp", 2)		// �����������2
		|| !LoadGLTextures("gtexture.bmp", 3)		// �����������3
		|| !LoadGLTextures("ttexture.bmp", 4)		// �����������4
		|| !LoadGLTextures("flag.bmp", 5)			// �����������5
		|| !LoadGLTextures("pole.bmp", 6)			// �����������6
		|| !LoadGLTextures("wall.bmp", 7)			// ǽ���������7
		|| !LoadGLTextures("floor.bmp", 8)			// �����������8
		|| !LoadGLTextures("ceil.bmp", 9)			// �ݶ��������9
		|| !LoadGLTextures("bat.bmp", 10)			// ����������10
		) {
		exit(-1);
	}
}


GLuint const GTex::getTexture(int index) const {
	if (index < 20) {
		return texture[index];
	}
	return 0;
}