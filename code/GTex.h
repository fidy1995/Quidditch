#ifndef _G_TEX_
#define _G_TEX_

#include <Windows.h>
#include <gl/glew.h>
#include <gl/GLUT.H>
#include <gl/GLAUX.H>

class GTex {
	GLuint texture[15];
	AUX_RGBImageRec *LoadBMP(char *Filename);
	int LoadGLTextures(char *textureName, int index);

public:
	GTex();
	void init();
	GLuint const getTexture(int index) const;
};

#endif  //_G_TEX_