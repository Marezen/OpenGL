#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"
//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer(void)
{
	xeye = sin(ugaoy)*sin(ugaox)*r;
	yeye = cos(ugaoy)*r;
	zeye = sin(ugaoy)*cos(ugaox)*r;
}
CGLRenderer::~CGLRenderer(void)
{
}
#pragma region osnovne funkcije
bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd ;
   	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
   	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
   	pfd.nVersion   = 1; 
   	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
   	pfd.iPixelType = PFD_TYPE_RGBA; 
   	pfd.cColorBits = 32;
   	pfd.cDepthBits = 24; 
   	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	
	if (nPixelFormat == 0) return false; 

	BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
  	
	if (!bResult) return false; 

   	m_hrc = wglCreateContext(pDC->m_hDC); 

	if (!m_hrc) return false; 

	return true;	
}
void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//ucitavamo teksture
	B[0] = LoadTexture("back.jpg");
	B[1] = LoadTexture("left.jpg");
	B[2] = LoadTexture("front.jpg");
	B[3] = LoadTexture("right.jpg");
	B[4] = LoadTexture("top.jpg");
	B[5] = LoadTexture("bot.jpg");
	spider = LoadTexture("spider.png");
	glEnable(GL_TEXTURE_2D);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}
UINT CGLRenderer::LoadTexture(char* filename)
{
	UINT textureID;
	DImage img;
	img.Load(CString(filename));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
	return textureID;
}
void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	// ... 
	glDeleteTextures(1, &spider);
	glDeleteTextures(6, B);
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}
void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//FOV 50
	gluPerspective(50, (double)w / (double)h, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}
#pragma endregion


void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xeye, yeye, zeye, 0, 5, 0, 0, 1, 0);
	
	DrawAxis();
	DrawEnvCube(50);

	glTranslatef(0, 2.5, 0);
	//spider
	DrawSpider();
	glFlush();
	SwapBuffers(pDC->m_hDC);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}
