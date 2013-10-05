#define SAMPLE_SURFACE_TYPE EGL_WINDOW_BIT
//#define SAMPLE_SURFACE_TYPE EGL_PIXMAP_BIT
//#define SAMPLE_SURFACE_TYPE EGL_PBUFFER_BIT

#define SAMPLE_PIXMAP_BITS 32   /* 16/32 */

#if !defined(SAMPLE_SURFACE_TYPE) || ((SAMPLE_SURFACE_TYPE != EGL_WINDOW_BIT) && (SAMPLE_SURFACE_TYPE != EGL_PIXMAP_BIT) && (SAMPLE_SURFACE_TYPE != EGL_PBUFFER_BIT))
#   error Define SAMPLE_SURFACE_TYPE properly.
#endif

#if defined (_MSC_VER)
#   pragma warning(disable : 4115) /* named type definition in parentheses */
#endif

#include <vector>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

#include "dg_game.h"
#include "dg_camera.h"

#include "dg_main_camera.h"
#include "dg_input_manager.h"
#include "dg_gui_text.h"
#include "dg_screen.h"
#include "dg_application.h"

#include "dg_horizon_grid.h"
#include "dg_light.h"
#include "dg_yramid.h"
#include "dg_star_group.h"
#include "dg_room.h"
#include "dg_model.h"
#include "dg_banner.h"
#include "dg_box_hill.h"
#include "dg_cardex.h"

#include "dg_runtime_info.h"

using std::vector;

/* EGL resources and Windows globals, defines, and prototypes */
//LONG WINAPI  MainWndProc (HWND, UINT, WPARAM, LPARAM);
//void         drawScene   (int width, int height);
//void updateState();
void perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

#define             SAMPLE_WINDOW_WIDTH     300
#define             SAMPLE_WINDOW_HEIGHT    300

static const char   g_szAppName[] = "Dragon Game";
static HWND         g_hWnd;

static EGLDisplay   g_EGLDisplay;
static EGLConfig    g_EGLConfig;
static EGLContext   g_EGLContext;
static EGLSurface   g_EGLWindowSurface;


DGInputManager* inputManager =  DGInputManager::getInstance();
DGGUIText* guiText = new DGGUIText();
DGScreen* screen = new DGScreen();
DGApplication* app = new DGApplication();

bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
time_t  lastTime;

DGGameObject* root = new DGGameObject();

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

BOOL InitGame() {
	root->addChild(new DGMainCamera());

	root->addChild(new DGHorizonGrid());
	//root->addChild(new DGLight());
	//root->addChild(new DGYramid());
	//root->addChild(new DGStarGroup());
	//root->addChild(new DGRoom());
	//root->addChild(new DGModel("Data/model/foot/Foot.obj"));

	//root->addChild(new DGBanner());
	//root->addChild(new DGBoxHill());

	root->addChild(new DGCardex());


	//root->addComponent(new DGRuntimeInfo());

	return TRUE;
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	// Set the fustrum clipping planes

	//Real w = Product(ITOR(150), FTOR(1.0/32.0));
	//Real h = Product(ITOR(150), FTOR(1.0/32.0));
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glFrustumr(-w, w, -h, h, ITOR(5), ITOR(500));
//			glViewport(0, 0, width, height);
//			float aspect = height ? (float)width/(float)height : 1.0f;
//			perspective(60.f, aspect, 10, 1000);
//			glMatrixMode(GL_MODELVIEW);	

	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	screen->resize(width, height);
}

