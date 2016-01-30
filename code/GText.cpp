#include "GText.h"

GLvoid GText::BuildFont(HDC *hDC)						// ����λͼ����
{
	HFONT	font;							// ������
	HFONT	oldfont;						// �ɵ�������
	base = glGenLists(96);					// ����96����ʾ�б�
	font = CreateFont(-24, 0, 0, 0, FW_BOLD,
		FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
		"Comic Sans MS");
	oldfont = (HFONT)SelectObject(*hDC, font);			// ѡ��������Ҫ������
	wglUseFontBitmaps(*hDC, 32, 96, base);				// ����96����ʾ�б����ƴ�ASCII��Ϊ32-128���ַ�
	SelectObject(*hDC, oldfont);							// ѡ��ԭ��������
	DeleteObject(font);									// ɾ������
}

GLvoid GText::KillFont(GLvoid)						// ɾ����ʾ�б�
{
	glDeleteLists(base, 96);						//ɾ��96����ʾ�б�
}

GLvoid GText::glPrint(double x, double y, const char *fmt, ...)					// �Զ���GL������庯��
{
	glRasterPos2f(x, y);
	char		text[256];				// �������ִ�
	va_list		ap;						// ָ��һ�������б��ָ��
	if (fmt == NULL)						// ����������򷵻�
		return;
	va_start(ap, fmt);						// �����ɱ����
	vsprintf_s(text, 256, fmt, ap);				// �Ѳ���ֵд���ַ���
	va_end(ap);								// ��������
	glPushAttrib(GL_LIST_BIT);					// ����ʾ�б�����ѹ�����Զ�ջ
	glListBase(base - 32);						// ������ʾ�б�Ļ���ֵ
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);		// ������ʾ�б�����ַ���
	glPopAttrib();						// �������Զ�ջ
}