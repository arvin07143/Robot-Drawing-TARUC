#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <vector>
#include <string>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

double fingerAngle = 0;
double widenFing = 0;
double elbowAngle = 0;

double kneeAngle = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;
using namespace std;

BITMAP BMP;
HBITMAP hBMP = NULL;


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_UP:
				fingerAngle -= 3;
			break;
		case VK_LEFT:
			fingerAngle += 3;
			break;
		case VK_RIGHT:
			if (kneeAngle > -10)kneeAngle -= 5;
			break;
		}

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------



bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

<<<<<<< HEAD
GLuint loadTexture(LPCSTR filename) {
	GLuint texture = 0;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
=======
GLuint loadTexture(LPCSTR fileName) {
	GLuint texture = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
>>>>>>> parent of e7121b9... Revert "update"

	DeleteObject(hBMP);

	return texture;
}

void drawSphere(float radius, float r, float g, float b, int type) {

	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, type);
	glColor3f(r, g, b);
	gluSphere(sphere, radius, 40, 40);
	gluDeleteQuadric(sphere);
}

<<<<<<< HEAD
void drawCylinder(float btm, float top, float height, int type, GLuint text) {

	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, type);
	glBindTexture(GL_TEXTURE, text);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluCylinder(cylinder, btm, top, height, 30, 30);
	gluDeleteQuadric(cylinder);
}


void drawHelmet() {
	GLuint texture2;
	texture2 = loadTexture("iron1.bmp");
	glBegin(GL_POLYGON);// top front right(front)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.28, 0.1);
=======
void drawSphere(float radius, float r, float g, float b, int type , GLuint text) {
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, type);
	glBindTexture(GL_TEXTURE_2D, text);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glColor3f(r, g, b);
	gluSphere(sphere, radius, 30, 30);

	gluDeleteQuadric(sphere);
}

void drawCylinder(float btm, float top, float height, float r, float g, float b, int type) {

	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, type);
	glColor3f(r, g, b);
	gluCylinder(cylinder, btm, top, height, 30, 30);

	gluDeleteQuadric(cylinder);
}


void drawCylinder(float btm, float top, float height, float r, float g, float b, int type, GLuint text) {

	GLUquadricObj* cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, type);
	glBindTexture(GL_TEXTURE_2D, text);
	gluQuadricTexture(cylinder, GL_TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	glColor3f(r, g, b);
	gluCylinder(cylinder, btm, top, height, 30, 30);
>>>>>>> parent of e7121b9... Revert "update"

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0.4, 0.1);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0.4, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, 0.3, 0.2);
	glEnd();

	glBegin(GL_POLYGON);//top front right(back)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, 0.3, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, 0.4, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0.4, 0.13);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.28, 0.13);
	glEnd();

	glBegin(GL_POLYGON);//top front right (right)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0.4, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, 0.3, 0.2);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, 0.3, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, 0.4, 0.23);
	glEnd();

	glBegin(GL_POLYGON);//top front right (bottom)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.28, 0.1);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, 0.3, 0.2);


	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0.3, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0.28, 0.13);
	glEnd();

	glBegin(GL_POLYGON);//top front right(top)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.4, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.4, 0.13);
	glEnd();


	glBegin(GL_POLYGON);//top front left (right)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, 0.3, 0.2);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, 0.3, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.23);
	glEnd();

	glBegin(GL_POLYGON);//top front left (bottom)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.28, 0.1);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, 0.3, 0.2);


	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, 0.3, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0.28, 0.13);
	glEnd();

	glBegin(GL_POLYGON);// bottom front right(front)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.08, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.2, 0.1);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, -0.2, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, -0.08, 0.2);
	glEnd();


	glBegin(GL_POLYGON);//bottom front right (back)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, -0.08, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, -0.2, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -0.2, 0.13);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.08, 0.13);
	glEnd();

	glBegin(GL_POLYGON);//bottom front right(bottom)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.2, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, -0.2, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, -0.2, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.2, 0.13);
	glEnd();

	glBegin(GL_POLYGON);//bottom front right(right)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, -0.2, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, -0.08, 0.2);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, -0.08, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, -0.2, 0.23);
	glEnd();

	glBegin(GL_POLYGON);//bottom front right(top)

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.08, 0.1);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, -0.08, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, -0.08, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.08, 0.13);
	glEnd();


	glBegin(GL_POLYGON);// bottom front left(front)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.08, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.2, 0.1);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, -0.2, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, -0.08, 0.2);
	glEnd();


	glBegin(GL_POLYGON);//bottom front left (back)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, -0.08, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, -0.2, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -0.2, 0.13);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.08, 0.13);
	glEnd();

	glBegin(GL_POLYGON);//bottom front left(bottom)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.2, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, -0.2, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, -0.2, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.2, 0.13);
	glEnd();

	glBegin(GL_POLYGON);// bottom front left(left)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, -0.2, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, -0.08, 0.2);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, -0.08, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, -0.2, 0.23);
	glEnd();

	glBegin(GL_POLYGON);// bottom front left(top)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.08, 0.1);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, -0.08, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, -0.08, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.08, 0.13);
	glEnd();

	glBegin(GL_POLYGON);//front left(front)
	glTexCoord2f(0.0f, 0.0f);;
	glVertex3f(0, 0.28, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0.4, 0.1);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, 0.3, 0.2);
	glEnd();


	glBegin(GL_POLYGON);//front left(back)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, 0.3, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0.4, 0.13);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.28, 0.13);
	glEnd();

	glBegin(GL_POLYGON);//front left(top)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.4, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, 0.4, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.4, 0.13);
	glEnd();

	glBegin(GL_POLYGON);// top left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.401, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.401, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, 0.401, 0.55);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.401, 0.55);
	glEnd();

	glBegin(GL_POLYGON);//Top Right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.401, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, 0.401, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0.401, 0.55);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.401, 0.55);
	glEnd();


	glBegin(GL_POLYGON);// bottom left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.201, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, -0.201, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, -0.201, 0.55);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.201, 0.55);
	glEnd();

	glBegin(GL_POLYGON);//bottom Right
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.201, 0.1);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, -0.201, 0.2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, -0.201, 0.55);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.201, 0.55);
	glEnd();

	glBegin(GL_POLYGON);//Back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, 0.35, 0.60);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, 0.35, 0.60);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, -0.15, 0.60);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, -0.15, 0.60);
	glEnd();

	glBegin(GL_POLYGON);//Top back connector

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.401, 0.55);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.2, 0.35, 0.60);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, 0.35, 0.60);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, 0.401, 0.55);
	glEnd();

	glBegin(GL_POLYGON);//bottom back connector
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, -0.15, 0.60);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, -0.201, 0.55);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, -0.201, 0.55);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, -0.15, 0.60);
	glEnd();

	glBegin(GL_POLYGON);// left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.20, 0.401, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.20, -0.201, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.20, -0.201, 0.55);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.20, 0.401, 0.55);
	glEnd();

	glBegin(GL_POLYGON);// right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.20, 0.401, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.20, -0.201, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.20, -0.201, 0.55);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.20, 0.401, 0.55);
	glEnd();

	glBegin(GL_POLYGON);//left back connector
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.20, -0.201, 0.55);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.20, 0.401, 0.55);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, 0.35, 0.60);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.2, -0.15, 0.60);
	glEnd();

	glBegin(GL_POLYGON);//right back connector
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.20, -0.201, 0.55);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.20, 0.401, 0.55);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, 0.35, 0.60);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, -0.15, 0.60);
	glEnd();

	glDeleteTextures(1, &texture2);

	glColor3f(1, 1, 1);
	GLuint texture15 = loadTexture("right_mouth.bmp");
	glBegin(GL_POLYGON);//right bottom face
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0.1, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, -0.2, 0.23);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -0.2, 0.12);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0.1, 0.12);
	glEnd();

	glDeleteTextures(1, &texture15);

	glColor3f(1, 1, 1);
	GLuint texture14 = loadTexture("left_mouth.bmp");
	glBegin(GL_POLYGON);//left bottom face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.1, 0.23);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, -0.2, 0.23);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -0.2, 0.12);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0.1, 0.12);
	glEnd();

	glDeleteTextures(1, &texture14);

	glColor3f(1, 1, 1);
	GLuint texture12 = loadTexture("robot_right_eye.bmp");
	glBegin(GL_POLYGON);//right top face
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.2, 0.1, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.2, 0.3, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0.3, 0.12);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0.1, 0.12);
	glEnd();
	glDeleteTextures(1, &texture12);

	glColor3f(1, 1, 1);

	GLuint texture13 = loadTexture("robot_left_eye.bmp");
	glBegin(GL_POLYGON);//left top face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.2, 0.1, 0.23);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.2, 0.3, 0.23);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0.3, 0.12);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0.1, 0.12);
	glEnd();
	glDeleteTextures(1, &texture13);
}

