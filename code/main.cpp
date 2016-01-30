//#include <fstream>
//#include <Windows.h>
//#include <gl/glew.h>
//#include <gl/GLUT.H>
//#include <gl/GLAUX.H>
//
//using namespace std;
//
//HGLRC hRC = NULL;
//HDC hDC = NULL;
//HWND hWnd = NULL;
//HINSTANCE hInstance = NULL;
//
//bool keys[256];
//bool active = true;
//bool fullscreen = true;
//
//BOOL light, lp, fp; // 光源，按下l键和f键
//
//char* picName = "test.bmp";
//
//GLfloat rtri; // 三角形旋转的角度
//GLfloat rquad; // 四边形旋转的角度
//GLfloat xrot, yrot, zrot; // 沿着3个轴的旋转角度
//GLfloat xspeed, yspeed; // 沿着2个轴的旋转速度
//GLfloat x = 0.0f, y = 0.0f, z = -5.0f; // 深入屏幕的距离
//GLuint texture[3]; // 3种纹理的储存位置
//GLuint	filter;	// 滤波类型
//
//GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // 环境光参数
//GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 漫射光参数
//GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f }; // 光源位置
//
//LPCSTR className = "OpenG";
//
//LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//class LoadTextureError {};
//
//// 载入位图图象
//AUX_RGBImageRec *LoadBMP(char *Filename) {
//	// 确保文件名已提供
//	if (!Filename) {
//		return NULL;								// 如果没提供，返回 NULL
//	}
//
//	ifstream ifs(Filename);							// 尝试打开文件
//
//	// 文件存在么?
//	if (!ifs.bad() && !ifs.fail()) {
//		ifs.close();								// 关闭句柄
//		return auxDIBImageLoad(Filename);			// 载入位图并返回指针
//	}
//
//	// 载入失败
//	return NULL;
//}
//
//// 载入位图并转换成纹理
//int LoadGLTextures(char *textureName) {
//	int Status = FALSE;								// 状态指示器
//	AUX_RGBImageRec *TextureImage[1];				// 创建纹理的存储空间
//	memset(TextureImage, 0, sizeof(void *)* 1);		// 将指针设为 NULL
//
//	// 载入位图，检查有无错误，如果位图没找到则退出
//	if (TextureImage[0] = LoadBMP(textureName)) {
//		Status = TRUE;								// 将 Status 设为 TRUE
//		glGenTextures(3, &texture[0]);				// 创建纹理		
//		// 使用来自位图数据生成的典型纹理
//		glBindTexture(GL_TEXTURE_2D, texture[0]);
//		// 生成纹理
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, 
//			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
//			TextureImage[0]->data);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//			GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
//			GL_NEAREST);								
//
//		// 创建线性滤波纹理
//		glBindTexture(GL_TEXTURE_2D, texture[1]);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
//			GL_LINEAR);									// 线形滤波
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
//			GL_LINEAR);									// 线形滤波
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX,
//			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
//			TextureImage[0]->data);
//
//		// 创建 MipMapped 纹理
//		glBindTexture(GL_TEXTURE_2D, texture[2]);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
//			GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
//			GL_LINEAR_MIPMAP_NEAREST);
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX,
//			TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
//			TextureImage[0]->data);
//	}
//	if (TextureImage[0])							// 纹理是否存在
//	{
//		// 纹理图像是否存在
//		if (TextureImage[0]->data) {
//			free(TextureImage[0]->data);			// 释放纹理图像占用的内存
//		}
//		free(TextureImage[0]);						// 释放图像结构
//	}
//	return Status;									// 返回 Status
//}
//
//GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
//{
//	if (height == 0) {
//		height = 1;
//	}
//	glViewport(0, 0, width, height);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//int InitGL(GLvoid)
//{
//	try {
//		// 调用纹理载入子例程
//		if (!LoadGLTextures(picName)) {
//			throw LoadTextureError();					// 如果未能载入，返回FALSE
//		}
//		F						// 启用纹理映射
//		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	// 设置环境光
//		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	// 设置漫射光
//		glLightfv(GL_LIGHT1, 
//			GL_POSITION, LightPosition);				// 设置光源位置
//		glEnable(GL_LIGHT1);							// 启用一号光源
//		glShadeModel(GL_SMOOTH);
//		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//		glClearDepth(1.0f);
//		glEnable(GL_DEPTH_TEST);
//		glDepthFunc(GL_LEQUAL);
//		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//		return TRUE;
//	}
//	catch (...) {
//		return FALSE;
//	}
//}
//
//// 此过程中包括所有的绘制代码
//int DrawGLScene(GLvoid)
//{
//	try {
//		// 清除屏幕及深度缓存
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		// 重置当前的模型观察矩阵
//		glLoadIdentity();
//		glTranslatef(x, y, z);				// 移入屏幕 z 个单位
//
//		glRotatef(xrot, 1.0f, 0.0f, 0.0f);			// 绕X轴旋转
//		glRotatef(yrot, 0.0f, 1.0f, 0.0f);			// 绕Y轴旋转
//		glRotatef(zrot, 0.0f, 0.0f, 1.0f);			// 绕Z轴旋转
//
//		glBindTexture(GL_TEXTURE_2D, 
//			texture[filter]);						// 选择由filter决定的纹理
//
//		glBegin(GL_QUADS);
//		// 前面
//		glNormal3f(0.0f, 0.0f, 1.0f);				// 法线指向观察者
//		glTexCoord2f(0.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 纹理和四边形的左下
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 纹理和四边形的右下
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, 1.0f);				// 纹理和四边形的右上
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// 纹理和四边形的左上
//		
//		// 后面
//		glNormal3f(0.0f, 0.0f, -1.0f);				// 法线背向观察者
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// 纹理和四边形的右下
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// 纹理和四边形的右上
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(1.0f, 1.0f, -1.0f);				// 纹理和四边形的左上
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(1.0f, -1.0f, -1.0f);				// 纹理和四边形的左下
//
//		// 顶面
//		glNormal3f(0.0f, 1.0f, 0.0f);				// 法线向上
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// 纹理和四边形的左上
//		glTexCoord2f(0.0f, 0.0f); 
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// 纹理和四边形的左下
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex3f(1.0f, 1.0f, 1.0f);				// 纹理和四边形的右下
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, -1.0f);				// 纹理和四边形的右上
//
//		// 底面
//		glNormal3f(0.0f, -1.0f, 0.0f);				// 法线朝下
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// 纹理和四边形的右上
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(1.0f, -1.0f, -1.0f);				// 纹理和四边形的左上
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 纹理和四边形的左下
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 纹理和四边形的右下
//
//		// 右面
//		glNormal3f(1.0f, 0.0f, 0.0f);				// 法线朝右
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(1.0f, -1.0f, -1.0f);				// 纹理和四边形的右下
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, -1.0f);				// 纹理和四边形的右上
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, 1.0f);				// 纹理和四边形的左上
//		glTexCoord2f(0.0f, 0.0f); 
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 纹理和四边形的左下
//
//		// 左面
//		glNormal3f(-1.0f, 0.0f, 0.0f);				// 法线朝左
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// 纹理和四边形的左下
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 纹理和四边形的右下
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// 纹理和四边形的右上
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// 纹理和四边形的左上
//
//		glEnd();
//
//		/*// 左移 1.5 单位，并移入屏幕 6.0
//		glTranslatef(-1.5f, 0.0f, -6.0f);
//		glRotatef(rtri, 0.0f, 1.0f, 0.0f);			// 绕Y轴旋转三角形
//
//		glBegin(GL_TRIANGLES);						// 绘制四面体
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// 红色
//		glVertex3f(0.0f, 1.0f, 0.0f);				// 三角形的上顶点 (前侧面)
//		glColor3f(0.0f, 1.0f, 0.0f);				// 绿色
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 三角形的左下顶点 (前侧面)
//		glColor3f(0.0f, 0.0f, 1.0f);				// 蓝色
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 三角形的右下顶点 (前侧面)
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// 红色
//		glVertex3f(0.0f, 1.0f, 0.0f);				// 三角形的上顶点 (右侧面)
//		glColor3f(0.0f, 0.0f, 1.0f);				// 蓝色
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 三角形的左下顶点 (右侧面)
//		glColor3f(0.0f, 1.0f, 0.0f);				// 绿色
//		glVertex3f(0.0f, -1.0f, -1.0f);				// 三角形的右下顶点 (右侧面)
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// 红色
//		glVertex3f(0.0f, 1.0f, 0.0f);				// 三角形的上顶点 (后侧面)
//		glColor3f(0.0f, 1.0f, 0.0f);				// 绿色
//		glVertex3f(0.0f, -1.0f, -1.0f);				// 三角形的左下顶点 (后侧面)
//		glColor3f(0.0f, 0.0f, 1.0f);				// 蓝色
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 三角形的右下顶点 (后侧面)
//
//		glEnd();
//
//		glLoadIdentity();							// 重置模型观察矩阵
//		glTranslatef(1.5f, 0.0f, -7.0f);			// 右移1.5单位,并移入屏幕7.0
//		glRotatef(rquad, 1.0f, 1.0f, 1.0f);			// 绕X轴旋转四边形
//
//		glBegin(GL_QUADS);							// 绘制六面体
//
//		glColor3f(0.0f, 1.0f, 0.0f);				// 颜色改为绿色
//		glVertex3f(1.0f, 1.0f, -1.0f);				// 四边形的右上顶点 (顶面)
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// 四边形的左上顶点 (顶面)
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// 四边形的左下顶点 (顶面)
//		glVertex3f(1.0f, 1.0f, 1.0f);				// 四边形的右下顶点 (顶面)
//
//		glColor3f(1.0f, 0.5f, 0.0f);				// 颜色改成橙色
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 四边形的右上顶点(底面)
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 四边形的左上顶点(底面)
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// 四边形的左下顶点(底面)
//		glVertex3f(1.0f, -1.0f, -1.0f);				// 四边形的右下顶点(底面)
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// 颜色改成红色
//		glVertex3f(1.0f, 1.0f, 1.0f);				// 四边形的右上顶点(前面)
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// 四边形的左上顶点(前面)
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 四边形的左下顶点(前面)
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 四边形的右下顶点(前面)
//
//		glColor3f(1.0f, 1.0f, 0.0f);				// 颜色改成黄色
//		glVertex3f(1.0f, -1.0f, -1.0f);				// 四边形的右上顶点(后面)
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// 四边形的左上顶点(后面)
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// 四边形的左下顶点(后面)
//		glVertex3f(1.0f, 1.0f, -1.0f);				// 四边形的右下顶点(后面)
//
//		glColor3f(0.0f, 0.0f, 1.0f);				// 颜色改成蓝色
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// 四边形的右上顶点(左面)
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// 四边形的左上顶点(左面)
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// 四边形的左下顶点(左面)
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// 四边形的右下顶点(左面)
//
//		glColor3f(1.0f, 0.0f, 1.0f);				// 颜色改成紫罗兰色
//		glVertex3f(1.0f, 1.0f, -1.0f);				// 四边形的右上顶点(右面)
//		glVertex3f(1.0f, 1.0f, 1.0f);				// 四边形的左上顶点(右面)
//		glVertex3f(1.0f, -1.0f, 1.0f);				// 四边形的左下顶点(右面)
//		glVertex3f(1.0f, -1.0f, -1.0f);				// 四边形的右下顶点(右面)
//
//		glEnd();									// 正方形绘制结束
//
//		rtri += 0.02f;								// 增加三角形的旋转变量
//		rquad -= 0.015f;							// 减少四边形的旋转变量*/
//
//
//
//		xrot += xspeed;								// xrot 增加 xspeed 单位
//		yrot += yspeed;								// yrot 增加 yspeed 单位
//		
//		/*glTranslatef(0.0f, 0.0f, -10.0f);
//		glRotatef(xrot, 1.0f, 0.0f, 0.0f);			// 绕Y轴旋转
//		glRotatef(yrot, 0.0f, 1.0f, 0.0f);
//		glColor3f(1.0f, 0.0f, 0.0f);				// 红色
//		
//		glBegin(GL_QUADS);
//		glVertex3f(-2.0f,  0.0f, -4.0f);
//		glVertex3f( 2.0f,  0.0f, -4.0f);
//		glVertex3f( 2.0f, -0.0f,  4.0f);
//		glVertex3f(-2.0f, -0.0f,  4.0f);
//		glEnd();
//		glTranslatef(1.0f, 0.125f, -1.0f);*/
//			/*for (GLfloat j = 0; j < 2 * 3.142; j += 0.001f)
//			{
//				glBegin(GL_QUADS);
//				glColor3f(0.0f, 0.0f, 1.0f);
//				glVertex3f(cos(j), sin(j), -4.0f);
//				glVertex3f(cos(j + 0.001), sin(j + 0.001), -4.0f);
//				glColor3f(1.0f, 0.0f, 0.0f);
//				glVertex3f(cos(j + 0.001), sin(j + 0.001), 4.0f);
//				glVertex3f(cos(j), sin(j), 4.0f);
//				glEnd();
//			}*/
//
//		// 成功的运行总是返回true
//		return TRUE;
//	}
//	catch (...) {
//		return FALSE;
//	}
//}
//
//GLvoid KillGLWindow(GLvoid)
//{
//	if (fullscreen) {
//		ChangeDisplaySettings(NULL, 0);
//		ShowCursor(TRUE);
//	}
//
//	if (hRC) {
//		if (!wglMakeCurrent(NULL, NULL)) {
//			MessageBox(NULL, "释放DC或RC失败。",
//				"关闭错误", MB_OK | MB_ICONINFORMATION);
//		}
//		if (!wglDeleteContext(hRC)) {
//			MessageBox(NULL, "释放RC失败。",
//				"关闭错误", MB_OK | MB_ICONINFORMATION);
//		}
//		hRC = NULL;
//	}
//
//	if (hDC && !ReleaseDC(hWnd, hDC)) {
//		MessageBox(NULL, "释放DC失败。",
//			"关闭错误", MB_OK | MB_ICONINFORMATION);
//		hDC = NULL;
//	}
//
//	if (hWnd && !DestroyWindow(hWnd)) {
//		MessageBox(NULL, "释放窗口句柄失败。",
//			"关闭错误", MB_OK | MB_ICONINFORMATION);
//		hWnd = NULL;
//	}
//
//	if (!UnregisterClass(className, hInstance)) {
//		MessageBox(NULL, "不能注销窗口类。",
//			"关闭错误", MB_OK | MB_ICONINFORMATION);
//		hInstance = NULL;
//	}
//}
//
//BOOL CreateGLWindow(char* title, int width, int height,
//	int bits, bool fullscreenflag)
//{
//	GLuint PixelFormat;
//
//	WNDCLASS wc;
//
//	DWORD dwExStyle;
//	DWORD dwStyle;
//
//	RECT WindowRect;
//	WindowRect.left = (long)0;
//	WindowRect.right = (long)width;
//	WindowRect.top = (long)0;
//	WindowRect.bottom = (long)height;
//
//	fullscreen = fullscreenflag;
//
//	hInstance = GetModuleHandle(NULL);
//
//	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//	wc.lpfnWndProc = (WNDPROC)WndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = NULL;
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = className;
//
//	if (!RegisterClass(&wc)) {
//		MessageBox(NULL, "注册窗口失败", "错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
//
//	if (fullscreen) {
//		DEVMODE dmScreenSettings; // 设备模式
//		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// 确保内存清空为零
//		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // Devmode 结构的大小
//		dmScreenSettings.dmPelsWidth = width; // 所选屏幕宽度
//		dmScreenSettings.dmPelsHeight = height; // 所选屏幕高度
//		dmScreenSettings.dmBitsPerPel = bits; // 每象素所选的色彩深度
//		dmScreenSettings.dmFields =
//			DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
//
//		// 尝试设置显示模式并返回结果。注: CDS_FULLSCREEN 移去了状态条。
//		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)
//			!= DISP_CHANGE_SUCCESSFUL) {
//			// 若模式失败，提供两个选项：退出或在窗口内运行。
//			if (MessageBox(NULL, "全屏模式在当前显卡上设置失败！\n使用窗口模式？",
//				"NeHe G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
//				fullscreen = FALSE;	// 选择窗口模式(Fullscreen=FALSE)
//			}
//			else {
//				MessageBox(NULL, "程序将被关闭", "错误", MB_OK | MB_ICONSTOP);
//				return FALSE;
//			}
//		}
//	}
//	if (fullscreen) {
//		dwExStyle = WS_EX_APPWINDOW;
//		dwStyle = WS_POPUP;
//		ShowCursor(FALSE);
//	}
//	else {
//		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
//		dwStyle = WS_OVERLAPPEDWINDOW;
//	}
//
//	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
//
//	if (!(hWnd = CreateWindowEx(dwExStyle,			// 扩展窗体风格
//		className,									// 类名字
//		title,										// 窗口标题
//		WS_CLIPSIBLINGS |							// 必须的窗体风格属性
//		WS_CLIPCHILDREN |							// 必须的窗体风格属性
//		dwStyle,									// 选择的窗体属性
//		0, 0,										// 窗口位置
//		WindowRect.right - WindowRect.left,			// 计算调整好的窗口宽度
//		WindowRect.bottom - WindowRect.top,			// 计算调整好的窗口高度
//		NULL,										// 无父窗口
//		NULL,										// 无菜单
//		hInstance,									// 实例
//		NULL))) 									// 不向WM_CREATE传递任何东东
//	{
//		KillGLWindow();								// 重置显示区
//		MessageBox(NULL, "不能创建一个窗口设备描述表",
//			"错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// 返回 FALSE
//	}
//	// pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式
//	static	PIXELFORMATDESCRIPTOR pfd =
//	{
//		sizeof(PIXELFORMATDESCRIPTOR),				// 上述格式描述符的大小
//		1,											// 版本号
//		PFD_DRAW_TO_WINDOW |						// 格式支持窗口
//		PFD_SUPPORT_OPENGL |						// 格式必须支持OpenGL
//		PFD_DOUBLEBUFFER,							// 必须支持双缓冲
//		PFD_TYPE_RGBA,								// 申请 RGBA 格式
//		bits,										// 选定色彩深度
//		0, 0, 0, 0, 0, 0,							// 忽略的色彩位
//		0,											// 无Alpha缓存
//		0,											// 忽略Shift Bit
//		0,											// 无累加缓存
//		0, 0, 0, 0,									// 忽略聚集位
//		16,											// 16位 Z-缓存 (深度缓存)
//		0,											// 无蒙板缓存
//		0,											// 无辅助缓存
//		PFD_MAIN_PLANE,								// 主绘图层
//		0,											// Reserved
//		0, 0, 0										// 忽略层遮罩
//	};
//
//	// 取得设备描述表了么?
//	if (!(hDC = GetDC(hWnd)))
//	{
//		KillGLWindow();								// 重置显示区
//		MessageBox(NULL, "不能创建一种相匹配的像素格式",
//			"错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// 返回 FALSE
//	}
//
//	// Windows 找到相应的象素格式了吗?
//	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
//	{
//		KillGLWindow();								// 重置显示区
//		MessageBox(NULL, "不能设置像素格式",
//			"错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// 返回 FALSE
//	}
//
//	// 能够设置象素格式么?
//	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
//	{
//		KillGLWindow();								// 重置显示区
//		MessageBox(NULL, "不能设置像素格式",
//			"错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// 返回 FALSE
//	}
//
//	// 能否取得着色描述表?
//	if (!(hRC = wglCreateContext(hDC)))
//	{
//		KillGLWindow();								// 重置显示区
//		MessageBox(NULL, "不能创建OpenGL渲染描述表",
//			"错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// 返回 FALSE
//	}
//
//	// 尝试激活着色描述表
//	if (!wglMakeCurrent(hDC, hRC))
//	{
//		KillGLWindow();								// 重置显示区
//		MessageBox(NULL, "不能激活当前的OpenGL渲然描述表",
//			"错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// 返回 FALSE
//	}
//
//	ShowWindow(hWnd, SW_SHOW);						// 显示窗口
//	SetForegroundWindow(hWnd);						// 略略提高优先级
//	SetFocus(hWnd);									// 设置键盘的焦点至此窗口
//	ReSizeGLScene(width, height);					// 设置透视 GL 屏幕
//
//	// 初始化新建的GL窗口
//	if (!InitGL())
//	{
//		KillGLWindow();								// 重置显示区
//		MessageBox(NULL, "初始化窗口错误",
//			"错误", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// 返回 FALSE
//	}
//
//	return TRUE;
//}
//
//LRESULT CALLBACK WndProc(
//	HWND	hWnd,									// 窗口的句柄
//	UINT	uMsg,									// 窗口的消息
//	WPARAM	wParam,									// 附加的消息内容
//	LPARAM	lParam)									// 附加的消息内容
//{
//	switch (uMsg) {
//	case WM_ACTIVATE: // 监视窗口激活消息
//	{
//		if (!HIWORD(wParam)) {						// 检查最小化状态
//			active = TRUE;							// 程序处于激活状态
//		}
//		else {
//			active = FALSE;							// 程序不再激活
//		}
//		return 0;									// 返回消息循环
//	}
//	case WM_SYSCOMMAND: // 系统中断命令
//	{
//		switch (wParam) { // 检查系统调用
//		case SC_SCREENSAVE: // 屏保要运行?
//		case SC_MONITORPOWER: // 显示器要进入节电模式?
//			return 0;								// 阻止发生
//		}
//		break;										// 退出
//	}
//	case WM_CLOSE: // 收到Close消息?
//	{
//		PostQuitMessage(0);							// 发出退出消息
//		return 0;									// 返回
//	}
//	case WM_KEYDOWN: // 有键按下么?
//	{
//		keys[wParam] = TRUE;						// 如果是，设为TRUE
//		return 0;									// 返回
//	}
//	case WM_KEYUP: // 有键放开么?
//	{
//		keys[wParam] = FALSE;						// 如果是，设为FALSE
//		return 0;									// 返回
//	}
//	case WM_SIZE: // 调整OpenGL窗口大小
//	{
//		ReSizeGLScene(LOWORD(lParam), 
//			HIWORD(lParam));						// LoWord=Width,HiWord=Height
//		return 0;									// 返回
//	}
//	}
//	// 向DefWindowProc传递所有未处理的消息。
//	return DefWindowProc(hWnd, uMsg, wParam, lParam);
//}
//
//int WINAPI WinMain(
//	HINSTANCE	hInstance,							// 当前窗口实例
//	HINSTANCE	hPrevInstance,						// 前一个窗口实例
//	LPSTR		lpCmdLine,							// 命令行参数
//	int			nCmdShow)							// 窗口显示状态
//{
//	MSG	msg;										// Windowsx消息结构
//	BOOL done = FALSE;								// 用来退出循环的Bool 变量
//
//	// 提示用户选择运行模式
//	if (MessageBox(NULL, "你想在全屏模式下运行么？", 
//		"设置全屏模式", MB_YESNO | MB_ICONQUESTION) == IDNO) {
//		fullscreen = FALSE;							// FALSE为窗口模式
//	}
//
//	// 创建OpenGL窗口
//	if (!CreateGLWindow("NeHe's OpenGL程序框架", 640, 480, 16, fullscreen))
//	{
//		return 0;									// 失败退出
//	}
//
//	// 保持循环直到 done=TRUE
//	while (!done)
//	{
//		// 有消息在等待吗?
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
//			// 收到退出消息?
//			if (msg.message == WM_QUIT)	{
//				done = TRUE;						// 是，则done=TRUE
//			}
//			// 不是，处理窗口消息
//			else {
//				TranslateMessage(&msg);				// 翻译消息
//				DispatchMessage(&msg);				// 发送消息
//			}
//		}
//
//		// 如果没有消息
//		else {
//			// 绘制场景。监视ESC键和来自DrawGLScene()的退出消息
//			// 程序激活的么?
//			if (active) {
//				// ESC 按下了么?
//				if (keys[VK_ESCAPE]) {
//					done = TRUE;					// ESC 发出退出信号
//				}
//				// 不是退出的时候，刷新屏幕
//				else {
//					DrawGLScene();					// 绘制场景
//					SwapBuffers(hDC);				// 交换缓存 (双缓存)
//					// L键已按下并且松开了?
//					if (keys['L'] && !lp) {
//						lp = TRUE;					// lp 设为 TRUE
//						light = !light;				// 切换光源的 TRUE/FALSE
//						// 如果没有光源
//						if (!light)	{
//							glDisable(GL_LIGHTING);	// 禁用光源
//						}
//						// 否则
//						else {
//							glEnable(GL_LIGHTING);	// 启用光源
//						}
//					}
//					// L键松开了么?
//					if (!keys['L']) {
//						lp = FALSE;					// 若是，则将lp设为FALSE
//					}
//					// F键按下了么?
//					if (keys['F'] && !fp) {
//						fp = TRUE;					// fp 设为 TRUE
//						filter += 1;				// filter的值加一
//						// 大于2了么?
//						if (filter>2) {
//							filter = 0;				// 若是重置为0
//						}
//					}
//					// F键放开了么?
//					if (!keys['F']) {
//						fp = FALSE;					// 若是fp设为FALSE
//					}
//					// PageUp按下了?
//					if (keys[VK_PRIOR]) {
//						z -= 0.0002f;					// 若按下，将木箱移向屏幕内部
//					}
//					// PageDown按下了么
//					if (keys[VK_NEXT]) {
//						z += 0.0002f;					// 若按下的话，将木箱移向观察者
//					}
//					// Up方向键按下了么?
//					if (keys[VK_UP]) {
//						xspeed -= 0.0001f;			// 若是,减少xspeed
//					}
//					// Down方向键按下了么?
//					if (keys[VK_DOWN]) {
//						xspeed += 0.0001f;			// 若是,增加xspeed
//					}
//					// Right方向键按下了么?
//					if (keys[VK_RIGHT]) {
//						yspeed += 0.0001f;			// 若是,增加yspeed
//					}
//					// Left方向键按下了么?
//					if (keys[VK_LEFT]) {
//						yspeed -= 0.0001f;			// 若是, 减少yspeed
//					}
//					
//					// move
//					if (keys['W']) {
//						y += 0.0001f;
//					}
//					if (keys['S']) {
//						y -= 0.0001f;
//					}
//					if (keys['A']) {
//						x -= 0.0001f;
//					}
//					if (keys['D']) {
//						x += 0.0001f;
//					}
//
//					// reset
//					if (keys['R']) {
//						x = 0.0f;
//						y = 0.0f;
//						z = -5.0f;
//						xrot = 0.0f;
//						yrot = 0.0f;
//						xspeed = 0.0f;
//						yspeed = 0.0f;
//					}
//					// freeze
//					if (keys['E']) {
//						xspeed = 0.0f;
//						yspeed = 0.0f;
//					}
//					// rotate
//					if (keys['U']) {
//						xrot += 0.01f;
//					}
//					if (keys['J']) {
//						xrot -= 0.01f;
//					}
//					if (keys['H']) {
//						yrot += 0.01f;
//					}
//					if (keys['K']) {
//						yrot -= 0.01f;
//					}
//				}
//			}
//
//			// F11键按下了么?
//			if (keys[VK_F11]) {
//				keys[VK_F11] = FALSE;				// 若是，使对应的Key数组中的值为 FALSE
//				KillGLWindow();						// 销毁当前的窗口
//				fullscreen = !fullscreen;			// 切换 全屏 / 窗口 模式
//				// 重建 OpenGL 窗口
//				if (!CreateGLWindow("NeHe's 第一个多边形程序",
//					640, 480, 16, fullscreen)) {
//					return 0;						// 如果窗口未能创建，程序退出
//				}
//			}
//		}
//	}
//
//	// 关闭程序
//	KillGLWindow();									// 销毁窗口
//	return (msg.wParam);							// 退出程序
//}

#include <time.h>
#include "GWin.h"

int WINAPI WinMain(
	HINSTANCE	hInstance,							// 当前窗口实例
	HINSTANCE	hPrevInstance,						// 前一个窗口实例
	LPSTR		lpCmdLine,							// 命令行参数
	int			nCmdShow)							// 窗口显示状态
{
	try {
		srand((unsigned)time(NULL));
		GWin *gwin = new GWin();
		gwin->run(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
		return 0;
	}
	catch (...) {
		MessageBox(NULL, "Unknown error", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		exit(-1);
	}
}

