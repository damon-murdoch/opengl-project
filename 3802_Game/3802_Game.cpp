#ifndef _GAME_CPP
#define _GAME_CPP
// 3802_Game.cpp : Defines the entry point for the console application.

#pragma comment (lib,"lib/glut32.lib")
#pragma comment (lib,"lib/glew32.lib")
#pragma comment (lib,"lib/glaux.lib")

#include <Windows.h>
#include <tchar.h>

#include "GL\glew.h"
#include "GL\glaux.h"
#include "GL\glut.h"

HDC		hDC=NULL;
HGLRC	hRC=NULL;
HWND	hWnd=NULL;
HINSTANCE hInstance;

bool keys[256];
bool active=TRUE;
bool fullscreen=TRUE;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
GLvoid GL_Resize_Scene(GLsizei width, GLsizei height){
	
	if(height==0) {
		height=1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
GLint GL_Init(GLvoid){
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	return TRUE;
}

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
GLint GL_Draw_Scene(GLvoid){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// rendering procedure code will go here

	return TRUE;
}

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
GLvoid GL_Kill_Window(GLvoid){
	if(fullscreen){
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}
	if(hRC){
		if(!wglMakeCurrent(NULL,NULL)){
			MessageBox(NULL,L"Release Of DC And RC Failed!",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		if(!wglDeleteContext(hRC)){
			MessageBox(NULL,L"Relese Rendering Context Failed!",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC))		// Are We Able To Release The DC
    {
	MessageBox(NULL,L"Release Device Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	hDC=NULL;				// Set DC To NULL
    }

    if (hWnd && !DestroyWindow(hWnd))	// Able To Destroy The Window?
    {
	MessageBox(NULL,L"Could Not Release hWnd.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	hWnd=NULL;			// Set hWnd To NULL
    }

    if (!UnregisterClass(L"OpenGL",hInstance))// Able To Unregister Class?
    {
	MessageBox(NULL,L"Could Not Unregister Class.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	hInstance=NULL;			// Set hInstance To NULL
    }
}

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
BOOL GL_Create_Window(char*title,int width,int height,int bits, bool fullscreenflag){
	
	GLuint		pixelFormat;
	WNDCLASS	windowClass;
	DWORD		exStyle;
	DWORD		style;

	RECT		windowRect;
	windowRect.left=(long)0;
	windowRect.right=(long)width;
	windowRect.top=(long)0;
	windowRect.bottom=(long)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC) WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL,IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = L"OpenGL";

	if(!RegisterClass(&windowClass)){
		MessageBox(NULL,L"Failed To Register The Window Class!",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(fullscreen){
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;	
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL){
			if (MessageBox(NULL,L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",L"OPENGL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES) {
				fullscreen=FALSE;
			}
			else {
				MessageBox(NULL,L"Program Will Now Close.",L"ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)	{
		exStyle=WS_EX_APPWINDOW;
		style=WS_POPUP;	
		ShowCursor(FALSE);	
    }

	else {
		exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		style = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect,style,FALSE,exStyle);

	if (!(hWnd=CreateWindowEx(exStyle,	
		L"OpenGL",	
		L"OpenGL Game",		
		style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0,
		0,				
		windowRect.right-windowRect.left,
		windowRect.bottom-windowRect.top,
		NULL,			
		NULL,		
		hInstance,		
		NULL)))	
    {
	GL_Kill_Window();		// Reset The Display
		MessageBox(NULL,L"Window Creation Error.",L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;			
    }

	static	PIXELFORMATDESCRIPTOR pfd={
		sizeof(PIXELFORMATDESCRIPTOR),
		1,			// Version Number
		PFD_DRAW_TO_WINDOW |	// Format Must Support Window
		PFD_SUPPORT_OPENGL |	// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,		// Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		bits,			// Select Our Color Depth
		0, 0, 0, 0, 0, 0,		// Color Bits Ignored
		0,			// No Alpha Buffer
		0,			// Shift Bit Ignored
		0,			// No Accumulation Buffer
		0, 0, 0, 0,		// Accumulation Bits Ignored
		16,			// 16Bit Z-Buffer (Depth Buffer)  
		0,			// No Stencil Buffer
		0,			// No Auxiliary Buffer
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,			// Reserved
		0, 0, 0			// Layer Masks Ignored	
	};

	// Did We Get A Device Context?
    if (!(hDC=GetDC(hWnd)))	{
	GL_Kill_Window();		// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Device Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;		// Return FALSE
    }

    // Did Windows Find A Matching Pixel Format?
    if (!(pixelFormat=ChoosePixelFormat(hDC,&pfd)))	{
		GL_Kill_Window();		// Reset The Display
		MessageBox(NULL,L"Can't Find A Suitable PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;		// Return FALSE
    }

    // Are We Able To Set The Pixel Format?
    if(!SetPixelFormat(hDC,pixelFormat,&pfd))		{
		GL_Kill_Window();		// Reset The Display
		MessageBox(NULL,L"Can't Set The PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;		// Return FALSE
    }

    // Are We Able To Get A Rendering Context?
    if (!(hRC=wglCreateContext(hDC))){
		GL_Kill_Window();		// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;		// Return FALSE
    }

    // Try To Activate The Rendering Context
    if(!wglMakeCurrent(hDC,hRC))	{
		GL_Kill_Window();		// Reset The Display
		MessageBox(NULL,L"Can't Activate The GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;		// Return FALSE
    }

    ShowWindow(hWnd,SW_SHOW);	// Show The Window
    SetForegroundWindow(hWnd);	// Slightly Higher Priority
    SetFocus(hWnd);		// Sets Focus To The Window
    GL_Resize_Scene(width,height);	// Set Up Our Perspective GL Screen

    // Initialize Our Newly Created GL Window
    if (!GL_Init()){
		GL_Kill_Window();		// Reset The Display
		MessageBox(NULL,L"Initialization Failed.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;		// Return FALSE
    }
    return TRUE;			// Success
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam){
	switch (uMsg)			// Check For Windows Messages
	{
		case WM_ACTIVATE:	// Watch For Window Activate Message
		{
			if (!HIWORD(wParam)) {
				active=TRUE; 
			}
			else {
				active=FALSE; 
			}

			return 0;	// Return To The Message Loop
		}

		case WM_SYSCOMMAND:	// Intercept System Commands
		{
			switch (wParam){
				case SC_SCREENSAVE:	
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_CLOSE:	// Did We Receive A Close Message?
		{
			PostQuitMessage(0);
			return 0;		// Jump Back
		}

		case WM_KEYDOWN:		// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;// If So, Mark It As TRUE
			return 0;		// Jump Back
		}

		case WM_KEYUP:		// Has A Key Been Released?
		{
			keys[wParam] = FALSE;// If So, Mark It As FALSE
			return 0;			// Jump Back
		}

		case WM_SIZE:		// Resize The OpenGL Window
		{
 			// LoWord=Width, HiWord=Height
			GL_Resize_Scene(LOWORD(lParam),HIWORD(lParam)); 
			return 0;			// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MSG	msg;			// Windows Message Structure
	BOOL	done=FALSE;		// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,L"Would You Like To Run In Fullscreen Mode?", L"Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO) {
		fullscreen=FALSE;	// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!GL_Create_Window("APRON TUTORIALS",640,480,16,fullscreen)){
		return 0;		// Quit If Window Was Not Created
	}

	while(!done){
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			if (msg.message==WM_QUIT){
				done=TRUE;
			}
			else{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else			// If There Are No Messages
		{
			// Draw The Scene.
			// Active?  Was There A Quit Received?
			if ((active && !GL_Draw_Scene()) || keys[VK_ESCAPE])
			{
				// ESC or DrawGLScene Signalled A Quit
				done=TRUE;
			}
			else		// Not Time To Quit, Update Screen
			{
				// Swap Buffers (Double Buffering)
				SwapBuffers(hDC);
			}

			if (keys[VK_F1])	// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;// If So Make Key FALSE
				GL_Kill_Window();	// Kill Our Current Window
				// Toggle Fullscreen / Windowed Mode
				fullscreen=!fullscreen;
				// Recreate Our OpenGL Window
				if (!GL_Create_Window("OpenGL Game",
				640,480,16,fullscreen))
				{
					// Quit If Window Was Not Created
					return 0;
				}
			}
		}
	}

	// Shutdown
	GL_Kill_Window();		// Kill The Window
	return (msg.wParam);	// Exit The Program
}

#endif