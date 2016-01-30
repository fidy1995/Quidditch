#include "GTex.h"

#include <fstream>
using namespace std;

AUX_RGBImageRec *GTex::LoadBMP(char *Filename) {
	// 确保文件名已提供
	if (!Filename) {
		return NULL;								// 如果没提供，返回 NULL
	}

	ifstream ifs(Filename);							// 尝试打开文件

	// 文件存在么?
	if (!ifs.bad() && !ifs.fail()) {
		ifs.close();								// 关闭句柄
		return auxDIBImageLoad(Filename);			// 载入位图并返回指针
	}

	// 载入失败
	return NULL;
}

// 载入位图并转换成纹理
int GTex::LoadGLTextures(char *textureName, int index) {
	int Status = FALSE;								// 状态指示器
	AUX_RGBImageRec *TextureImage[1];				// 创建纹理的存储空间
	memset(TextureImage, 0, sizeof(void *)* 1);		// 将指针设为 NULL

	// 载入位图，检查有无错误，如果位图没找到则退出
	if (TextureImage[0] = LoadBMP(textureName)) {
		Status = TRUE;								// 将 Status 设为 TRUE
														

		// 创建线性滤波纹理
		glBindTexture(GL_TEXTURE_2D, texture[index]);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			GL_LINEAR);									// 线形滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_LINEAR);									// 线形滤波
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX,
			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
			TextureImage[0]->data);

		//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	}
	if (TextureImage[0])							// 纹理是否存在
	{
		// 纹理图像是否存在
		if (TextureImage[0]->data) {
			free(TextureImage[0]->data);			// 释放纹理图像占用的内存
		}
		free(TextureImage[0]);						// 释放图像结构
	}
	if (!Status) {
		exit(index);
	}
	return Status;									// 返回 Status
}

GTex::GTex() {
	for (int i = 0; i < 20; i++) {
		texture[i] = 0;
	}
	init();
}

void GTex::init() {
	glGenTextures(20, texture); // 创建纹理	
	if (   !LoadGLTextures("ctexture.bmp", 0)		// 母球纹理，编号0
		|| !LoadGLTextures("qtexture.bmp", 1)		// 静球纹理，编号1
		|| !LoadGLTextures("ntexture.bmp", 2)		// 动球纹理，编号2
		|| !LoadGLTextures("gtexture.bmp", 3)		// 金球纹理，编号3
		|| !LoadGLTextures("ttexture.bmp", 4)		// 桌面纹理，编号4
		|| !LoadGLTextures("flag.bmp", 5)			// 旗帜纹理，编号5
		|| !LoadGLTextures("pole.bmp", 6)			// 桌腿纹理，编号6
		|| !LoadGLTextures("wall.bmp", 7)			// 墙面纹理，编号7
		|| !LoadGLTextures("floor.bmp", 8)			// 地面纹理，编号8
		|| !LoadGLTextures("ceil.bmp", 9)			// 屋顶纹理，编号9
		|| !LoadGLTextures("bat.bmp", 10)			// 球杆纹理，编号10
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