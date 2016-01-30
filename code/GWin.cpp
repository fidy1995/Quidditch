#include "GWin.h"

bool *keys;
bool active;

GWin::GWin() {
	active = true;
	force = 0.0;
	angle = 0.0;
	gameOver = false;
	batAvail = true;
	keys = new bool[256];
	for (int i = 0; i < 256; i++) {
		keys[i] = false;
	}
	light = true;
	fps = 0;
	QueryPerformanceFrequency(&tc);
}

int GWin::run(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	MSG	msg;										// Windowsx��Ϣ�ṹ
	BOOL done = FALSE;								// �����˳�ѭ����Bool ����

	// ��ʾ�û�ѡ������ģʽ
	if (MessageBox(NULL, "������ȫ��ģʽ������ô��",
		"����ȫ��ģʽ", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		fullscreen = FALSE;							// FALSEΪ����ģʽ
	}

	// ����OpenGL����
	if (!CreateGLWindow("game", 640, 480, 16, fullscreen))
	{
		return 0;									// ʧ���˳�
	}

	// ����ѭ��ֱ�� done=TRUE
	while (!done)
	{
		// ����Ϣ�ڵȴ���?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// �յ��˳���Ϣ?
			if (msg.message == WM_QUIT)	{
				done = TRUE;						// �ǣ���done=TRUE
			}
			// ���ǣ���������Ϣ
			else {
				TranslateMessage(&msg);				// ������Ϣ
				DispatchMessage(&msg);				// ������Ϣ
			}
		}

		// ���û����Ϣ
		else {
			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			// ���򼤻��ô?
			if (active) {
				// ESC ������ô?
				if (keys[VK_ESCAPE]) {
					done = TRUE;					// ESC �����˳��ź�
				}
				// �����˳���ʱ��ˢ����Ļ
				else {
					// ��������˽�����Ϸ
					if (gameOver) {
						char c[80];
						sprintf_s(c, 80, "Your score: %d", game->getScore());
						MessageBox(NULL, c, "Game over", MB_OK | MB_ICONEXCLAMATION);
						resetGameWindow();
					}
					else {
						game->run(0.01);
						DrawGLScene();					// ���Ƴ���
						SwapBuffers(hDC);				// �������� (˫����)
						// L���Ѱ��²����ɿ���?
						if (keys['L'] && !lp) {
							lp = TRUE;					// lp ��Ϊ TRUE
							light = !light;				// �л���Դ�� TRUE/FALSE
							// ���û�й�Դ
							if (!light)	{
								glDisable(GL_LIGHT0);	// ���ù�Դ
							}
							// ����
							else {
								glEnable(GL_LIGHT0);	// ���ù�Դ
							}
						}
						// L���ɿ���ô?
						if (!keys['L']) {
							lp = FALSE;					// ���ǣ���lp��ΪFALSE
						}

						// PageUp������?
						if (keys[VK_PRIOR]) {
							z -= 0.04f;
						}
						// PageDown������ô
						if (keys[VK_NEXT]) {
							z += 0.04f;
						}
						// Up�����������ô?
						if (keys[VK_UP]) {
							if (force < 6.0f) {
								force += 0.2f;
							}
						}
						// Down�����������ô?
						if (keys[VK_DOWN]) {
							if (force > 0.0f) {
								force -= 0.2f;
							}
						}
						// Right�����������ô?
						if (keys[VK_RIGHT]) {
							angle += 0.2f;
						}
						// Left�����������ô?
						if (keys[VK_LEFT]) {
							angle -= 0.1f;
						}
						if (keys[VK_SPACE] && batAvail && force != 0) {
							if (game->getSphere(0).getVelocity().model() == 0) {
								b = new Bat(TVector(force, angle * PI / 180, 0, 0));
								batAvail = false;
							}
						}
						if (force < 0.0) {
							game->setBat(*b);
							angle = 0.0f;
							force = 0.0f;
							batAvail = true;
						}
						if (game->getBatCount() == 10 && game->stopped()) {
							gameOver = true;
						}

						// move
						if (keys['U']) {
							y -= 0.02f;
						}
						if (keys['J']) {
							y += 0.02f;
						}
						if (keys['K']) {
							x -= 0.02f;
						}
						if (keys['H']) {
							x += 0.02f;
						}

						// reset
						if (keys['R']) {
							x = 0.0f;
							y = 0.0f;
							z = -8.0f;
							xrot = 15.0f;
							yrot = 0.0f;
						}
						// freeze
						if (keys['E']) {

						}
						// rotate
						if (keys['W']) {
							if (xrot < 90.0f) {
								xrot += 0.2f;
							}
						}
						if (keys['S']) {
							if (xrot > 15.0f) {
								xrot -= 0.2f;
							}
						}
						if (keys['A']) {
							yrot += 0.2f;
						}
						if (keys['D']) {
							yrot -= 0.2f;
						}
					}
				}
			}

			// F11��������ô?
			if (keys[VK_F11]) {
				keys[VK_F11] = FALSE;				// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
				KillGLWindow();						// ���ٵ�ǰ�Ĵ���
				fullscreen = !fullscreen;			// �л� ȫ�� / ���� ģʽ
				// �ؽ� OpenGL ����
				if (!CreateGLWindow("game",
					640, 480, 16, fullscreen)) {
					return 0;						// �������δ�ܴ����������˳�
				}
			}
		}
		t1 = t2;
		QueryPerformanceCounter(&t2);
		fps = tc.QuadPart / (t2.QuadPart - t1.QuadPart);
	}

	// �رճ���
	KillGLWindow();									// ���ٴ���
}

