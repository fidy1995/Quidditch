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
	GLuint	base;			// �����������ʾ�б�Ŀ�ʼλ��

	// ����λͼ����
	GLvoid BuildFont(HDC *hDC);

public:
	GText() {}
	GText(HDC *hDC) {
		BuildFont(hDC);
	}

	// ɾ����ʾ�б�
	GLvoid KillFont(GLvoid);
	// �Զ���GL������庯��
	GLvoid glPrint(double x, double y, const char *fmt, ...);
};

#endif //_G_TEXT