void CGLRenderer::DrawAxis()
{
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 10);
	glEnd();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
}
//funkcija za okolinu:
void CGLRenderer::DrawEnvCube(double a)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, B[0]);
	glBegin(GL_QUADS);
	//zadnnja
	glTexCoord2f(0, 1); // tacka teksture
	glVertex3d(a / 2, 0, a / 2);
	glTexCoord2f(0, 0);
	glVertex3d(a / 2, a, a / 2);
	glTexCoord2f(1, 0);
	glVertex3d(-a / 2, a, a / 2);
	glTexCoord2f(1, 1);
	glVertex3d(-a / 2, 0, a / 2);
	glEnd();
	//leva
	glBindTexture(GL_TEXTURE_2D, B[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3d(-a / 2, 0, a / 2);
	glTexCoord2f(0, 0);
	glVertex3d(-a / 2, a, a / 2);
	glTexCoord2f(1, 0);
	glVertex3d(-a / 2, a, -a / 2);
	glTexCoord2f(1, 1);
	glVertex3d(-a / 2, 0, -a / 2);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, B[2]);
	glBegin(GL_QUADS);
	//prednja
	glTexCoord2f(0, 1);
	glVertex3d(-a / 2, 0, -a / 2);
	glTexCoord2f(0, 0);
	glVertex3d(-a / 2, a, -a / 2);
	glTexCoord2f(1, 0);
	glVertex3d(a / 2, a, -a / 2);
	glTexCoord2f(1, 1);
	glVertex3d(a / 2, 0, -a / 2);
	glEnd();

	//desno:
	glBindTexture(GL_TEXTURE_2D, B[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3d(a / 2, 0, -a / 2);
	glTexCoord2f(0, 0);
	glVertex3d(a / 2, a, -a / 2);
	glTexCoord2f(1, 0);
	glVertex3d(a / 2, a, a / 2);
	glTexCoord2f(1, 1);
	glVertex3d(a / 2, 0, a / 2);
	glEnd();

	//gore 
	glBindTexture(GL_TEXTURE_2D, B[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3d(-a / 2, a, -a / 2);
	glTexCoord2f(0, 0);
	glVertex3d(-a / 2, a, a / 2);
	glTexCoord2f(1, 0);
	glVertex3d(a / 2, a, a / 2);
	glTexCoord2f(1, 1);
	glVertex3d(a / 2, a, -a / 2);
	glEnd();

	//dole
	glBindTexture(GL_TEXTURE_2D, B[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3d(-a / 2, 0, -a / 2);
	glTexCoord2f(0, 0);
	glVertex3d(a / 2, 0, -a / 2);
	glTexCoord2f(1, 0);
	glVertex3d(a / 2, 0, a / 2);
	glTexCoord2f(1, 1);
	glVertex3d(-a / 2, 0, a / 2);
	glEnd();
}

//funkcije za crtanje pauka:
void CGLRenderer::DrawSphere(double r1, int nSeg, double texU, double texV, double texR)
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spider);

	int step1 = nSeg; //latituda
	int step2 = nSeg * 2; // longituda

	glBegin(GL_QUAD_STRIP);
	//ovo nam je obilazak
	for (int j = -90; j < 90; j += step1) {
		for (int i = 360; i >= 0; i -= step2) {

			//teksture ucitaju celu spider teksturu,ne odvajam nigde posebno za texU i texV

			glNormal3f(sin(i * toRad) * cos(j * toRad), sin(j * toRad), cos(i * toRad) * cos(j * toRad));
			glTexCoord2f(i / 360., (90 - j) / 180.);
			glVertex3f(r1 * sin(i * toRad) * cos(j * toRad), r1 * sin(j * toRad), r1 * cos(i * toRad) * cos(j * toRad));

			glNormal3f(sin(i * toRad) * cos((j + step1) * toRad), sin((j + step1) * toRad), cos(i * toRad) * cos((j + step1) * toRad));
			glTexCoord2f(i / 360., (90 - (j + step1)) / 180.);
			glVertex3f(r1 * sin(i * toRad) * cos((j + step1) * toRad), r1 * sin((j + step1) * toRad), r1 * cos(i * toRad) * cos((j + step1) * toRad));
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glRotatef(90, 0, 1, 0);
}
void CGLRenderer::DrawCone(double r, double h, int nSeg, double texU, double texV, double texR)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, spider);
	glColor3f(0.2, 0.2, 0.2);
	//odredimo korak za segmente teksture
	double alfaStep = (2 * pi) / nSeg;
	double alfa = 0.0;

	//FAN zbog kupe
	glBegin(GL_TRIANGLE_FAN);
	//vrh,od te tacke crta sve ostalo
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, h, 0.0);
	//i sad za svaki segment odredimo teme i njegovu normalu
	for (int i = 0; i <= nSeg; i++)
	{
		//menja se x i z osa,a Y ne,jer po Y ide samo u visinu,to ne bi trebalo da menjamo
		glNormal3f(cos(alfa), 0.0, sin(alfa));

		//nisam uspeo da ucitam teksturu kako treba
		glTexCoord2f(texU+cos(alfa), texV);
		//za poluprecnik,tamo ce biti tacka
		glVertex3f(r * cos(alfa), 0.0, r * sin(alfa));
		alfa += alfaStep;
	}
	glEnd();
}
//crtanje pauka
void CGLRenderer::DrawLegSegment(double r, double h, int nSeg)
{
	glPushMatrix();
	//oko Y ose,da bi se pravilno pozicioniralo
	glRotatef(-30, 0, 1, 0);
	//desne 4 noge
	for (int i = 0; i < 4; i++)
	{
		DrawLeg();
		glRotatef(30, 0, 1, 0);
	}
	glRotatef(30, 0, 1, 0);
	//leve noge
	for (int i = 0; i < 4; i++)
	{
		DrawLeg();
		glRotatef(30, 0, 1, 0);
	}
	glPopMatrix();
}
void CGLRenderer::DrawLeg()
{
	glPushMatrix();
	glTranslatef(0, -1, 1);
	glRotatef(45, 1, 0, 0); // savije nogu
	DrawCone(0.5, 5, 9, 0.75, 0.75, 10); // manji deo
	glTranslatef(0, 5, 0); // pomeri na vrh Cone-a i crtaj sferu
	DrawSphere(0.6, 1, 0, 0, 0);
	glRotatef(85, 0, 0, 1); // u odnosu na pocetni polozaj za 85
	DrawCone(0.5, 5, 15, 0., 0., 0); // nacrta veci deo noge.
	glPopMatrix();
}
void CGLRenderer::DrawSpiderBody()
{
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	glPushMatrix();
	glScalef(1, 0.5, 1); // spolosteno za 50%
	glTranslatef(10, -2.5, 0);
	DrawSphere(2.5, 10, 0, 0, 0);

	glPopMatrix();

	glPushMatrix();
	glScalef(1, 0.2, 1); // za 80% spoljosteno
	glTranslatef(6., -6, 0);
	DrawSphere(1.5, 10, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 0.2, 1.5); // za 80% spoljosteno
	glTranslatef(4., -6, 0);
	DrawSphere(1, 10, 0, 0, 0);
	glPopMatrix();
	glPopMatrix();
}
void CGLRenderer::DrawSpider()
{
	glPushMatrix();
	DrawSpiderBody();
	glTranslatef(0, -0.3, 0);
	DrawLegSegment(1, 10, 5);
	glPopMatrix();
}