<<<<<<< HEAD
void drawHilt() {

	GLuint texture5 = loadTexture("black.bmp");
	glPushMatrix();
	glTranslatef(0.0, 0.38, 0);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.015, 0.02, 0.02, GLU_FILL, texture5);//hilt
	glPopMatrix();
	glDeleteTextures(1, &texture5);


	glPushMatrix();
	glTranslatef(0.0, 0.73, 0);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.02, 0.02, 0.04, GLU_FILL, texture5);//hilt
	glPopMatrix();
	glDeleteTextures(1, &texture5);

	glPushMatrix();
	glTranslatef(0.0, 0.35, 0.0);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.015, 0.015, 0.06, GLU_FILL, texture5);
	glPopMatrix();
	glDeleteTextures(1, &texture5);

	GLuint texture4 = loadTexture("ice.bmp");
	glPushMatrix();
	glTranslatef(0.0, 0.4, 0);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.02, 0.02, 0.33, GLU_FILL, texture4);//hilt
	glPopMatrix();

	glDeleteTextures(1, &texture4);

	GLuint texture9 = loadTexture("snow_white.bmp");
	glPushMatrix();
	glTranslatef(0, 0.33, -0.014);
	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);
	//Face 1 : Behind
	glVertex3f(-0.05, -0.05, 0.02);
	glVertex3f(-0.05, 0.05, 0.02);
	glVertex3f(0.05, 0.05, 0.02);
	glVertex3f(0.05, -0.05, 0.02);
	glEnd();

	//Face 2 : right
	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.05, -0.05, 0.02);
	glVertex3f(0.05, -0.05, 0.01);
	glVertex3f(0.05, 0.05, 0.01);
	glVertex3f(0.05, 0.05, 0.02);
	glEnd();

	//Face 3 : Top
	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.05, 0.05, 0.02);
	glVertex3f(0.05, 0.05, 0.01);
	glVertex3f(-0.05, 0.05, 0.01);
	glVertex3f(-0.05, 0.05, 0.02);
	glEnd();

	//Face 4 : Left
	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0.05, 0.02);
	glVertex3f(-0.05, -0.05, 0.02);
	glVertex3f(-0.05, -0.05, 0.01);
	glVertex3f(-0.05, 0.05, 0.01);
	glEnd();

	//Face 5 : Front
	glTexCoord2f(0.5f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 0.05, 0.01);
	glVertex3f(-0.05, -0.05, 0.01);
	glVertex3f(0.05, -0.05, 0.01);
	glVertex3f(0.05, 0.05, 0.01);
	glEnd();

	//Face 6 : Bottom
	glTexCoord2f(1.0f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex3f(0.05, -0.05, 0.01);
	glVertex3f(0.05, -0.05, 0.02);
	glVertex3f(-0.05, -0.05, 0.02);
	glVertex3f(-0.05, -0.05, 0.01);
	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &texture9);
}

