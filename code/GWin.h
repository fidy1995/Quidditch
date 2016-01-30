#ifndef _G_WIN_
#define _G_WIN_

#include "game.h"
#include "perlin.h"

#include "GBat.h"
#include "GLight.h"
#include "GSphere.h"
#include "GTable.h"
#include "GTex.h"
#include "GFlag.h"
#include "GRoom.h"
#include "GParticle.h"
#include "GText.h"

#include <time.h>
#include <fstream>
#include <Windows.h>

#include <gl/glew.h>
#include <gl/GLUT.H>
#include <gl/GLAUX.H>

class GWin {
	Game *game;
	GSphere *gsphere[14];
	GTable *gtable;
	GRoom *groom;
	GBat *gbat;
	GFlag *gflag;
	GLight *glight;
	GTex *gtex;
	GParticle *gpart;
	GText *gtext;

	HGLRC hRC = NULL;
	HDC hDC = NULL;
	HWND hWnd = NULL;
	HINSTANCE hInstance = NULL;

	bool fullscreen = true;

	BOOL light, lp, fp; // 光源，按下l键和f键
	GLfloat xrot = 15.0f, yrot = 0; // 沿着轴的旋转角度
	GLfloat x = 0.0f, y = 0.0f, z = -8.0f; // 深入屏幕的距离

	LPCSTR className = "OpenG";

	double force, angle;
	bool gameOver, batAvail;
	Perlin *perlin;
	Bat *b;
	int fps;
	LARGE_INTEGER t1, t2, tc;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	BOOL CreateGLWindow(char* title, int width, int height,
		int bits, bool fullscreenflag);
	GLvoid KillGLWindow(GLvoid);
	int DrawGLScene(GLvoid);
	int InitGL(GLvoid);
	static GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	void resetGameWindow();
public:
	GWin();

	int run(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow);
};

#endif // _G_WIN_