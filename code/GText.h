#ifndef _G_TEXT_
#define _G_TEXT_

#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#include <Windows.h>

#include <gl/glew.h>
#include <gl/GLUT.H>

using namespace std;

class GText {
	GLuint	base;			// 绘制字体的显示列表的开始位置

	// 创建位图字体
	GLvoid BuildFont(HDC *hDC);

public:
	GText() {}
	GText(HDC *hDC) {
		BuildFont(hDC);
	}

	// 删除显示列表
	GLvoid KillFont(GLvoid);
	// 自定义GL输出字体函数
	GLvoid glPrint(double x, double y, const char *fmt, ...);
};

#endif //_G_TEXT