void drawSword() {
	GLuint texture10 = loadTexture("dark_grey.bmp");
	glPushMatrix();
	glTranslatef(0, 0.3, 0.001);
	glRotatef(90, 1, 0, 0);
	drawCylinder(0.005, 0.005, 0.5, GL_FILL, NULL);
	glPopMatrix();
	glDeleteTextures(1, &texture10);

	glColor3f(1, 1, 1);
	GLuint texture6 = loadTexture("light_red.bmp");
	glPushMatrix();
	glTranslatef(0, 0, 0.053);
	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.03, -0.2, -0.05);
	glVertex3f(-0.03, -0.8, -0.05);
	glVertex3f(0, -0.85, -0.05);
	glVertex3f(0.03, -0.8, -0.05);
	glVertex3f(0.03, -0.2, -0.05);
	glVertex3f(-0.03, -0.2, -0.05);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, 0.048);
	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.03, -0.2, -0.05);
	glVertex3f(-0.03, -0.8, -0.05);
	glVertex3f(0, -0.85, -0.05);
	glVertex3f(0.03, -0.8, -0.05);
	glVertex3f(0.03, -0.2, -0.05);
	glVertex3f(-0.03, -0.2, -0.05);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.055);
	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);//side
	glVertex3f(-0.03, -0.2, -0.05);
	glVertex3f(-0.03, -0.8, -0.05);
	glVertex3f(-0.03, -0.8, -0.055);
	glVertex3f(-0.03, -0.2, -0.055);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.055);
	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//tip side
	glVertex3f(-0.03, -0.8, -0.05);
	glVertex3f(0, -0.85, -0.05);
	glVertex3f(0, -0.85, -0.055);
	glVertex3f(-0.03, -0.8, -0.055);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, 0.055);
	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//tip side
	glVertex3f(0.03, -0.8, -0.05);
	glVertex3f(0, -0.85, -0.05);
	glVertex3f(0, -0.85, -0.055);
	glVertex3f(0.03, -0.8, -0.055);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.055);
	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);//side
	glVertex3f(0.03, -0.2, -0.05);
	glVertex3f(0.03, -0.8, -0.05);
	glVertex3f(0.03, -0.8, -0.055);
	glVertex3f(0.03, -0.2, -0.055);
	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &texture6);

	glPushMatrix();
	glTranslatef(0, 0, 0.046);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(-0.015, -0.2, -0.05);
	glVertex3f(-0.015, -0.8, -0.05);
	glVertex3f(0, -0.85, -0.05);
	glVertex3f(0.015, -0.8, -0.05);
	glVertex3f(0.015, -0.2, -0.05);
	glVertex3f(-0.015, -0.2, -0.05);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.056);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(-0.015, -0.2, -0.05);
	glVertex3f(-0.015, -0.8, -0.05);
	glVertex3f(0, -0.85, -0.05);
	glVertex3f(0.015, -0.8, -0.05);
	glVertex3f(0.015, -0.2, -0.05);
	glVertex3f(-0.015, -0.2, -0.05);
	glEnd();
	glPopMatrix();

	glColor3f(1, 1, 1);
	GLuint texture11 = loadTexture("light_red.bmp");
	glBegin(GL_POLYGON);//left deco front

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.04, -0.15, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.01, -0.2, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.01, -0.05, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.025, -0.05, 0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.025, 0.3, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.04, 0.3, 0);
	glEnd();


	glBegin(GL_POLYGON);//left deco back

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.04, 0.3, 0.005);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.04, -0.15, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.01, -0.2, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.01, -0.05, 0.005);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.025, -0.05, 0.005);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.025, 0.3, 0.005);

	glEnd();


	glBegin(GL_POLYGON);//left deco left

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.04, 0.3, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.04, 0.3, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.04, -0.15, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.04, -0.15, 0);
	glEnd();


	glBegin(GL_POLYGON);//left deco bottom

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.04, -0.15, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.04, -0.15, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.01, -0.2, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.01, -0.2, 0);
	glEnd();


	glBegin(GL_POLYGON);//left deco right bottom

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.01, -0.2, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.01, -0.2, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.01, -0.05, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.01, -0.05, 0);
	glEnd();


	glBegin(GL_POLYGON);//left deco right connector

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.025, -0.05, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.025, -0.05, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.025, 0.3, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.025, 0.3, 0);
	glEnd();


	glBegin(GL_POLYGON);//left deco right top

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.025, 0.3, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, 0.3, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.025, 0.3, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.04, 0.3, 0.005);
	glEnd();


	glBegin(GL_POLYGON);//right deco front

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.04, 0.3, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, -0.15, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.01, -0.2, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.01, -0.05, 0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.025, -0.05, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.025, 0.3, 0);

	glEnd();

	glBegin(GL_POLYGON);//right deco back

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.04, 0.3, 0.005);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, -0.15, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.01, -0.2, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.01, -0.05, 0.005);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.025, -0.05, 0.005);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.025, 0.3, 0.005);
	glEnd();

	glBegin(GL_POLYGON);//right deco left

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.04, 0.3, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, 0.3, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.04, -0.15, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.04, -0.15, 0);
	glEnd();

	glBegin(GL_POLYGON);//right deco bottom

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.04, -0.15, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, -0.15, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.01, -0.2, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.01, -0.2, 0);
	glEnd();

	glBegin(GL_POLYGON);//right deco left bottom

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.01, -0.2, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.01, -0.2, 0.005);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.01, -0.05, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.01, -0.05, 0);
	glEnd();


	glBegin(GL_POLYGON);//right deco left top

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.025, 0.3, 0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, 0.3, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.025, 0.3, 0.005);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.04, 0.3, 0.005);
	glEnd();


	glDeleteTextures(1, &texture11);
}

