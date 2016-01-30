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
	MSG	msg;										// Windowsx消息结构
	BOOL done = FALSE;								// 用来退出循环的Bool 变量

	// 提示用户选择运行模式
	if (MessageBox(NULL, "你想在全屏模式下运行么？",
		"设置全屏模式", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		fullscreen = FALSE;							// FALSE为窗口模式
	}

	// 创建OpenGL窗口
	if (!CreateGLWindow("game", 640, 480, 16, fullscreen))
	{
		return 0;									// 失败退出
	}

	// 保持循环直到 done=TRUE
	while (!done)
	{
		// 有消息在等待吗?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// 收到退出消息?
			if (msg.message == WM_QUIT)	{
				done = TRUE;						// 是，则done=TRUE
			}
			// 不是，处理窗口消息
			else {
				TranslateMessage(&msg);				// 翻译消息
				DispatchMessage(&msg);				// 发送消息
			}
		}

		// 如果没有消息
		else {
			// 绘制场景。监视ESC键和来自DrawGLScene()的退出消息
			// 程序激活的么?
			if (active) {
				// ESC 按下了么?
				if (keys[VK_ESCAPE]) {
					done = TRUE;					// ESC 发出退出信号
				}
				// 不是退出的时候，刷新屏幕
				else {
					// 如果触发了结束游戏
					if (gameOver) {
						char c[80];
						sprintf_s(c, 80, "Your score: %d", game->getScore());
						MessageBox(NULL, c, "Game over", MB_OK | MB_ICONEXCLAMATION);
						resetGameWindow();
					}
					else {
						game->run(0.01);
						DrawGLScene();					// 绘制场景
						SwapBuffers(hDC);				// 交换缓存 (双缓存)
						// L键已按下并且松开了?
						if (keys['L'] && !lp) {
							lp = TRUE;					// lp 设为 TRUE
							light = !light;				// 切换光源的 TRUE/FALSE
							// 如果没有光源
							if (!light)	{
								glDisable(GL_LIGHT0);	// 禁用光源
							}
							// 否则
							else {
								glEnable(GL_LIGHT0);	// 启用光源
							}
						}
						// L键松开了么?
						if (!keys['L']) {
							lp = FALSE;					// 若是，则将lp设为FALSE
						}

						// PageUp按下了?
						if (keys[VK_PRIOR]) {
							z -= 0.04f;
						}
						// PageDown按下了么
						if (keys[VK_NEXT]) {
							z += 0.04f;
						}
						// Up方向键按下了么?
						if (keys[VK_UP]) {
							if (force < 6.0f) {
								force += 0.2f;
							}
						}
						// Down方向键按下了么?
						if (keys[VK_DOWN]) {
							if (force > 0.0f) {
								force -= 0.2f;
							}
						}
						// Right方向键按下了么?
						if (keys[VK_RIGHT]) {
							angle += 0.2f;
						}
						// Left方向键按下了么?
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

			// F11键按下了么?
			if (keys[VK_F11]) {
				keys[VK_F11] = FALSE;				// 若是，使对应的Key数组中的值为 FALSE
				KillGLWindow();						// 销毁当前的窗口
				fullscreen = !fullscreen;			// 切换 全屏 / 窗口 模式
				// 重建 OpenGL 窗口
				if (!CreateGLWindow("game",
					640, 480, 16, fullscreen)) {
					return 0;						// 如果窗口未能创建，程序退出
				}
			}
		}
		t1 = t2;
		QueryPerformanceCounter(&t2);
		fps = tc.QuadPart / (t2.QuadPart - t1.QuadPart);
	}

	// 关闭程序
	KillGLWindow();									// 销毁窗口
}

LRESULT CALLBACK GWin::WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_ACTIVATE: // 监视窗口激活消息
	{
		if (!HIWORD(wParam)) {						// 检查最小化状态
			active = TRUE;							// 程序处于激活状态
		}
		else {
			active = FALSE;							// 程序不再激活
		}
		return 0;									// 返回消息循环
	}
	case WM_SYSCOMMAND: // 系统中断命令
	{
		switch (wParam) { // 检查系统调用
		case SC_SCREENSAVE: // 屏保要运行?
		case SC_MONITORPOWER: // 显示器要进入节电模式?
			return 0;								// 阻止发生
		}
		break;										// 退出
	}
	case WM_CLOSE: // 收到Close消息?
	{
		PostQuitMessage(0);							// 发出退出消息
		return 0;									// 返回
	}
	case WM_KEYDOWN: // 有键按下么?
	{
		keys[wParam] = TRUE;						// 如果是，设为TRUE
		return 0;									// 返回
	}
	case WM_KEYUP: // 有键放开么?
	{
		keys[wParam] = FALSE;						// 如果是，设为FALSE
		return 0;									// 返回
	}
	case WM_SIZE: // 调整OpenGL窗口大小
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));						// LoWord=Width,HiWord=Height
		return 0;									// 返回
	}
	}
	// 向DefWindowProc传递所有未处理的消息。
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
		MessageBox(NULL, "注册窗口失败", "错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (fullscreen) {
		DEVMODE dmScreenSettings; // 设备模式
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// 确保内存清空为零
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // Devmode 结构的大小
		dmScreenSettings.dmPelsWidth = width; // 所选屏幕宽度
		dmScreenSettings.dmPelsHeight = height; // 所选屏幕高度
		dmScreenSettings.dmBitsPerPel = bits; // 每象素所选的色彩深度
		dmScreenSettings.dmFields =
			DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 尝试设置显示模式并返回结果。注: CDS_FULLSCREEN 移去了状态条。
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)
			!= DISP_CHANGE_SUCCESSFUL) {
			// 若模式失败，提供两个选项：退出或在窗口内运行。
			if (MessageBox(NULL, "全屏模式在当前显卡上设置失败！\n使用窗口模式？",
				"NeHe G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
				fullscreen = FALSE;	// 选择窗口模式(Fullscreen=FALSE)
			}
			else {
				MessageBox(NULL, "程序将被关闭", "错误", MB_OK | MB_ICONSTOP);
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

	if (!(hWnd = CreateWindowEx(dwExStyle,			// 扩展窗体风格
		className,									// 类名字
		title,										// 窗口标题
		WS_CLIPSIBLINGS |							// 必须的窗体风格属性
		WS_CLIPCHILDREN |							// 必须的窗体风格属性
		dwStyle,									// 选择的窗体属性
		0, 0,										// 窗口位置
		WindowRect.right - WindowRect.left,			// 计算调整好的窗口宽度
		WindowRect.bottom - WindowRect.top,			// 计算调整好的窗口高度
		NULL,										// 无父窗口
		NULL,										// 无菜单
		hInstance,									// 实例
		NULL))) 									// 不向WM_CREATE传递任何东东
	{
		KillGLWindow();								// 重置显示区
		MessageBox(NULL, "不能创建一个窗口设备描述表",
			"错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// 返回 FALSE
	}
	// pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// 上述格式描述符的大小
		1,											// 版本号
		PFD_DRAW_TO_WINDOW |						// 格式支持窗口
		PFD_SUPPORT_OPENGL |						// 格式必须支持OpenGL
		PFD_DOUBLEBUFFER,							// 必须支持双缓冲
		PFD_TYPE_RGBA,								// 申请 RGBA 格式
		bits,										// 选定色彩深度
		0, 0, 0, 0, 0, 0,							// 忽略的色彩位
		0,											// 无Alpha缓存
		0,											// 忽略Shift Bit
		0,											// 无累加缓存
		0, 0, 0, 0,									// 忽略聚集位
		16,											// 16位 Z-缓存 (深度缓存)
		0,											// 无蒙板缓存
		0,											// 无辅助缓存
		PFD_MAIN_PLANE,								// 主绘图层
		0,											// Reserved
		0, 0, 0										// 忽略层遮罩
	};

	// 取得设备描述表了么?
	if (!(hDC = GetDC(hWnd)))
	{
		KillGLWindow();								// 重置显示区
		MessageBox(NULL, "不能创建一种相匹配的像素格式",
			"错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// 返回 FALSE
	}

	// Windows 找到相应的象素格式了吗?
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		KillGLWindow();								// 重置显示区
		MessageBox(NULL, "不能设置像素格式",
			"错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// 返回 FALSE
	}

	// 能够设置象素格式么?
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		KillGLWindow();								// 重置显示区
		MessageBox(NULL, "不能设置像素格式",
			"错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// 返回 FALSE
	}

	// 能否取得着色描述表?
	if (!(hRC = wglCreateContext(hDC)))
	{
		KillGLWindow();								// 重置显示区
		MessageBox(NULL, "不能创建OpenGL渲染描述表",
			"错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// 返回 FALSE
	}

	// 尝试激活着色描述表
	if (!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();								// 重置显示区
		MessageBox(NULL, "不能激活当前的OpenGL渲然描述表",
			"错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// 返回 FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// 显示窗口
	SetForegroundWindow(hWnd);						// 略略提高优先级
	SetFocus(hWnd);									// 设置键盘的焦点至此窗口
	ReSizeGLScene(width, height);					// 设置透视 GL 屏幕

	// 初始化新建的GL窗口
	if (!InitGL())
	{
		KillGLWindow();								// 重置显示区
		MessageBox(NULL, "初始化窗口错误",
			"错误", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// 返回 FALSE
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
			MessageBox(NULL, "释放DC或RC失败。",
				"关闭错误", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC)) {
			MessageBox(NULL, "释放RC失败。",
				"关闭错误", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC)) {
		MessageBox(NULL, "释放DC失败。",
			"关闭错误", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd)) {
		MessageBox(NULL, "释放窗口句柄失败。",
			"关闭错误", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass(className, hInstance)) {
		MessageBox(NULL, "不能注销窗口类。",
			"关闭错误", MB_OK | MB_ICONINFORMATION);
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