#pragma once

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);
	
	//osnovne funkcije
	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);				
	void DestroyScene(CDC* pDC);			

	//funkcije za zadatak:
	UINT LoadTexture(char* filename);
	void DrawEnvCube(double a);
	void DrawSphere(double r, int nSeg, double texU, double texV, double texR);
	void DrawCone(double r, double h, int nSeg, double texU, double texV, double texR);
	void DrawLeg();
	void DrawSpiderBody();
	void DrawSpider();
	void DrawLegSegment(double r, double h, int nSeg);
	void DrawAxis();
	//isto kao kod bagera
	float angle1 = 0;
	float angle2 = 0;
	float angle3 = 0;
	float angle4 = 0;
	float xeye;
	float yeye;
	float zeye;
	float ugaox = 180;
	float ugaoy = 30;
	float r = 20;
	UINT B[6];
	UINT spider;

	float toRad = 0.0174532925;
	float pi = 3.141592;
protected:
	HGLRC	 m_hrc;

};