void drawHammer() {
	GLuint texture7 = loadTexture("silver_metallic.bmp");
	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//front
	glVertex3f(-0.25, 0.8, 0);
	glVertex3f(0.25, 0.8, 0);
	glVertex3f(0.25, 0.4, 0);
	glVertex3f(-0.25, 0.4, 0);
	glEnd();

	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);//back
	glVertex3f(-0.25, 0.8, 0.2);
	glVertex3f(0.25, 0.8, 0.2);
	glVertex3f(0.25, 0.4, 0.2);
	glVertex3f(-0.25, 0.4, 0.2);
	glEnd();

	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);//left
	glVertex3f(-0.3, 0.78, 0.03);
	glVertex3f(-0.3, 0.78, 0.17);
	glVertex3f(-0.3, 0.42, 0.17);
	glVertex3f(-0.3, 0.42, 0.03);
	glEnd();

	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);//right
	glVertex3f(0.3, 0.78, 0.03);
	glVertex3f(0.3, 0.78, 0.17);
	glVertex3f(0.3, 0.42, 0.17);
	glVertex3f(0.3, 0.42, 0.03);
	glEnd();

	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//top
	glVertex3f(-0.25, 0.85, 0.05);
	glVertex3f(-0.25, 0.85, 0.15);
	glVertex3f(0.25, 0.85, 0.15);
	glVertex3f(0.25, 0.85, 0.05);
	glEnd();

	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);//bottom
	glVertex3f(-0.25, 0.35, 0.05);
	glVertex3f(-0.25, 0.35, 0.15);
	glVertex3f(0.25, 0.35, 0.15);
	glVertex3f(0.25, 0.35, 0.05);
	glEnd();

	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);//top front side
	glVertex3f(-0.25, 0.8, 0);
	glVertex3f(-0.25, 0.85, 0.05);
	glVertex3f(0.25, 0.85, 0.05);
	glVertex3f(0.25, 0.8, 0);
	glEnd();

	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);//top back side
	glVertex3f(-0.25, 0.8, 0.2);
	glVertex3f(-0.25, 0.85, 0.15);
	glVertex3f(0.25, 0.85, 0.15);
	glVertex3f(0.25, 0.8, 0.2);
	glEnd();

	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//bottom front side
	glVertex3f(-0.25, 0.4, 0);
	glVertex3f(-0.25, 0.35, 0.05);
	glVertex3f(0.25, 0.35, 0.05);
	glVertex3f(0.25, 0.4, 0);
	glEnd();

	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);//bottom back side
	glVertex3f(-0.25, 0.4, 0.2);
	glVertex3f(-0.25, 0.35, 0.15);
	glVertex3f(0.25, 0.35, 0.15);
	glVertex3f(0.25, 0.4, 0.2);
	glEnd();

	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);//right top side
	glVertex3f(0.25, 0.85, 0.15);
	glVertex3f(0.3, 0.78, 0.17);
	glVertex3f(0.3, 0.78, 0.03);
	glVertex3f(0.25, 0.85, 0.05);
	glEnd();

	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);//right bottom side
	glVertex3f(0.25, 0.35, 0.15);
	glVertex3f(0.3, 0.42, 0.17);
	glVertex3f(0.3, 0.42, 0.03);
	glVertex3f(0.25, 0.35, 0.05);
	glEnd();

	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//left bottom side
	glVertex3f(-0.25, 0.35, 0.15);
	glVertex3f(-0.3, 0.42, 0.17);
	glVertex3f(-0.3, 0.42, 0.03);
	glVertex3f(-0.25, 0.35, 0.05);
	glEnd();

	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);//left top side
	glVertex3f(-0.25, 0.85, 0.15);
	glVertex3f(-0.3, 0.78, 0.17);
	glVertex3f(-0.3, 0.78, 0.03);
	glVertex3f(-0.25, 0.85, 0.05);
	glEnd();

	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);//right front  side
	glVertex3f(0.25, 0.8, 0);
	glVertex3f(0.3, 0.78, 0.03);
	glVertex3f(0.3, 0.42, 0.03);
	glVertex3f(0.25, 0.4, 0);
	glEnd();

	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);//right back side
	glVertex3f(0.25, 0.8, 0.2);
	glVertex3f(0.3, 0.78, 0.17);
	glVertex3f(0.3, 0.42, 0.17);
	glVertex3f(0.25, 0.4, 0.2);
	glEnd();

	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//left front  side
	glVertex3f(-0.25, 0.8, 0);
	glVertex3f(-0.3, 0.78, 0.03);
	glVertex3f(-0.3, 0.42, 0.03);
	glVertex3f(-0.25, 0.4, 0);
	glEnd();

	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);//left back side
	glVertex3f(-0.25, 0.8, 0.2);
	glVertex3f(-0.3, 0.78, 0.17);
	glVertex3f(-0.3, 0.42, 0.17);
	glVertex3f(-0.25, 0.4, 0.2);
	glEnd();

	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);//connector front right top
	glVertex3f(0.25, 0.85, 0.05);
	glVertex3f(0.25, 0.8, 0);
	glVertex3f(0.3, 0.78, 0.03);
	glEnd();

	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);//connector front right bottom
	glVertex3f(0.25, 0.35, 0.05);
	glVertex3f(0.25, 0.4, 0);
	glVertex3f(0.3, 0.42, 0.03);
	glEnd();

	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//connector front left top
	glVertex3f(-0.25, 0.85, 0.05);
	glVertex3f(-0.25, 0.8, 0);
	glVertex3f(-0.3, 0.78, 0.03);
	glEnd();

	glTexCoord2f(0.0f, 1.0f);
	glBegin(GL_POLYGON);//connector front left bottom
	glVertex3f(-0.25, 0.35, 0.05);
	glVertex3f(-0.25, 0.4, 0);
	glVertex3f(-0.3, 0.42, 0.03);
	glEnd();

	glTexCoord2f(1.0f, 0.0f);
	glBegin(GL_POLYGON);//connector back right top
	glVertex3f(0.25, 0.85, 0.15);
	glVertex3f(0.25, 0.8, 0.2);
	glVertex3f(0.3, 0.78, 0.17);
	glEnd();

	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);//connector back right bottom
	glVertex3f(0.25, 0.35, 0.15);
	glVertex3f(0.25, 0.4, 0.2);
	glVertex3f(0.3, 0.42, 0.17);
	glEnd();

	glTexCoord2f(0.0f, 0.0f);
	glBegin(GL_POLYGON);//connector back left top
	glVertex3f(-0.25, 0.85, 0.15);
	glVertex3f(-0.25, 0.8, 0.2);
	glVertex3f(-0.3, 0.78, 0.17);
	glEnd();

	glTexCoord2f(1.0f, 1.0f);
	glBegin(GL_POLYGON);//connector back left bottom
	glVertex3f(-0.25, 0.35, 0.15);
	glVertex3f(-0.25, 0.4, 0.2);
	glVertex3f(-0.3, 0.42, 0.17);
	glEnd();
	glDeleteTextures(1, &texture7);

	glBegin(GL_LINE_LOOP);//front
	glColor3f(0, 0, 0);
	glVertex3f(-0.25, 0.8, -0.001);
	glVertex3f(0.25, 0.8, -0.001);
	glVertex3f(0.25, 0.4, -0.001);
	glVertex3f(-0.25, 0.4, -0.001);
	glEnd();

	glBegin(GL_LINE_LOOP);//back
	glVertex3f(-0.25, 0.8, 0.201);
	glVertex3f(0.25, 0.8, 0.201);
	glVertex3f(0.25, 0.4, 0.201);
	glVertex3f(-0.25, 0.4, 0.201);
	glEnd();

	glBegin(GL_LINE_LOOP);//left
	glVertex3f(-0.301, 0.78, 0.03);
	glVertex3f(-0.301, 0.78, 0.17);
	glVertex3f(-0.301, 0.42, 0.17);
	glVertex3f(-0.301, 0.42, 0.03);
	glEnd();

	glBegin(GL_LINE_LOOP);//right
	glVertex3f(0.301, 0.78, 0.03);
	glVertex3f(0.301, 0.78, 0.17);
	glVertex3f(0.301, 0.42, 0.17);
	glVertex3f(0.301, 0.42, 0.03);
	glEnd();

	glBegin(GL_LINE_LOOP);//top
	glVertex3f(-0.25, 0.851, 0.05);
	glVertex3f(-0.25, 0.851, 0.15);
	glVertex3f(0.25, 0.851, 0.15);
	glVertex3f(0.25, 0.851, 0.05);
	glEnd();

	glBegin(GL_LINE_LOOP);//bottom
	glVertex3f(-0.25, 0.349, 0.05);
	glVertex3f(-0.25, 0.349, 0.15);
	glVertex3f(0.25, 0.349, 0.15);
	glVertex3f(0.25, 0.349, 0.05);
	glEnd();

	glBegin(GL_LINE_LOOP);//top front side
	glVertex3f(-0.25, 0.801, 0);
	glVertex3f(-0.25, 0.851, 0.05);
	glVertex3f(0.25, 0.851, 0.05);
	glVertex3f(0.25, 0.801, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);//top back side
	glVertex3f(-0.25, 0.801, 0.2);
	glVertex3f(-0.25, 0.851, 0.15);
	glVertex3f(0.25, 0.851, 0.15);
	glVertex3f(0.25, 0.801, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);//bottom front side
	glVertex3f(-0.25, 0.399, 0);
	glVertex3f(-0.25, 0.349, 0.05);
	glVertex3f(0.25, 0.349, 0.05);
	glVertex3f(0.25, 0.399, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);//bottom back side
	glVertex3f(-0.25, 0.399, 0.2);
	glVertex3f(-0.25, 0.349, 0.15);
	glVertex3f(0.25, 0.349, 0.15);
	glVertex3f(0.25, 0.399, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);//right top side
	glVertex3f(0.251, 0.851, 0.15);
	glVertex3f(0.301, 0.781, 0.17);
	glVertex3f(0.301, 0.781, 0.03);
	glVertex3f(0.251, 0.851, 0.05);
	glEnd();

	glBegin(GL_LINE_LOOP);//right bottom side
	glVertex3f(0.251, 0.349, 0.15);
	glVertex3f(0.301, 0.419, 0.17);
	glVertex3f(0.301, 0.419, 0.03);
	glVertex3f(0.251, 0.349, 0.05);
	glEnd();

	glBegin(GL_LINE_LOOP);//left bottom side
	glVertex3f(-0.251, 0.349, 0.151);
	glVertex3f(-0.301, 0.419, 0.171);
	glVertex3f(-0.301, 0.419, 0.031);
	glVertex3f(-0.251, 0.349, 0.051);
	glEnd();

	glBegin(GL_LINE_LOOP);//left top side
	glVertex3f(-0.251, 0.851, 0.151);
	glVertex3f(-0.301, 0.781, 0.171);
	glVertex3f(-0.301, 0.781, 0.031);
	glVertex3f(-0.251, 0.851, 0.051);
	glEnd();

}

