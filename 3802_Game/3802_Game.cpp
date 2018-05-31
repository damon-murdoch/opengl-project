#ifndef _GAME_CPP
#define _GAME_CPP

// 3802_Game.cpp : Defines the entry point for the console application.

#include "common.h"
#include "robotprac.h"
#include "camera.h"
#include "models.h"
#include "lighting.h"
#include "skybox.h"
#include "shader.h"
#include "guicon.h"
#include "terrain.h"
#include "physics.h"

// Preprocessor Definitions

#define CAMERASPEED 0.01f
#define FRAMEWIDE 1248
#define FRAMEHIGH 1024
#define DRAW_DISTANCE 1500

#ifndef MAX_OBJECTS
	#define MAX_OBJECTS 512
	#ifdef MAX_BOUNDING_BOXES
		#undef MAX_BOUNDING_BOXES
		#define MAX_BOUNDING_BOXES MAX_OBJECTS
	#endif // MAX_BOUNDING_BOXES
#endif // MAX_OBJECTS

// Function Declarations
void Initialise_Shading();
void Draw_Bounding_Box(tBoundingBox box);
void Keyboard_Input();
void Draw_Grid();
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
GLvoid GL_Resize_Scene(GLsizei width, GLsizei height);
GLint GL_Init(GLvoid);
GLvoid GL_Kill_Window(GLvoid);
BOOL GL_Create_Window(char*title,int width,int height,int bits, bool fullscreenflag);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam);
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void Update_Projection(GLboolean toggle = GL_FALSE);

// Global Variables

HDC		hDC=NULL;
HGLRC	hRC=NULL;
HWND	hWnd=NULL;
HINSTANCE hInstance;

Camera camera;

bool keys[256];
bool active=TRUE;
bool fullscreen=TRUE;

bool stereo;
int eyes;

Shader phong;

Terrain terrain;

Light pointlight;

Model honk;

Skybox skybox(0,0,0,1000,1000,1000);

Image skb_f,skb_b,skb_l,skb_r,skb_u,skb_d;

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
GLint GL_Init(GLvoid){

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);

	

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

	skb_f.load_image("img/sor_lake1/lake1_ft.JPG");
	skb_b.load_image("img/sor_lake1/lake1_bk.JPG");
	skb_l.load_image("img/sor_lake1/lake1_lf.JPG");
	skb_r.load_image("img/sor_lake1/lake1_rt.JPG");
	skb_u.load_image("img/sor_lake1/lake1_up.JPG");
	skb_d.load_image("img/sor_lake1/lake1_dn.JPG");

	skybox.Assign_Front(skb_f);
	skybox.Assign_Back(skb_b);
	skybox.Assign_Left(skb_l);
	skybox.Assign_Right(skb_r);
	skybox.Assign_Up(skb_u);
	skybox.Assign_Down(skb_d);

	Initialise_Shading();

	honk.Load("obj/honk/honk.obj");

	phong.load("phong.vertex","phong.fragment");

	terrain.Initialise_Terrain(2,"img/heightmap/heightmap.png");

	return TRUE;
}

// Function Implementations

void Initialise_Shading(){
	
	glEnable(GL_LIGHTING);

	GLfloat ambient_light[] = {5.0f,5.0f,5.0f,5.0f};
	GLfloat diffuse_light[] = {0.8f,0.8f,0.8f,1.0f};
	GLfloat specular_light[] = {0.5f,0.5f,0.5f,1.0f};
	GLfloat position[] = {0.0f,0.0f,0.0f,0.0f};

	pointlight.Initialise(ambient_light,diffuse_light,specular_light,position);
	pointlight.Bind(GL_LIGHT0);
}

void Draw_Bounding_Box(tBoundingBox box){
	
	glColor3f(0,0,1.0f);

	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(box.min.x,box.min.y,box.min.z);
		glVertex3f(box.max.x,box.min.y,box.min.z);
		glVertex3f(box.max.x,box.min.y,box.max.z);
		glVertex3f(box.min.x,box.min.y,box.max.z);
	}
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	{
		glVertex3f(box.min.x,box.max.y,box.min.z);
		glVertex3f(box.max.x,box.max.y,box.min.z);
		glVertex3f(box.max.x,box.max.y,box.max.z);
		glVertex3f(box.min.x,box.max.y,box.max.z);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glVertex3f(box.min.x,box.min.y,box.min.z);
		glVertex3f(box.min.x,box.max.y,box.min.z);
		
		glVertex3f(box.max.x,box.min.y,box.min.z);
		glVertex3f(box.max.x,box.max.y,box.min.z);
		
		glVertex3f(box.max.x,box.min.y,box.max.z);
		glVertex3f(box.max.x,box.max.y,box.max.z);
		
		glVertex3f(box.min.x,box.min.y,box.max.z);
		glVertex3f(box.min.x,box.max.y,box.max.z);
	}
	glEnd();
}

void Keyboard_Input(){
	if((GetKeyState(VK_UP) & 0x80) || (GetKeyState('W') & 0x80)){
		camera.Move_Camera(CAMERASPEED);
	}
	if((GetKeyState(VK_DOWN) & 0x80) || (GetKeyState('S') & 0x80)){
		camera.Move_Camera(-CAMERASPEED);
	}
	if((GetKeyState(VK_LEFT) & 0x80) || (GetKeyState('A') & 0x80)){
		camera.Strafe_Camera(-CAMERASPEED);
	}
	if((GetKeyState(VK_RIGHT) & 0x80) || (GetKeyState('D') & 0x80)){
		camera.Strafe_Camera(CAMERASPEED);
	}
}

