#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"


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