void drawHammerHilt() {
	glColor3f(1, 1, 1);
	GLuint texture8 = loadTexture("wood.bmp");
	glPushMatrix();
	glTranslatef(0, 0.05, 0.07);
	//Face 1: behind
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.04, -0.4, 0.05);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.04, 0.3, 0.05);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, 0.3, 0.05);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.04, -0.4, 0.05);
	glEnd();

	//Face 2 : right
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.04, -0.4, 0.05);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.04, -0.4, 0.0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, 0.3, 0.0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.04, 0.3, 0.05);
	glEnd();

	//Face 3 : Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.04, 0.3, 0.05);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.04, 0.3, 0.0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.04, 0.3, 0.0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.04, 0.3, 0.05);
	glEnd();

	//Face 4 : Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.04, 0.3, 0.05);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.04, -0.4, 0.05);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.04, -0.4, 0.0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.04, 0.3, 0.0);
	glEnd();

	//Face 5 : Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.04, 0.3, 0.0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.04, -0.4, 0.0);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.04, -0.4, 0.0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.04, 0.3, 0.0);
	glEnd();

	//Face 6 : Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.04, -0.4, 0.0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.04, -0.4, 0.05);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.04, -0.3, 0.05);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.04, -0.3, 0.0);
	glEnd();
	glDeleteTextures(1, &texture8);
	glPopMatrix();
}



void display()
{

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 1.0, 0.0, 0);


	glColor3f(1, 1, 1);
	//drawHelmet();

	//glRotatef(0.010, 1, 1, 0);
	//drawHilt();
	//drawSword();
	drawHammer();
	drawHammerHilt();

	glDisable(GL_TEXTURE_2D);
=======
void drawDisk(float inner, float outer, float r, float g, float b, int type ,GLuint text) {

	GLUquadricObj* disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, type);
	glBindTexture(GL_TEXTURE_2D, text);
	gluQuadricTexture(disk, GL_TRUE);
	gluQuadricNormals(disk, GLU_SMOOTH);
	glColor3f(r, g, b);
	gluDisk(disk, inner, outer, 30, 30);

	gluDeleteQuadric(disk);
}