LRESULT CALLBACK GWin::WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_ACTIVATE: // ���Ӵ��ڼ�����Ϣ
	{
		if (!HIWORD(wParam)) {						// �����С��״̬
			active = TRUE;							// �����ڼ���״̬
		}
		else {
			active = FALSE;							// �����ټ���
		}
		return 0;									// ������Ϣѭ��
	}
	case WM_SYSCOMMAND: // ϵͳ�ж�����
	{
		switch (wParam) { // ���ϵͳ����
		case SC_SCREENSAVE: // ����Ҫ����?
		case SC_MONITORPOWER: // ��ʾ��Ҫ����ڵ�ģʽ?
			return 0;								// ��ֹ����
		}
		break;										// �˳�
	}
	case WM_CLOSE: // �յ�Close��Ϣ?
	{
		PostQuitMessage(0);							// �����˳���Ϣ
		return 0;									// ����
	}
	case WM_KEYDOWN: // �м�����ô?
	{
		keys[wParam] = TRUE;						// ����ǣ���ΪTRUE
		return 0;									// ����
	}
	case WM_KEYUP: // �м��ſ�ô?
	{
		keys[wParam] = FALSE;						// ����ǣ���ΪFALSE
		return 0;									// ����
	}
	case WM_SIZE: // ����OpenGL���ڴ�С
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));						// LoWord=Width,HiWord=Height
		return 0;									// ����
	}
	}
	// ��DefWindowProc��������δ�������Ϣ��
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL GWin::CreateGLWindow(char* title, int width, int height,
	int bits, bool fullscreenflag) {
	GLuint PixelFormat;

	WNDCLASS wc;

	DWORD dwExStyle;
	DWORD dwStyle;

	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, "ע�ᴰ��ʧ��", "����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (fullscreen) {
		DEVMODE dmScreenSettings; // �豸ģʽ
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// ȷ���ڴ����Ϊ��
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // Devmode �ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth = width; // ��ѡ��Ļ���
		dmScreenSettings.dmPelsHeight = height; // ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel = bits; // ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields =
			DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬����
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)
			!= DISP_CHANGE_SUCCESSFUL) {
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
			if (MessageBox(NULL, "ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��",
				"NeHe G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
				fullscreen = FALSE;	// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
			}
			else {
				MessageBox(NULL, "���򽫱��ر�", "����", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}
	if (fullscreen) {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(dwExStyle,			// ��չ������
		className,									// ������
		title,										// ���ڱ���
		WS_CLIPSIBLINGS |							// ����Ĵ���������
		WS_CLIPCHILDREN |							// ����Ĵ���������
		dwStyle,									// ѡ��Ĵ�������
		0, 0,										// ����λ��
		WindowRect.right - WindowRect.left,			// ��������õĴ��ڿ��
		WindowRect.bottom - WindowRect.top,			// ��������õĴ��ڸ߶�
		NULL,										// �޸�����
		NULL,										// �޲˵�
		hInstance,									// ʵ��
		NULL))) 									// ����WM_CREATE�����κζ���
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL, "���ܴ���һ�������豸������",
			"����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}
	// pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// ������ʽ�������Ĵ�С
		1,											// �汾��
		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,							// ����֧��˫����
		PFD_TYPE_RGBA,								// ���� RGBA ��ʽ
		bits,										// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,							// ���Ե�ɫ��λ
		0,											// ��Alpha����
		0,											// ����Shift Bit
		0,											// ���ۼӻ���
		0, 0, 0, 0,									// ���Ծۼ�λ
		16,											// 16λ Z-���� (��Ȼ���)
		0,											// ���ɰ建��
		0,											// �޸�������
		PFD_MAIN_PLANE,								// ����ͼ��
		0,											// Reserved
		0, 0, 0										// ���Բ�����
	};

	// ȡ���豸��������ô?
	if (!(hDC = GetDC(hWnd)))
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL, "���ܴ���һ����ƥ������ظ�ʽ",
			"����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	// Windows �ҵ���Ӧ�����ظ�ʽ����?
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL, "�����������ظ�ʽ",
			"����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	// �ܹ��������ظ�ʽô?
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL, "�����������ظ�ʽ",
			"����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	// �ܷ�ȡ����ɫ������?
	if (!(hRC = wglCreateContext(hDC)))
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL, "���ܴ���OpenGL��Ⱦ������",
			"����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	// ���Լ�����ɫ������
	if (!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL, "���ܼ��ǰ��OpenGL��Ȼ������",
			"����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// ��ʾ����
	SetForegroundWindow(hWnd);						// ����������ȼ�
	SetFocus(hWnd);									// ���ü��̵Ľ������˴���
	ReSizeGLScene(width, height);					// ����͸�� GL ��Ļ

	// ��ʼ���½���GL����
	if (!InitGL())
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL, "��ʼ�����ڴ���",
			"����", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	return TRUE;
}

GLvoid GWin::KillGLWindow(GLvoid) {
	gtext->KillFont();
	if (fullscreen) {
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC) {
		if (!wglMakeCurrent(NULL, NULL)) {
			MessageBox(NULL, "�ͷ�DC��RCʧ�ܡ�",
				"�رմ���", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC)) {
			MessageBox(NULL, "�ͷ�RCʧ�ܡ�",
				"�رմ���", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC)) {
		MessageBox(NULL, "�ͷ�DCʧ�ܡ�",
			"�رմ���", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd)) {
		MessageBox(NULL, "�ͷŴ��ھ��ʧ�ܡ�",
			"�رմ���", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass(className, hInstance)) {
		MessageBox(NULL, "����ע�������ࡣ",
			"�رմ���", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

int GWin::DrawGLScene(GLvoid) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(x, y, z);
	gtext->glPrint(-4.2f, 3.0f, "FPS: %d", fps);
	gtext->glPrint(-4.2f, 2.7f, "Score: %d", game->getScore());
	gtext->glPrint(-4.2f, 2.4f, "Bats: %d", 10 - game->getBatCount());
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	gtable->GDrawTable(gtex);
	groom->GDrawRoom(gtex);
	
	for (int i = 0; i < game->getSphereNumber(); i++) {
		if (gsphere[i]) delete gsphere[i];
		gsphere[i] = new GSphere((game->getSphere(i)));
		gsphere[i]->GDrawSphere(gtex);
		if (i == 13) {
			gpart->drawParticles(gtex, game->getSphere(13).getPosition());
		}
	}
	if (game->stopped()) {
		gbat = new GBat();
		gbat->GDrawBat(game->getSphere(0), force, angle, gtex);
		if (!batAvail) {
			force -= 0.4f;
		}
	}
	gflag->GDrawFlag(gtex);

	return 1;
}

int GWin::InitGL(GLvoid) {
	game = new Game();
	perlin = new Perlin();
	gtex = new GTex();
	gflag = new GFlag(game->getFlag());
	gtable = new GTable(game->getTable(), perlin);
	groom = new GRoom(perlin);
	gpart = new GParticle();
	gtext = new GText(&hDC);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(30.0f / 256.0f, 144.0f / 256.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glight = new GLight();
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);
	return TRUE;
}

GLvoid GWin::ReSizeGLScene(GLsizei width, GLsizei height) {
	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GWin::resetGameWindow() {
	delete game;
	delete b;
	delete[] keys;
	active = true;
	force = 0.0;
	angle = 0.0;
	gameOver = false;
	batAvail = true;
	game = new Game();
	x = 0.0f;
	y = 0.0f;
	z = -8.0f;
	xrot = 15.0f;
	yrot = 0.0f;
	keys = new bool[256];
	for (int i = 0; i < 256; i++) {
		keys[i] = 0;
	}
}