BOOL InitGL()										// All Setup For OpenGL Goes Here
{
	/* EGL Setup */
    static const EGLint s_configAttribs[] =
    {
#if (SAMPLE_PIXMAP_BITS == 16)
        EGL_RED_SIZE,       5,
        EGL_GREEN_SIZE,     5,
        EGL_BLUE_SIZE,      5,
#elif (SAMPLE_PIXMAP_BITS == 32)
        EGL_RED_SIZE,       8,
        EGL_GREEN_SIZE,     8,
        EGL_BLUE_SIZE,      8,
#endif
        EGL_ALPHA_SIZE,     8,
        EGL_DEPTH_SIZE,     24,
        EGL_STENCIL_SIZE,   8,
        EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,//SAMPLE_SURFACE_TYPE,
        EGL_NONE
    };

    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;

    g_EGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglGetConfigs(g_EGLDisplay, NULL, 0, &numConfigs);
    eglInitialize(g_EGLDisplay, &majorVersion, &minorVersion);
    eglChooseConfig(g_EGLDisplay, s_configAttribs, &g_EGLConfig, 1, &numConfigs);
    g_EGLContext = eglCreateContext(g_EGLDisplay, g_EGLConfig, NULL, NULL);

#if (SAMPLE_SURFACE_TYPE == EGL_WINDOW_BIT)
    g_EGLWindowSurface = eglCreateWindowSurface(g_EGLDisplay, g_EGLConfig, g_hWnd, NULL);
#endif
    eglMakeCurrent(g_EGLDisplay, g_EGLWindowSurface, g_EGLWindowSurface, g_EGLContext);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading

	glClearColor(0.0f, 0.0f, 0.0f, 0.3f);				// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup

	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	guiText->init(screen);

	try {
		root->start();
	} catch(const DGException& e) {
		MessageBox(NULL, e.message, "Dragon Game Init Error!", MB_OK | MB_ICONINFORMATION);
	}

	return TRUE;										// Initialization Went OK
}

BOOL DrawGLScene()									// Here's Where We Do All The Drawing
{
	time_t currentTime = time(NULL);
	app->frameInterval = currentTime - lastTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	DGContext* ctx = new DGContext();

	ctx->setInput(inputManager);
	ctx->setGUIText(guiText);
	ctx->setScreen(screen);
	ctx->setApp(app);

	root->update(ctx);

	root->draw(ctx);

#if (SAMPLE_SURFACE_TYPE == EGL_WINDOW_BIT)
	eglSwapBuffers(g_EGLDisplay, g_EGLWindowSurface);
#endif
	InvalidateRect(g_hWnd, NULL, FALSE);

	delete ctx;

	lastTime = currentTime;

	return TRUE;										// Everything Went OK
}

GLvoid KillGLWindow()								// Properly Kill The Window
{
	if(root) {
		//root->destroy();
		delete root;
		root = NULL;
	}

	if (guiText) {
		guiText->destroy();
		guiText = NULL;
	}

	if (screen) {
		delete screen;
		screen = NULL;
	}

	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	/* Destroy all EGL resources */
    eglMakeCurrent(g_EGLDisplay, NULL, NULL, NULL);
    eglDestroyContext(g_EGLDisplay, g_EGLContext);
    eglDestroySurface(g_EGLDisplay, g_EGLWindowSurface);
    eglTerminate(g_EGLDisplay);
}

LONG WINAPI MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT     ps;
    LONG            lRet = 1;

    switch (uMsg)
    {
    case WM_CREATE:
        InitGL();
        break;
    case WM_PAINT:
        DrawGLScene();
        break;
    case WM_SIZE:
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
		break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
		KillGLWindow();
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:							// Is A Key Being Held Down?
		inputManager->handleKeyDown(wParam);		// If So, Mark It As TRUE
		break;
	case WM_KEYUP:								// Has A Key Been Released?
		inputManager->handleKeyUp(wParam);		// If So, Mark It As FALSE
		break;
    default:
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
        break;
    }

    return lRet;
}

/* OpenGL code */

/*-------------------------------------------------------------------*//*!
 * \brief   Sets the perspective matrix to OpenGL.
 * \param   fovy    Vertical field-of-view.
 * \param   aspect  Aspect ratio.
 * \param   zNear   Distance to near plane.
 * \param   zFar    Distance to far plane.
 *//*-------------------------------------------------------------------*/
/*
void perspective (
    GLfloat fovy,
    GLfloat aspect,
    GLfloat zNear,
    GLfloat zFar)
{
    GLfloat xmin, xmax, ymin, ymax;

    ymax = zNear * (GLfloat)tan(fovy * 3.1415962f / 360.0);
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustumf(xmin, xmax, ymin, ymax, zNear, zFar);
}
*/
/*-------------------------------------------------------------------*//*!
 * \internal
 * \brief   Update state.
 * \param   width   Rendering width.
 * \param   height  Rendering height.
 *//*-------------------------------------------------------------------*/