void drawCube() {
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
   // Top face (y = 1.0f)
   // Define vertices in counter-clockwise (CCW) order with normal pointing out
	//glColor3f(0.0f, 1.0f, 0.0f); 
	glTexCoord2f(1.0f, 0.0f);// Green
	glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	//glColor3f(1.0f, 0.5f, 0.0f); 
	glTexCoord2f(1.0f, 1.0f);// Orange
	glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	//glColor3f(1.0f, 0.0f, 0.0f); 
	glTexCoord2f(1.0f, 1.0f);// Red
	glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	//glColor3f(1.0f, 1.0f, 0.0f); 
	glTexCoord2f(1.0f, 0.0f);// Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	//glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);// Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	//glColor3f(1.0f, 0.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube
}


void finger(float length) {
	//fingerbase
	//drawCylinder(3, 3, 20, 255, 255, 255, GLU_LINE);

	GLuint joint = loadTexture("join.bmp");

	GLuint metal = loadTexture("metal.bmp");

	glPushMatrix();
	glTranslatef(18.5, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawCylinder(1.8, 1.8, length, 255, 255, 255, GLU_FILL,metal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 0, 0);
	glRotatef(90, 1, 0, 0);
	drawSphere(1.8, 255, 255, 255, GLU_FILL,joint);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 0, 0);
	glRotatef(fingerAngle, 0, 1, 0);
	glTranslatef(-18, 0, 0);

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawCylinder(1.8, 1.8, 8, 255, 255, 255, GLU_FILL,metal);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	drawSphere(1.8,255, 255, 255, GLU_FILL,joint);
	glPopMatrix();

	glDeleteTextures(1, &joint);

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotatef(fingerAngle, 0, 1, 0);
	glTranslatef(-10, 0, 0);

	GLuint fingertip = loadTexture("metal.bmp");

	//fingertip
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS); //front ( z = -1)
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, -2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glEnd();

	glBegin(GL_QUADS); //back ( z = 1)
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, 2);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();

	glBegin(GL_QUADS); //left 
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -1, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glEnd();

	glBegin(GL_QUADS); //right 
	glTexCoord2f(0, 0);
	glVertex3f(2, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, 0);
	glScalef(4, 2, 2);
	drawCube();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glDeleteTextures(1, &metal);
	glDeleteTextures(1, &fingertip);

}

void drawPalm() {

	GLuint palm = loadTexture("dotted.bmp");
	glBegin(GL_POLYGON); //z = -1
	glTexCoord2f(0.2, 0);
	glVertex3f(0,0,-1);
	glTexCoord2f(0.8, 0);
	glVertex3f(1,0,-1);
	glTexCoord2f(1, 0.5);
	glVertex3f(1.2,1,-1);
	glTexCoord2f(0.8, 1);
	glVertex3f(1,2,-1);
	glTexCoord2f(0.2, 1);
	glVertex3f(0,2,-1);
	glTexCoord2f(0, 0.5);
	glVertex3f(-0.2,1,-1);
	glEnd();

	glBegin(GL_POLYGON); //z = 1
	glTexCoord2f(0.2, 0);
	glVertex3f(0, 0, 1);
	glTexCoord2f(0.8, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 0.5);
	glVertex3f(1.2, 1, 1);
	glTexCoord2f(0.8, 1);
	glVertex3f(1, 2, 1);
	glTexCoord2f(0.2, 1);
	glVertex3f(0, 2, 1);
	glTexCoord2f(0, 0.5);
	glVertex3f(-0.2, 1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 2, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(1, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 2, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glDeleteTextures(1, &palm);
}

void drawHand() {
	glPushMatrix();
	glTranslatef(-2, -22.5, 0);
	glScalef(18, 12, 2);
	drawPalm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 25, 0);
	glRotatef(-90, 0, 0, 1);
	finger(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, 27, 0);
	glRotatef(-90, 0, 0, 1);
	finger(7);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9, 25, 0);
	glRotatef(-90, 0, 0, 1);
	finger(5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.5, 23, 0);
	glRotatef(-90, 0, 0, 1);
	finger(3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 3, 0);
	glRotatef(-70, 0, 0, 1);
	glScalef(0.6, 1, 1);
	finger(3);
	glPopMatrix();
}

void drawFootBase() {
	GLuint texture3 = loadTexture("grey.bmp");
	glPushMatrix();
	glScalef(5, 5, 7);
	glBegin(GL_QUADS); //front ( z = -1)
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(0, 1);
	glVertex3f(1,-1,-1);
	glTexCoord2f(1, 0);
	glVertex3f(1,2,-1);
	glTexCoord2f(1, 1);
	glVertex3f(-1,0.5,-1);
	glEnd();

	glBegin(GL_QUADS); //back ( z = 1)
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 0.5, 1);
	glEnd();

	glBegin(GL_QUADS); //down ( y = -1)
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //left ( x = -1)
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 0.5, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 0.5, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //right ( x = 1)
	glTexCoord2f(0, 0);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //up ( y = 1 / 2)
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 2, -1);
	glEnd();

	glPushMatrix();
	glTranslatef(3, 0.5, 0);
	glScalef(2, 1.5, 1);
	drawCube();
	glPopMatrix();

	glPopMatrix();

	glDeleteTextures(1, &texture3);
}

void drawFootExtension() {
	GLuint texture1 = loadTexture("texture.bmp");
	glPushMatrix();
	glScalef(3, 3, 10);
	glBegin(GL_QUADS); //front ( z = -1)
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -0.5, -1);
	glEnd();

	glBegin(GL_QUADS); //back ( z = 1)
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -0.5, 1);
	glEnd();

	glBegin(GL_QUADS); //down ( y = -1)
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //left ( x = -1)
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, -0.5, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, -0.5, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //right ( x = 1)
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, -1, 1);
	glEnd();

	glBegin(GL_QUADS); //up ( y = 1 / 2)
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -0.5, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, -0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 2, -1);
	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &texture1);

}

