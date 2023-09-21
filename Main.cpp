#include<afxwin.h>
#include<gl/GL.h>
#pragma comment(lib, "opengl32.lib")
class App :public CWinApp
{

public:
	virtual BOOL InitInstance();
};
App app;


class Win :public CFrameWnd
{

public:
	Win();
	HGLRC glRC;
	int rx = 0;
	int ry = 0;
	~Win() { wglDeleteContext(glRC); }
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

BOOL App::InitInstance()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_pMainWnd = new Win;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return CWinApp::InitInstance();
}


void Win::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Ќе вызывать CFrameWnd::OnPaint() дл€ сообщений рисовани€
	wglMakeCurrent(dc, glRC);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(rx, 1, 0, 0);
	glRotated(ry, 0, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	

	CRect rect;
	GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
	int x0(0), y0(0);
	if (width > height)
	{
		x0 = (width - height) / 2.;
		glViewport(x0, y0, height, height);
	}
	else
	{
		y0 = (height - width) / 2.;
		glViewport(x0, y0, width, width);

	}

	


	glBegin(GL_QUADS);


	//нижн€€ ок красный
	glColor3d(1, 0, 0);
	glVertex3d(0.5, -0.5, 0.5);

	glColor3d(0, 1, 0);
	glVertex3d(-0.5, -0.5, 0.5);

	glColor3d(0, 0, 1);
	glVertex3d(-0.5, -0.5, -0.5);

	glColor3d(0, 1, 1);
	glVertex3d(0.5, -0.5, -0.5);


	//верхн€€ ок зеленый
	glColor3d(0, 1, 0);
	glVertex3d(0.5, 0.5, 0.5);

	glColor3d(1, 0, 1);
	glVertex3d(0.5, 0.5, -0.5);

	glColor3d(1, 1, 0);
	glVertex3d(-0.5, 0.5, -0.5);

	glColor3d(0.5, 1, 0);
	glVertex3d(-0.5, 0.5, 0.5);


	//права€ ок синий
	glColor3d(1, 0, 0);
	glVertex3d(0.5, -0.5, 0.5);

	glColor3d(0, 1, 1);
	glVertex3d(0.5, -0.5, -0.5);

	glColor3d(1, 0, 1);
	glVertex3d(0.5, 0.5, -0.5);

	glColor3d(1, 0.5, 0);
	glVertex3d(0.5, 0.5, 0.5);


	//лева€ ок желтый
	glColor3d(0, 1, 0);
	glVertex3d(-0.5, -0.5, 0.5);
	
	glColor3d(0.5, 1, 0);
	glVertex3d(-0.5, 0.5, 0.5);

	glColor3d(1, 1, 0);
	glVertex3d(-0.5, 0.5, -0.5);

	glColor3d(0, 0, 1);
	glVertex3d(-0.5, -0.5, -0.5);


	//передн€€ ок фиолетовый
	glColor3d(1, 0, 0);
	glVertex3d(0.5, -0.5, 0.5);

	glColor3d(1, 0.5, 0);
	glVertex3d(0.5, 0.5, 0.5);

	glColor3d(0.5, 1, 0);
	glVertex3d(-0.5, 0.5, 0.5);

	glColor3d(0, 1, 0);
	glVertex3d(-0.5, -0.5, 0.5);


	//задн€€ ок голубой
	glColor3d(0, 1, 1);
	glVertex3d(0.5, -0.5, -0.5);

	glColor3d(0, 0, 1);
	glVertex3d(-0.5, -0.5, -0.5);

	glColor3d(1, 1, 0);
	glVertex3d(-0.5, 0.5, -0.5);

	glColor3d(1, 0, 1);
	glVertex3d(0.5, 0.5, -0.5);

	glEnd();


	glFlush();
	SwapBuffers(dc);
	wglMakeCurrent(NULL, NULL);
}


Win::Win():glRC(NULL)
{
	Create(NULL, L"OpenGL");;
}

BEGIN_MESSAGE_MAP(Win, CFrameWnd)
ON_WM_SIZE()
ON_WM_PAINT()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()


void Win::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	if (glRC != NULL)wglDeleteContext(glRC);
	CDC* dc = GetDC();
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 32
	};

	pfd.cDepthBits = 24;
	int Pixelformat = ChoosePixelFormat(*dc, &pfd);
	SetPixelFormat(*dc, Pixelformat, &pfd);
	glRC = wglCreateContext(*dc);
	ReleaseDC(dc);
	Invalidate(FALSE);
	// TODO: добавьте свой код обработчика сообщений
}


void Win::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (nChar == VK_LEFT)ry--;
	if (nChar == VK_RIGHT)ry++;
	if (nChar == VK_UP)rx++;
	if (nChar == VK_DOWN)rx--;
	Invalidate(FALSE);
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
