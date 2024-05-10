#include <windows.h>
#include <gl/gl.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

GLfloat angle = 0.0f;

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
        return 0;

    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          512,
                          512,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    EnableOpenGL(hwnd, &hDC, &hRC);

    while (!bQuit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glLoadIdentity();
            glTranslatef(0.0f, 0.0f, -5.0f);
            glRotatef(angle, 1.0f, 1.0f, 1.0f);

            glBegin(GL_QUADS);

            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);

            glColor3f(1.0f, 0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
            glColor3f(0.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
            glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
            glColor3f(0.0f, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

            glColor3f(1.0f, 0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
            glColor3f(0.0f, 1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
            glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
            glColor3f(0.0f, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

            glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
            glColor3f(1.0f, 0.0f, 1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
            glColor3f(1.0f, 1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

            glEnd();

            SwapBuffers(hDC);

            angle += 0.5f;
            Sleep(1);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);

    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    }
    break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    *hDC = GetDC(hwnd);

    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