void drawAnkle() {
	GLuint texture1 = loadTexture("black.bmp");
	glPushMatrix();
	glTranslatef(0, -11, -16);
	glScalef(3.6, 3, 4);
	glBegin(GL_QUADS); //front ( z = -1)
	glTexCoord2f(0,0);
	glVertex3f(-2, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, -2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glEnd();

	glBegin(GL_QUADS); //back ( z = 1)
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, 2);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();

	glBegin(GL_QUADS); //left 
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -1, 2);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glEnd();

	glBegin(GL_QUADS); //right 
	glTexCoord2f(0, 0);
	glVertex3f(2, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, 2);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);
	glEnd();
	glPopMatrix();
	glDeleteTextures(1, &texture1);

}

void drawFoot() {
	glPushMatrix();
	glScalef(1, 0.6, 1);
	glRotatef(-90, 0, 1, 0);
	drawFootBase();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 0, 15);
	drawFootExtension();
	glPushMatrix();
	glTranslatef(20, 0, 0);
	glRotatef(180, 0, 1, 0);
	drawFootExtension();
	glPopMatrix();
	glPopMatrix();

}

void drawLeg() {
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);


	glPushMatrix();
	glTranslatef(0, 14, -15);
	glRotatef(kneeAngle, 1, 0, 0);
	glTranslatef(0, -15, 15);
	glPushMatrix();
	glTranslatef(0, -20, 0);
	glRotatef(180, 0, 1, 0);
	drawFoot();
	glPopMatrix();

	drawAnkle();

	GLuint texture4 = loadTexture("metal.bmp");
	glPushMatrix();
	glTranslatef(0, -8, -15);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(4.5, 5, 25, 255, 255, 255, GLU_FILL, texture4);
	glPopMatrix();
	glDeleteTextures(1, &texture4);

	glPopMatrix();

	texture4 = loadTexture("join.bmp");
	glPushMatrix();
	glTranslatef(0, 18, -15);
	glRotatef(90, 0, 1, 0);
	drawSphere(4.5, 0, 0, 0, GLU_FILL, texture4);
	glPopMatrix();
	glDeleteTextures(1, &texture4);

	GLuint texture5 = loadTexture("metal.bmp");
	glPushMatrix();
	glTranslatef(0, 20, -15);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(4.5, 5, 25, 255, 255, 255, GLU_FILL, texture4);
	glPopMatrix();
	glDeleteTextures(1, &texture5);

	glPopMatrix();
}

void drawArm() {
	glPushMatrix();
	glTranslatef(0,-7, 0);
	glRotatef(elbowAngle, 1, 0, 0);
	glTranslatef(0, 7, 0);
	glPushMatrix();
	glTranslatef(0, 27, 0);
	glPushMatrix();
	glScalef(0.5, 0.5, 1);
	drawHand();
	glPopMatrix();

	GLuint wrist = loadTexture("circular.bmp");

	glPushMatrix();
	glTranslatef(3.5, -12.1, 0);
	glScalef(2, 1, 1);
	glBegin(GL_QUADS); //front ( z = -1)
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, -3);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, -3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glEnd();

	glBegin(GL_QUADS); //back ( z = 1)
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, 3);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, 3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();

	glBegin(GL_QUADS); //left 
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, -3);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -1, 3);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glEnd();

	glBegin(GL_QUADS); //right 
	glTexCoord2f(0, 0);
	glVertex3f(2, -1, -3);
	glTexCoord2f(0, 1);
	glVertex3f(2, -1, 3);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);
	glEnd();

	glDeleteTextures(1, &wrist);



	GLuint arm = loadTexture("metalweb.bmp");

	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.5, -13, 0);
	glRotatef(90, 1, 0, 0);
	drawCylinder(3, 3, 20, 255, 255, 255, GLU_FILL , arm);
	glPopMatrix();
	glPopMatrix();

	GLuint joint = loadTexture("join.bmp");
	glPushMatrix();
	glTranslatef(3.5, -6.5, 0);
	glRotatef(90, 0, 1, 0);
	drawSphere(3, 255, 255, 255, GLU_FILL , joint);
	glPopMatrix();

	glPopMatrix();

	glDeleteTextures(1, &joint);

	glPushMatrix();
	glTranslatef(3.5, -8, 0);
	glRotatef(90, 1, 0, 0);
	drawCylinder(3, 3, 20, 255, 255, 255, GLU_FILL , arm);
	glPopMatrix();

	glDeleteTextures(1, &arm);
	glDeleteTextures(1, &joint);
}