/*
void updateState()
{
    static const GLfloat light_position[]   = { -50.f, 50.f, 200.f, 0.f };
    static const GLfloat light_ambient[]    = { 0.25f, 0.25f, 0.25f, 1.f };
    static const GLfloat light_diffuse[]    = { 1.f, 1.f, 1.f, 1.f };
    static const GLfloat material_spec[]    = { 0.f, 0.f, 0.f, 0.f };

    glLightfv           (GL_LIGHT0, GL_POSITION, light_position);
    glLightfv           (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv           (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv           (GL_LIGHT0, GL_SPECULAR, light_diffuse);
    glMaterialfv        (GL_FRONT_AND_BACK, GL_SPECULAR, material_spec);

    glEnable            (GL_LIGHTING);
    glEnable            (GL_LIGHT0);
    glEnable            (GL_CULL_FACE);
//    glEnable            (GL_NORMALIZE);

    glShadeModel        (GL_SMOOTH);
    glClearColor        (0.1f, 0.2f, 0.1f, 0.f );
}
*/
/*-------------------------------------------------------------------*//*!
 * \brief   Main procedure.
 * \param   hInstance       Instance handle.
 * \param   hPrevInstance   Previous instance handle.
 * \param   lpCmdLine       Command line.
 * \param   nCmdShow        Show command.
 * \return  Returns exit status.
 *//*-------------------------------------------------------------------*/
int WINAPI WinMain (
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow)
{
    MSG             msg;
    WNDCLASS        wndclass;

    hPrevInstance;
    lpCmdLine;

    /* Register the frame class */
    wndclass.style         = 0;
    wndclass.lpfnWndProc   = (WNDPROC)MainWndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = LoadIcon (hInstance, g_szAppName);
    wndclass.hCursor       = LoadCursor (NULL,IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName  = g_szAppName;
    wndclass.lpszClassName = g_szAppName;

    if (!RegisterClass (&wndclass) )
        return FALSE;

    /* Create the frame */
    g_hWnd = CreateWindow (g_szAppName,
                          g_szAppName,
						  WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|
						  WS_MINIMIZEBOX|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          SAMPLE_WINDOW_WIDTH,
                          SAMPLE_WINDOW_HEIGHT,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    /* make sure window was created */
    if (!g_hWnd)
        return FALSE;

    /* adjust client rectangle size */
    {
        RECT    rc;
        DWORD   dwStyle;
        int     xp;
        int     yp;
        int     menuFlag;

        // change window style to popup
		// dwStyle = GetWindowStyle(hWnd);
        dwStyle = GetWindowLong(g_hWnd, GWL_STYLE);

        GetWindowRect(g_hWnd, &rc);
        xp = rc.left;   //(GetSystemMetrics(SM_CXSCREEN) - (rc.right-rc.left))/2;
        yp = rc.top;    //(GetSystemMetrics(SM_CYSCREEN) - (rc.bottom-rc.top))/2;

        menuFlag    = GetMenu(g_hWnd) != NULL;
        rc.top      = rc.left = 0;
        rc.right    = SAMPLE_WINDOW_WIDTH;
        rc.bottom   = SAMPLE_WINDOW_HEIGHT;
        AdjustWindowRect(&rc, dwStyle, menuFlag);

        SetWindowPos(g_hWnd, HWND_NOTOPMOST, xp, yp, rc.right - rc.left, rc.bottom - rc.top,
                         SWP_NOZORDER | SWP_NOACTIVATE );
    }

    /* show and update main window */
    ShowWindow (g_hWnd, nCmdShow);
    UpdateWindow (g_hWnd);

    /* Message loop */
    while(true)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
        {
			if (msg.message == WM_QUIT)
			{
				KillGLWindow();
			}
            if (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
			{				
				return 0;
			}
        }

		{   
			RECT rc;
			GetClientRect(g_hWnd, &rc);
			int width = rc.right;
			int height = rc.bottom;
			glViewport(0, 0, width, height);
		}
    }

	return 0;
}

