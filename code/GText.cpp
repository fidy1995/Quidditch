#include "GText.h"

GLvoid GText::BuildFont(HDC *hDC)						// 创建位图字体
{
	HFONT	font;							// 字体句柄
	HFONT	oldfont;						// 旧的字体句柄
	base = glGenLists(96);					// 创建96个显示列表
	font = CreateFont(-24, 0, 0, 0, FW_BOLD,
		FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
		"Comic Sans MS");
	oldfont = (HFONT)SelectObject(*hDC, font);			// 选择我们需要的字体
	wglUseFontBitmaps(*hDC, 32, 96, base);				// 创建96个显示列表，绘制从ASCII码为32-128的字符
	SelectObject(*hDC, oldfont);							// 选择原来的字体
	DeleteObject(font);									// 删除字体
}

GLvoid GText::KillFont(GLvoid)						// 删除显示列表
{
	glDeleteLists(base, 96);						//删除96个显示列表
}

GLvoid GText::glPrint(double x, double y, const char *fmt, ...)					// 自定义GL输出字体函数
{
	glRasterPos2f(x, y);
	char		text[256];				// 保存文字串
	va_list		ap;						// 指向一个变量列表的指针
	if (fmt == NULL)						// 如果无输入则返回
		return;
	va_start(ap, fmt);						// 分析可变参数
	vsprintf_s(text, 256, fmt, ap);				// 把参数值写入字符串
	va_end(ap);								// 结束分析
	glPushAttrib(GL_LIST_BIT);					// 把显示列表属性压入属性堆栈
	glListBase(base - 32);						// 设置显示列表的基础值
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);		// 调用显示列表绘制字符串
	glPopAttrib();						// 弹出属性堆栈
}