void lowerBody() {

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	glScalef(20, 20, 4);

	GLuint metal = loadTexture("blackpolish.bmp");

	glBegin(GL_POLYGON);// z=-1 front
	glColor3f(1, 1, 1);
	glTexCoord2f(0,0.2);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0.5, 0);
	glVertex3f(0.5, -0.2, -1);
	glTexCoord2f(1, 0.2);
	glVertex3f(1, 0, -1);
	glTexCoord2f(0.8, 1);
	glVertex3f(0.9, 1, -1);
	glTexCoord2f(0.2, 1);
	glVertex3f(0.1, 1, -1);
	glEnd();

	glBegin(GL_POLYGON);// z=1
	glTexCoord2f(0, 0.2);
	glVertex3f(0, 0, 1);
	glTexCoord2f(0.5, 0);
	glVertex3f(0.5, -0.2, 1);
	glTexCoord2f(1, 0.2);
	glVertex3f(1, 0, 1);
	glTexCoord2f(0.8, 1);
	glVertex3f(0.9, 1, 1);
	glTexCoord2f(0.2, 1);
	glVertex3f(0.1, 1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.9, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.9, 1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.2, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, -0.2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.2, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, -0.2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0.1, 1, -1);
	glVertex3f(0.9, 1, -1);
	glVertex3f(0.9, 1, 1);
	glVertex3f(0.1, 1, 1);
	glEnd();

	glDeleteTextures(1, &metal);
	glPopMatrix();

	GLuint machine = loadTexture("metal.bmp");

	glPushMatrix();
	glTranslatef(0, 0, -4);
	glScalef(20, 20, 3);
	glBegin(GL_POLYGON);// z=-1 front
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 1, -1);
	glTexCoord2f(0.15, 0.1);
	glVertex3f(0.25, -0.1, -0.5);
	glTexCoord2f(0.5, 0);
	glVertex3f(0.5, -0.2, 0);
	glTexCoord2f(0.65, 0.1);
	glVertex3f(0.75, -0.1, -0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.9, 1, -1);
	glEnd();

	glBegin(GL_POLYGON);// z=0 back
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 1, 0);
	glTexCoord2f(0.15, 0.1);
	glVertex3f(0.25, -0.1, 0);
	glTexCoord2f(0.5, 0);
	glVertex3f(0.5, -0.2, 0);
	glTexCoord2f(0.65, 0.1);
	glVertex3f(0.75, -0.1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.9, 1, 0);
	glEnd();

	glDeleteTextures(1, &machine);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.25, -0.1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, -0.1, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0.9, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0.9, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.75, -0.1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.75, -0.1, -0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex3f(0.5, -0.2, 0);
	glVertex3f(0.25, -0.1, -0.5);
	glVertex3f(0.25, -0.1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex3f(0.5, -0.2, 0);
	glVertex3f(0.75, -0.1, -0.5);
	glVertex3f(0.75, -0.1, 0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -6);
	glRotatef(-8, 1, 0, 0);
	glScalef(20, 20, 2);

	GLuint text = loadTexture("circular.bmp");

	glBegin(GL_QUADS); //front
	glColor3f(1, 0, 0);
	glTexCoord2f(0.5,1);
	glVertex3f(0.5, 1, 1);
	glTexCoord2f(0,0.5);
	glVertex3f(0.1682, 0.5, 1);
	glTexCoord2f(0.5,0);
	glVertex3f(0.5, -0.2, 1);
	glTexCoord2f(1,0.5);
	glVertex3f(0.8318, 0.5, 1);
	glEnd();

	

	glBegin(GL_POLYGON); //back
	glColor3f(1, 1, 1);
	glTexCoord2f(0.5, 1);
	glVertex3f(0.5, 1, 0);
	glTexCoord2f(0, 0.5);
	glVertex3f(0.1682, 0.5, 0);
	glTexCoord2f(0.5, 1);
	glVertex3f(0.5, -0.2, 0);
	glTexCoord2f(1, 0.5);
	glVertex3f(0.8318, 0.5, 0);
	glEnd();

	glBegin(GL_QUADS); //left top
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.1682, 0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.1682, 0.5, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 1, 0);
	glEnd();

	glBegin(GL_QUADS); //RIGHT top
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.8318, 0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.8318, 0.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 1, 0);
	glEnd();

	glBegin(GL_QUADS); //bottom right
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.2, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.8318, 0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.8318, 0.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, -0.2, 0);
	glEnd();

	glBegin(GL_QUADS); //left bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.2, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.1682, 0.5, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.1682, 0.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, -0.2, 0);
	glEnd();

	glDeleteTextures(1, &text);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 9, -7.5);
	glRotatef(-8, 1, 0, 0);
	glScalef(20, 20, 2);
	GLuint dot = loadTexture("dotted.bmp");
	drawDisk(0.1, 0.2, 1, 0, 0, GLU_FILL , dot);
	glDeleteTextures(1, &dot);
	glPopMatrix();
	glPopMatrix();

}

void upperBody() {
	GLuint electronic = loadTexture("electronic.bmp");
	glPushMatrix();
	glTranslatef(-18, 20, 0);
	glScalef(16, 8, 4);
	glBegin(GL_POLYGON); //z = -1
	glColor3f(1, 1, 1);
	glTexCoord2f(0.2, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0.8, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 0.5);
	glVertex3f(1.2, 1, -1);
	glTexCoord2f(0.8, 1);
	glVertex3f(1, 2, -1);
	glTexCoord2f(0.2, 1);
	glVertex3f(0, 2, -1);
	glTexCoord2f(0, 0.5);
	glVertex3f(-0.2, 1, -1);
	glEnd();

	glBegin(GL_POLYGON); //z = 1
	glTexCoord2f(0.2, 0);
	glVertex3f(0, 0, 1);
	glTexCoord2f(0.8, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 0.5);
	glVertex3f(1.2, 1, 1);
	glTexCoord2f(0.8, 1);
	glVertex3f(1, 2, 1);
	glTexCoord2f(0.2, 1);
	glVertex3f(0, 2, 1);
	glTexCoord2f(0, 0.5);
	glVertex3f(-0.2, 1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 2, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(1, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.2, 1, -1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 2, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 2, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 2, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1.2, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1.2, 1, -1);
	glEnd();
	glPopMatrix();

	glDeleteTextures(1, &electronic);

	GLuint socket = loadTexture("join.bmp");

	glPushMatrix();
	glTranslatef(-23, 28, 0);
	glRotatef(90, 1, 0, 0);
	drawSphere(3,1,1,1,GLU_FILL,socket);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 28, 0);
	glRotatef(90, 1, 0, 0);
	drawSphere(3, 1, 1, 1, GLU_FILL,socket);
	glPopMatrix();

	glDeleteTextures(1, &socket);

	GLuint polish = loadTexture("blackpolish.bmp");
	glPushMatrix();
	glTranslatef(-29, 28, 0);
	glScalef(3, 3, 4);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 28, 0);
	glScalef(3, 3, 4);
	drawCube();
	glPopMatrix();
	glDeleteTextures(1, &polish);
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glRotatef(1, 0, 1, 0);

	lowerBody();
	upperBody();

	glPushMatrix();
	glTranslatef(-29, 15, 3);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(1, 0.5, 0.8);
	drawArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 15, 3);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(1, 0.5, 0.8);
	drawArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, -20, 7);
	drawLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, -20, 7);
	drawLeg();
	glPopMatrix();

	


	
	//
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
>>>>>>> parent of e7121b9... Revert "update"
}
//--------------------------------------------------------------------


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;
	glOrtho(-80, 80, -45, 45, -45, 45);

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------