void Draw_Grid(){
	for (int i = -500; i<500; i+=5){
		glBegin(GL_LINES);
		{
			glColor3ub(150,190,150);
			glVertex3f(-500,0,(float)i);
			glVertex3f(500,0,(float)i);
			glVertex3f((float)i,0,-500);
			glVertex3f((float)i,0,500);
		}
		glEnd();
	}
}

void Update_Projection(GLboolean toggle){
	static GLboolean s_use_perspective = GL_TRUE;
	if(toggle)
		s_use_perspective = !s_use_perspective;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if(s_use_perspective)	glFrustum(-1.0,1.0,-1.0,1.0,5,DRAW_DISTANCE);
	else					glOrtho(-1.0,1.0,-1.0,1.0,5,DRAW_DISTANCE);

	glMatrixMode(GL_MODELVIEW);

}

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
GLvoid GL_Resize_Scene(GLsizei width, GLsizei height){
	
	if(height==0) {
		height=1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,DRAW_DISTANCE);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// from http://www.morrowland.com/apron/tutorials/gl/gl_window.php
GLint GL_Draw_Scene(GLvoid){
	
	phong.use();

	assert(glGetError()==GL_NO_ERROR);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(camera.m_pos.x,camera.m_pos.y,camera.m_pos.z,
			  camera.m_view.x,camera.m_view.y,camera.m_view.z,
			  camera.m_up.x,camera.m_up.y,camera.m_up.z);

	skybox.Render();

	terrain.Render();

	Draw_Grid();

	honk.Render();

	glColor3f(255,0,0);

	glFlush();
	SwapBuffers(hDC);

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

	if (hDC && !ReleaseDC(hWnd,hDC))
    {
	MessageBox(NULL,L"Release Device Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	hDC=NULL;
    }

    if (hWnd && !DestroyWindow(hWnd))
    {
	MessageBox(NULL,L"Could Not Release hWnd.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	hWnd=NULL;
    }

    if (!UnregisterClass(L"OpenGL",hInstance))
    {
	MessageBox(NULL,L"Could Not Unregister Class.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
	hInstance=NULL;
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
	GL_Kill_Window();
		MessageBox(NULL,L"Window Creation Error.",L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;			
    }

	static	PIXELFORMATDESCRIPTOR pfd={
		sizeof(PIXELFORMATDESCRIPTOR),
		1,	
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |	
		PFD_DOUBLEBUFFER,		
		PFD_TYPE_RGBA,	
		bits,			
		0, 0, 0, 0, 0, 0,		
		0,		
		0,			
		0,			
		0, 0, 0, 0,		
		16,		
		0,		
		0,		
		PFD_MAIN_PLANE,	
		0,			
		0, 0, 0		
	};

    if (!(hDC=GetDC(hWnd)))	{
	GL_Kill_Window();
		MessageBox(NULL,L"Can't Create A GL Device Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
    }

    if (!(pixelFormat=ChoosePixelFormat(hDC,&pfd)))	{
		GL_Kill_Window();
		MessageBox(NULL,L"Can't Find A Suitable PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
    }

    if(!SetPixelFormat(hDC,pixelFormat,&pfd))	{
		GL_Kill_Window();
		MessageBox(NULL,L"Can't Set The PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
    }

    if (!(hRC=wglCreateContext(hDC))){
		GL_Kill_Window();
		MessageBox(NULL,L"Can't Create A GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
    }

    if(!wglMakeCurrent(hDC,hRC))	{
		GL_Kill_Window();
		MessageBox(NULL,L"Can't Activate The GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
    }

    ShowWindow(hWnd,SW_SHOW);
    SetForegroundWindow(hWnd);
    SetFocus(hWnd);	
    GL_Resize_Scene(width,height);	

	if(glewInit() != GLEW_OK){
		GL_Kill_Window();
		MessageBox(NULL,L"Glew Initialization Failed.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

    if (!GL_Init()){
		GL_Kill_Window();
		MessageBox(NULL,L"Initialization Failed.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
    }

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam){
	switch (uMsg)
	{
		case WM_ACTIVATE:
		{
			if (!HIWORD(wParam)) {
				active=TRUE; 
			}
			else {
				active=FALSE; 
			}

			return 0;
		}

		case WM_SYSCOMMAND:	
		{
			switch (wParam){
				case SC_SCREENSAVE:	
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			return 0;
		}

		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			return 0;
		}

		case WM_SIZE:
		{
			GL_Resize_Scene(LOWORD(lParam),HIWORD(lParam)); 
			return 0;
		}
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	
	#ifdef _DEBUG
		RedirectIOToConsole();
	#endif
	
	MSG	msg;
	BOOL	done=FALSE;

	if (MessageBox(NULL,L"Would You Like To Run In Fullscreen Mode?", L"Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO) {
		fullscreen=FALSE;
	}

	if (!GL_Create_Window("APRON TUTORIALS",FRAMEWIDE,FRAMEHIGH,16,fullscreen)){
		return 0;
	}

	camera.Position_Camera(0,2.5f,5,0,2.5f,0,0,1,0);

	while(!done){
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			if (msg.message==WM_QUIT){
				done=TRUE;
			}
			else{
				GL_Draw_Scene();
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{

			Keyboard_Input();
			camera.Mouse_Move(FRAMEWIDE,FRAMEHIGH);

			if ((active && !GL_Draw_Scene()) || keys[VK_ESCAPE])
			{
				done=TRUE;
			}
			else
			{
				SwapBuffers(hDC);
			}

			if (keys[VK_F1])
			{
				keys[VK_F1]=FALSE;
				GL_Kill_Window();
				fullscreen=!fullscreen;
				if (!GL_Create_Window("OpenGL Game",
				FRAMEWIDE,FRAMEHIGH,16,fullscreen))
				{
					return 0;
				}
			}
		}
	}
	GL_Kill_Window();
	return (msg.wParam);
}

#endif