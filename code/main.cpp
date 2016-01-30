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
//BOOL light, lp, fp; // ��Դ������l����f��
//
//char* picName = "test.bmp";
//
//GLfloat rtri; // ��������ת�ĽǶ�
//GLfloat rquad; // �ı�����ת�ĽǶ�
//GLfloat xrot, yrot, zrot; // ����3�������ת�Ƕ�
//GLfloat xspeed, yspeed; // ����2�������ת�ٶ�
//GLfloat x = 0.0f, y = 0.0f, z = -5.0f; // ������Ļ�ľ���
//GLuint texture[3]; // 3������Ĵ���λ��
//GLuint	filter;	// �˲�����
//
//GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; // ���������
//GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ��������
//GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f }; // ��Դλ��
//
//LPCSTR className = "OpenG";
//
//LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//class LoadTextureError {};
//
//// ����λͼͼ��
//AUX_RGBImageRec *LoadBMP(char *Filename) {
//	// ȷ���ļ������ṩ
//	if (!Filename) {
//		return NULL;								// ���û�ṩ������ NULL
//	}
//
//	ifstream ifs(Filename);							// ���Դ��ļ�
//
//	// �ļ�����ô?
//	if (!ifs.bad() && !ifs.fail()) {
//		ifs.close();								// �رվ��
//		return auxDIBImageLoad(Filename);			// ����λͼ������ָ��
//	}
//
//	// ����ʧ��
//	return NULL;
//}
//
//// ����λͼ��ת��������
//int LoadGLTextures(char *textureName) {
//	int Status = FALSE;								// ״ָ̬ʾ��
//	AUX_RGBImageRec *TextureImage[1];				// ��������Ĵ洢�ռ�
//	memset(TextureImage, 0, sizeof(void *)* 1);		// ��ָ����Ϊ NULL
//
//	// ����λͼ��������޴������λͼû�ҵ����˳�
//	if (TextureImage[0] = LoadBMP(textureName)) {
//		Status = TRUE;								// �� Status ��Ϊ TRUE
//		glGenTextures(3, &texture[0]);				// ��������		
//		// ʹ������λͼ�������ɵĵ�������
//		glBindTexture(GL_TEXTURE_2D, texture[0]);
//		// ��������
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, 
//			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, 
//			TextureImage[0]->data);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//			GL_NEAREST);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
//			GL_NEAREST);								
//
//		// ���������˲�����
//		glBindTexture(GL_TEXTURE_2D, texture[1]);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
//			GL_LINEAR);									// �����˲�
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
//			GL_LINEAR);									// �����˲�
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX,
//			TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
//			TextureImage[0]->data);
//
//		// ���� MipMapped ����
//		glBindTexture(GL_TEXTURE_2D, texture[2]);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
//			GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
//			GL_LINEAR_MIPMAP_NEAREST);
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX,
//			TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
//			TextureImage[0]->data);
//	}
//	if (TextureImage[0])							// �����Ƿ����
//	{
//		// ����ͼ���Ƿ����
//		if (TextureImage[0]->data) {
//			free(TextureImage[0]->data);			// �ͷ�����ͼ��ռ�õ��ڴ�
//		}
//		free(TextureImage[0]);						// �ͷ�ͼ��ṹ
//	}
//	return Status;									// ���� Status
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
//		// ������������������
//		if (!LoadGLTextures(picName)) {
//			throw LoadTextureError();					// ���δ�����룬����FALSE
//		}
//		F						// ��������ӳ��
//		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	// ���û�����
//		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	// ���������
//		glLightfv(GL_LIGHT1, 
//			GL_POSITION, LightPosition);				// ���ù�Դλ��
//		glEnable(GL_LIGHT1);							// ����һ�Ź�Դ
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
//// �˹����а������еĻ��ƴ���
//int DrawGLScene(GLvoid)
//{
//	try {
//		// �����Ļ����Ȼ���
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		// ���õ�ǰ��ģ�͹۲����
//		glLoadIdentity();
//		glTranslatef(x, y, z);				// ������Ļ z ����λ
//
//		glRotatef(xrot, 1.0f, 0.0f, 0.0f);			// ��X����ת
//		glRotatef(yrot, 0.0f, 1.0f, 0.0f);			// ��Y����ת
//		glRotatef(zrot, 0.0f, 0.0f, 1.0f);			// ��Z����ת
//
//		glBindTexture(GL_TEXTURE_2D, 
//			texture[filter]);						// ѡ����filter����������
//
//		glBegin(GL_QUADS);
//		// ǰ��
//		glNormal3f(0.0f, 0.0f, 1.0f);				// ����ָ��۲���
//		glTexCoord2f(0.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(1.0f, -1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// ������ı��ε�����
//		
//		// ����
//		glNormal3f(0.0f, 0.0f, -1.0f);				// ���߱���۲���
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// ������ı��ε�����
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(1.0f, 1.0f, -1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(1.0f, -1.0f, -1.0f);				// ������ı��ε�����
//
//		// ����
//		glNormal3f(0.0f, 1.0f, 0.0f);				// ��������
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 0.0f); 
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex3f(1.0f, 1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, -1.0f);				// ������ı��ε�����
//
//		// ����
//		glNormal3f(0.0f, -1.0f, 0.0f);				// ���߳���
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// ������ı��ε�����
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(1.0f, -1.0f, -1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(1.0f, -1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// ������ı��ε�����
//
//		// ����
//		glNormal3f(1.0f, 0.0f, 0.0f);				// ���߳���
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(1.0f, -1.0f, -1.0f);				// ������ı��ε�����
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, -1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(1.0f, 1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 0.0f); 
//		glVertex3f(1.0f, -1.0f, 1.0f);				// ������ı��ε�����
//
//		// ����
//		glNormal3f(-1.0f, 0.0f, 0.0f);				// ���߳���
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// ������ı��ε�����
//		glTexCoord2f(1.0f, 0.0f); 
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(1.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// ������ı��ε�����
//		glTexCoord2f(0.0f, 1.0f); 
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// ������ı��ε�����
//
//		glEnd();
//
//		/*// ���� 1.5 ��λ����������Ļ 6.0
//		glTranslatef(-1.5f, 0.0f, -6.0f);
//		glRotatef(rtri, 0.0f, 1.0f, 0.0f);			// ��Y����ת������
//
//		glBegin(GL_TRIANGLES);						// ����������
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// ��ɫ
//		glVertex3f(0.0f, 1.0f, 0.0f);				// �����ε��϶��� (ǰ����)
//		glColor3f(0.0f, 1.0f, 0.0f);				// ��ɫ
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// �����ε����¶��� (ǰ����)
//		glColor3f(0.0f, 0.0f, 1.0f);				// ��ɫ
//		glVertex3f(1.0f, -1.0f, 1.0f);				// �����ε����¶��� (ǰ����)
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// ��ɫ
//		glVertex3f(0.0f, 1.0f, 0.0f);				// �����ε��϶��� (�Ҳ���)
//		glColor3f(0.0f, 0.0f, 1.0f);				// ��ɫ
//		glVertex3f(1.0f, -1.0f, 1.0f);				// �����ε����¶��� (�Ҳ���)
//		glColor3f(0.0f, 1.0f, 0.0f);				// ��ɫ
//		glVertex3f(0.0f, -1.0f, -1.0f);				// �����ε����¶��� (�Ҳ���)
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// ��ɫ
//		glVertex3f(0.0f, 1.0f, 0.0f);				// �����ε��϶��� (�����)
//		glColor3f(0.0f, 1.0f, 0.0f);				// ��ɫ
//		glVertex3f(0.0f, -1.0f, -1.0f);				// �����ε����¶��� (�����)
//		glColor3f(0.0f, 0.0f, 1.0f);				// ��ɫ
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// �����ε����¶��� (�����)
//
//		glEnd();
//
//		glLoadIdentity();							// ����ģ�͹۲����
//		glTranslatef(1.5f, 0.0f, -7.0f);			// ����1.5��λ,��������Ļ7.0
//		glRotatef(rquad, 1.0f, 1.0f, 1.0f);			// ��X����ת�ı���
//
//		glBegin(GL_QUADS);							// ����������
//
//		glColor3f(0.0f, 1.0f, 0.0f);				// ��ɫ��Ϊ��ɫ
//		glVertex3f(1.0f, 1.0f, -1.0f);				// �ı��ε����϶��� (����)
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// �ı��ε����϶��� (����)
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// �ı��ε����¶��� (����)
//		glVertex3f(1.0f, 1.0f, 1.0f);				// �ı��ε����¶��� (����)
//
//		glColor3f(1.0f, 0.5f, 0.0f);				// ��ɫ�ĳɳ�ɫ
//		glVertex3f(1.0f, -1.0f, 1.0f);				// �ı��ε����϶���(����)
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// �ı��ε����϶���(����)
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)
//		glVertex3f(1.0f, -1.0f, -1.0f);				// �ı��ε����¶���(����)
//
//		glColor3f(1.0f, 0.0f, 0.0f);				// ��ɫ�ĳɺ�ɫ
//		glVertex3f(1.0f, 1.0f, 1.0f);				// �ı��ε����϶���(ǰ��)
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// �ı��ε����϶���(ǰ��)
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// �ı��ε����¶���(ǰ��)
//		glVertex3f(1.0f, -1.0f, 1.0f);				// �ı��ε����¶���(ǰ��)
//
//		glColor3f(1.0f, 1.0f, 0.0f);				// ��ɫ�ĳɻ�ɫ
//		glVertex3f(1.0f, -1.0f, -1.0f);				// �ı��ε����϶���(����)
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// �ı��ε����϶���(����)
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// �ı��ε����¶���(����)
//		glVertex3f(1.0f, 1.0f, -1.0f);				// �ı��ε����¶���(����)
//
//		glColor3f(0.0f, 0.0f, 1.0f);				// ��ɫ�ĳ���ɫ
//		glVertex3f(-1.0f, 1.0f, 1.0f);				// �ı��ε����϶���(����)
//		glVertex3f(-1.0f, 1.0f, -1.0f);				// �ı��ε����϶���(����)
//		glVertex3f(-1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)
//		glVertex3f(-1.0f, -1.0f, 1.0f);				// �ı��ε����¶���(����)
//
//		glColor3f(1.0f, 0.0f, 1.0f);				// ��ɫ�ĳ�������ɫ
//		glVertex3f(1.0f, 1.0f, -1.0f);				// �ı��ε����϶���(����)
//		glVertex3f(1.0f, 1.0f, 1.0f);				// �ı��ε����϶���(����)
//		glVertex3f(1.0f, -1.0f, 1.0f);				// �ı��ε����¶���(����)
//		glVertex3f(1.0f, -1.0f, -1.0f);				// �ı��ε����¶���(����)
//
//		glEnd();									// �����λ��ƽ���
//
//		rtri += 0.02f;								// ���������ε���ת����
//		rquad -= 0.015f;							// �����ı��ε���ת����*/
//
//
//
//		xrot += xspeed;								// xrot ���� xspeed ��λ
//		yrot += yspeed;								// yrot ���� yspeed ��λ
//		
//		/*glTranslatef(0.0f, 0.0f, -10.0f);
//		glRotatef(xrot, 1.0f, 0.0f, 0.0f);			// ��Y����ת
//		glRotatef(yrot, 0.0f, 1.0f, 0.0f);
//		glColor3f(1.0f, 0.0f, 0.0f);				// ��ɫ
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
//		// �ɹ����������Ƿ���true
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
//			MessageBox(NULL, "�ͷ�DC��RCʧ�ܡ�",
//				"�رմ���", MB_OK | MB_ICONINFORMATION);
//		}
//		if (!wglDeleteContext(hRC)) {
//			MessageBox(NULL, "�ͷ�RCʧ�ܡ�",
//				"�رմ���", MB_OK | MB_ICONINFORMATION);
//		}
//		hRC = NULL;
//	}
//
//	if (hDC && !ReleaseDC(hWnd, hDC)) {
//		MessageBox(NULL, "�ͷ�DCʧ�ܡ�",
//			"�رմ���", MB_OK | MB_ICONINFORMATION);
//		hDC = NULL;
//	}
//
//	if (hWnd && !DestroyWindow(hWnd)) {
//		MessageBox(NULL, "�ͷŴ��ھ��ʧ�ܡ�",
//			"�رմ���", MB_OK | MB_ICONINFORMATION);
//		hWnd = NULL;
//	}
//
//	if (!UnregisterClass(className, hInstance)) {
//		MessageBox(NULL, "����ע�������ࡣ",
//			"�رմ���", MB_OK | MB_ICONINFORMATION);
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
//		MessageBox(NULL, "ע�ᴰ��ʧ��", "����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;
//	}
//
//	if (fullscreen) {
//		DEVMODE dmScreenSettings; // �豸ģʽ
//		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// ȷ���ڴ����Ϊ��
//		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // Devmode �ṹ�Ĵ�С
//		dmScreenSettings.dmPelsWidth = width; // ��ѡ��Ļ���
//		dmScreenSettings.dmPelsHeight = height; // ��ѡ��Ļ�߶�
//		dmScreenSettings.dmBitsPerPel = bits; // ÿ������ѡ��ɫ�����
//		dmScreenSettings.dmFields =
//			DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
//
//		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬����
//		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)
//			!= DISP_CHANGE_SUCCESSFUL) {
//			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
//			if (MessageBox(NULL, "ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��",
//				"NeHe G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
//				fullscreen = FALSE;	// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
//			}
//			else {
//				MessageBox(NULL, "���򽫱��ر�", "����", MB_OK | MB_ICONSTOP);
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
//	if (!(hWnd = CreateWindowEx(dwExStyle,			// ��չ������
//		className,									// ������
//		title,										// ���ڱ���
//		WS_CLIPSIBLINGS |							// ����Ĵ���������
//		WS_CLIPCHILDREN |							// ����Ĵ���������
//		dwStyle,									// ѡ��Ĵ�������
//		0, 0,										// ����λ��
//		WindowRect.right - WindowRect.left,			// ��������õĴ��ڿ��
//		WindowRect.bottom - WindowRect.top,			// ��������õĴ��ڸ߶�
//		NULL,										// �޸�����
//		NULL,										// �޲˵�
//		hInstance,									// ʵ��
//		NULL))) 									// ����WM_CREATE�����κζ���
//	{
//		KillGLWindow();								// ������ʾ��
//		MessageBox(NULL, "���ܴ���һ�������豸������",
//			"����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// ���� FALSE
//	}
//	// pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
//	static	PIXELFORMATDESCRIPTOR pfd =
//	{
//		sizeof(PIXELFORMATDESCRIPTOR),				// ������ʽ�������Ĵ�С
//		1,											// �汾��
//		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
//		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
//		PFD_DOUBLEBUFFER,							// ����֧��˫����
//		PFD_TYPE_RGBA,								// ���� RGBA ��ʽ
//		bits,										// ѡ��ɫ�����
//		0, 0, 0, 0, 0, 0,							// ���Ե�ɫ��λ
//		0,											// ��Alpha����
//		0,											// ����Shift Bit
//		0,											// ���ۼӻ���
//		0, 0, 0, 0,									// ���Ծۼ�λ
//		16,											// 16λ Z-���� (��Ȼ���)
//		0,											// ���ɰ建��
//		0,											// �޸�������
//		PFD_MAIN_PLANE,								// ����ͼ��
//		0,											// Reserved
//		0, 0, 0										// ���Բ�����
//	};
//
//	// ȡ���豸��������ô?
//	if (!(hDC = GetDC(hWnd)))
//	{
//		KillGLWindow();								// ������ʾ��
//		MessageBox(NULL, "���ܴ���һ����ƥ������ظ�ʽ",
//			"����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// ���� FALSE
//	}
//
//	// Windows �ҵ���Ӧ�����ظ�ʽ����?
//	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
//	{
//		KillGLWindow();								// ������ʾ��
//		MessageBox(NULL, "�����������ظ�ʽ",
//			"����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// ���� FALSE
//	}
//
//	// �ܹ��������ظ�ʽô?
//	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
//	{
//		KillGLWindow();								// ������ʾ��
//		MessageBox(NULL, "�����������ظ�ʽ",
//			"����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// ���� FALSE
//	}
//
//	// �ܷ�ȡ����ɫ������?
//	if (!(hRC = wglCreateContext(hDC)))
//	{
//		KillGLWindow();								// ������ʾ��
//		MessageBox(NULL, "���ܴ���OpenGL��Ⱦ������",
//			"����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// ���� FALSE
//	}
//
//	// ���Լ�����ɫ������
//	if (!wglMakeCurrent(hDC, hRC))
//	{
//		KillGLWindow();								// ������ʾ��
//		MessageBox(NULL, "���ܼ��ǰ��OpenGL��Ȼ������",
//			"����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// ���� FALSE
//	}
//
//	ShowWindow(hWnd, SW_SHOW);						// ��ʾ����
//	SetForegroundWindow(hWnd);						// ����������ȼ�
//	SetFocus(hWnd);									// ���ü��̵Ľ������˴���
//	ReSizeGLScene(width, height);					// ����͸�� GL ��Ļ
//
//	// ��ʼ���½���GL����
//	if (!InitGL())
//	{
//		KillGLWindow();								// ������ʾ��
//		MessageBox(NULL, "��ʼ�����ڴ���",
//			"����", MB_OK | MB_ICONEXCLAMATION);
//		return FALSE;								// ���� FALSE
//	}
//
//	return TRUE;
//}
//
//LRESULT CALLBACK WndProc(
//	HWND	hWnd,									// ���ڵľ��
//	UINT	uMsg,									// ���ڵ���Ϣ
//	WPARAM	wParam,									// ���ӵ���Ϣ����
//	LPARAM	lParam)									// ���ӵ���Ϣ����
//{
//	switch (uMsg) {
//	case WM_ACTIVATE: // ���Ӵ��ڼ�����Ϣ
//	{
//		if (!HIWORD(wParam)) {						// �����С��״̬
//			active = TRUE;							// �����ڼ���״̬
//		}
//		else {
//			active = FALSE;							// �����ټ���
//		}
//		return 0;									// ������Ϣѭ��
//	}
//	case WM_SYSCOMMAND: // ϵͳ�ж�����
//	{
//		switch (wParam) { // ���ϵͳ����
//		case SC_SCREENSAVE: // ����Ҫ����?
//		case SC_MONITORPOWER: // ��ʾ��Ҫ����ڵ�ģʽ?
//			return 0;								// ��ֹ����
//		}
//		break;										// �˳�
//	}
//	case WM_CLOSE: // �յ�Close��Ϣ?
//	{
//		PostQuitMessage(0);							// �����˳���Ϣ
//		return 0;									// ����
//	}
//	case WM_KEYDOWN: // �м�����ô?
//	{
//		keys[wParam] = TRUE;						// ����ǣ���ΪTRUE
//		return 0;									// ����
//	}
//	case WM_KEYUP: // �м��ſ�ô?
//	{
//		keys[wParam] = FALSE;						// ����ǣ���ΪFALSE
//		return 0;									// ����
//	}
//	case WM_SIZE: // ����OpenGL���ڴ�С
//	{
//		ReSizeGLScene(LOWORD(lParam), 
//			HIWORD(lParam));						// LoWord=Width,HiWord=Height
//		return 0;									// ����
//	}
//	}
//	// ��DefWindowProc��������δ�������Ϣ��
//	return DefWindowProc(hWnd, uMsg, wParam, lParam);
//}
//
//int WINAPI WinMain(
//	HINSTANCE	hInstance,							// ��ǰ����ʵ��
//	HINSTANCE	hPrevInstance,						// ǰһ������ʵ��
//	LPSTR		lpCmdLine,							// �����в���
//	int			nCmdShow)							// ������ʾ״̬
//{
//	MSG	msg;										// Windowsx��Ϣ�ṹ
//	BOOL done = FALSE;								// �����˳�ѭ����Bool ����
//
//	// ��ʾ�û�ѡ������ģʽ
//	if (MessageBox(NULL, "������ȫ��ģʽ������ô��", 
//		"����ȫ��ģʽ", MB_YESNO | MB_ICONQUESTION) == IDNO) {
//		fullscreen = FALSE;							// FALSEΪ����ģʽ
//	}
//
//	// ����OpenGL����
//	if (!CreateGLWindow("NeHe's OpenGL������", 640, 480, 16, fullscreen))
//	{
//		return 0;									// ʧ���˳�
//	}
//
//	// ����ѭ��ֱ�� done=TRUE
//	while (!done)
//	{
//		// ����Ϣ�ڵȴ���?
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
//			// �յ��˳���Ϣ?
//			if (msg.message == WM_QUIT)	{
//				done = TRUE;						// �ǣ���done=TRUE
//			}
//			// ���ǣ���������Ϣ
//			else {
//				TranslateMessage(&msg);				// ������Ϣ
//				DispatchMessage(&msg);				// ������Ϣ
//			}
//		}
//
//		// ���û����Ϣ
//		else {
//			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
//			// ���򼤻��ô?
//			if (active) {
//				// ESC ������ô?
//				if (keys[VK_ESCAPE]) {
//					done = TRUE;					// ESC �����˳��ź�
//				}
//				// �����˳���ʱ��ˢ����Ļ
//				else {
//					DrawGLScene();					// ���Ƴ���
//					SwapBuffers(hDC);				// �������� (˫����)
//					// L���Ѱ��²����ɿ���?
//					if (keys['L'] && !lp) {
//						lp = TRUE;					// lp ��Ϊ TRUE
//						light = !light;				// �л���Դ�� TRUE/FALSE
//						// ���û�й�Դ
//						if (!light)	{
//							glDisable(GL_LIGHTING);	// ���ù�Դ
//						}
//						// ����
//						else {
//							glEnable(GL_LIGHTING);	// ���ù�Դ
//						}
//					}
//					// L���ɿ���ô?
//					if (!keys['L']) {
//						lp = FALSE;					// ���ǣ���lp��ΪFALSE
//					}
//					// F��������ô?
//					if (keys['F'] && !fp) {
//						fp = TRUE;					// fp ��Ϊ TRUE
//						filter += 1;				// filter��ֵ��һ
//						// ����2��ô?
//						if (filter>2) {
//							filter = 0;				// ��������Ϊ0
//						}
//					}
//					// F���ſ���ô?
//					if (!keys['F']) {
//						fp = FALSE;					// ����fp��ΪFALSE
//					}
//					// PageUp������?
//					if (keys[VK_PRIOR]) {
//						z -= 0.0002f;					// �����£���ľ��������Ļ�ڲ�
//					}
//					// PageDown������ô
//					if (keys[VK_NEXT]) {
//						z += 0.0002f;					// �����µĻ�����ľ������۲���
//					}
//					// Up�����������ô?
//					if (keys[VK_UP]) {
//						xspeed -= 0.0001f;			// ����,����xspeed
//					}
//					// Down�����������ô?
//					if (keys[VK_DOWN]) {
//						xspeed += 0.0001f;			// ����,����xspeed
//					}
//					// Right�����������ô?
//					if (keys[VK_RIGHT]) {
//						yspeed += 0.0001f;			// ����,����yspeed
//					}
//					// Left�����������ô?
//					if (keys[VK_LEFT]) {
//						yspeed -= 0.0001f;			// ����, ����yspeed
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
//			// F11��������ô?
//			if (keys[VK_F11]) {
//				keys[VK_F11] = FALSE;				// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
//				KillGLWindow();						// ���ٵ�ǰ�Ĵ���
//				fullscreen = !fullscreen;			// �л� ȫ�� / ���� ģʽ
//				// �ؽ� OpenGL ����
//				if (!CreateGLWindow("NeHe's ��һ������γ���",
//					640, 480, 16, fullscreen)) {
//					return 0;						// �������δ�ܴ����������˳�
//				}
//			}
//		}
//	}
//
//	// �رճ���
//	KillGLWindow();									// ���ٴ���
//	return (msg.wParam);							// �˳�����
//}

#include <time.h>
#include "GWin.h"

int WINAPI WinMain(
	HINSTANCE	hInstance,							// ��ǰ����ʵ��
	HINSTANCE	hPrevInstance,						// ǰһ������ʵ��
	LPSTR		lpCmdLine,							// �����в���
	int			nCmdShow)							// ������ʾ״̬
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

