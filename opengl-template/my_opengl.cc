#include "my_opengl.h"
#include <math.h>
#include <GL/glh_glut.h>
#include "load_obj.h"
using namespace glh;
GLfloat xRot = 0;
GLfloat yRot = 0;
GLfloat zRot = 0;

int myState = 0;
int scalState = 0;
int oldX = 0;
int oldY = 0;
float rate = 1;
double x_trans, y_trans, z_trans = 0;
double x_old_theta, y_old_theta, z_old_theta = 0;
float scale=0;

void OpenglInit(int argc, char** argv)
{
	obj1.Init("./dataset/cat.obj");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowSize(600, 600);			//set window size
	glutInitWindowPosition(100, 150);		//set window position
	glutCreateWindow("Display");		//window name
	
	// scale
	scale = 0.9f / (2.0f*obj1.radius_);
	glScalef(scale, scale, scale);

	// text
	
	glRasterPos2f(-0.9, 0.7);
	DrawString("linlinge");

	// message
	glutDisplayFunc(DisplayFunc);//��Ļ��ʾ�Ļص�����
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);//����ʱ�ص���������û����Ϣʱ���ã�
	glutKeyboardFunc(KeyboardFunc);//���֡���ĸ���İ������Ļص�����
	glutSpecialFunc(SpecialFunc);//���ⰴ����⣨F1~F12�����Ƽ���
	glutMouseFunc(MouseFunc);//�����
	glutMotionFunc(MotionFunc);//��갴���϶����
	
	glutPassiveMotionFunc(PassiveMotionFunc);//����ƶ����

	// main loop
	glutMainLoop();
}

void SetBackground1()
{
	// exmaple: shape1
	float color = 0.0f;
	glBegin(GL_POINTS);
	for (float posY = -1.0f; posY <= 1.0f; posY += 0.001f)
	{
		color += 0.0005f;
		//���õ���ɫ
		glColor3f(pow(color, 2), color, color); //���õ���ɫ
		for (float posX = 1.0f; posX >= -1.0f; posX -= 0.001f)
		{
			//���Ƶ�
			glVertex3f(posX, posY, 0);
		}
	}
	glEnd();
}

void AddLight()
{
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	GLfloat LightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat LightDif[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat LightPos[] = { 0.0, 20.0, 80.0, 0.0 };

	//light
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
}

// insert to DisplayFunc
void AddText()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.9/scale,0.9/scale);
	DrawString("[Page	Up] Zoom in");
	glRasterPos2f(-0.9 / scale, 0.8 / scale);
	DrawString("[Page	Down] Zoom out");
}

void DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color buffer
	glDisable(GL_DEPTH_TEST | GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.8f, 0.8f, 0.8f , 0.1);	//can set the background


	AddText();

	// �������״̬����ת
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	

	AddLight();
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (auto& v : obj1.points_)
	{
		glVertex3f(v.x,v.y,v.z);
	}
	glEnd();


	glPopMatrix();	
	glutSwapBuffers();	//swap buffer
}

void ReshapeFunc(GLsizei width, GLsizei height)
{
	/*if (height == 0) height = 1;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

void Plot(vector<float>& x, vector<float>& y)
{
	glColor3f(1, 0, 0);
	if (x.size() == y.size())
	{
		vector<float>::iterator it = max_element(y.begin(), y.end());
		float y_max = *it;
		it = min_element(y.begin(), y.end());
		float y_min = *it;

		glBegin(GL_LINES);
		for (int i = 0; i < x.size() - 1; i++)
		{
			glVertex3f(TOSCREEN(x[i], x[0], x[x.size() - 1]), TOSCREEN(y[i], y_min, y_max), 0);
			glVertex3f(TOSCREEN(x[i + 1], x[0], x[x.size() - 1]), TOSCREEN(y[i + 1], y_min, y_max), 0);
		}
		glEnd();
	}
	else
	{
		cout << "Error: The Dimension of x and y not matched!" << endl;
	}
}

void Mesh(vector<vector<Vec3f>>& dat)
{
	for (int i = 0; i < dat.size() - 1; i++)
	{
		for (int j = 0; j < dat[0].size() - 1; j++)
		{
			float colorx = 0.6*(sin(10 * dat[i][j].x) + 1);
			float colory = 0.6*(sin(10 * dat[i][j].y) + 1);
			float colorz = 0.6*(sin(10 * dat[i][j].x + 1) + 1);

			glColor3f(colorx, colory, colorz);
			glBegin(GL_LINE_LOOP);
			glVertex3f(dat[i][j].x, dat[i][j].y, dat[i][j].z);
			glVertex3f(dat[i][j + 1].x, dat[i][j + 1].y, dat[i][j + 1].z);
			glVertex3f(dat[i + 1][j + 1].x, dat[i + 1][j + 1].y, dat[i + 1][j + 1].z);
			glVertex3f(dat[i + 1][j].x, dat[i + 1][j].y, dat[i + 1][j].z);
			glVertex3f(dat[i][j].x, dat[i][j].y, dat[i][j].z);
			glEnd();
		}
	}
}

void DrawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(128);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}



//����ʱ���õĺ���
void IdleFunc()
{
	glutPostRedisplay();//���»��ƣ�������DisplayFunc()������
}
//���֡���ĸ���������
void KeyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		
			
	}

	if (key == 's' || key == 'S')
	{
		
	}

	if (key == 'a' || key == 'A')
	{
	
	}

	if (key == 'd' || key == 'D')
	{
		
	}

}
//F1~F12�����Ƽ����
void SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		xRot -= 5.0f;
		break;
	case GLUT_KEY_DOWN:
		xRot += 5.0f;
		break;
	case GLUT_KEY_LEFT:
		yRot -= 5.0f;
		break;
	case GLUT_KEY_RIGHT:
		yRot += 5.0f;
		break;
	case GLUT_KEY_F1:
		zRot += 5.0f;
		break;
	case GLUT_KEY_F2:
		zRot -= 5.0f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		glScalef(0.9, 0.9, 0.9);
		break;
	case GLUT_KEY_PAGE_UP:
		glScalef(1.1, 1.1, 1.1);
		break;


	}

	// ʹ���µ��������»��Ƴ���
	glutPostRedisplay();
}
//�����
void MouseFunc(int button, int state, int x, int y)
{
	//button  ��갴�� 0 -- ���    1 -- �м�   2 -- �Ҽ�
	//state  ���״̬  0 -- ����  1 -- ̧��
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		oldX = x;
		oldY = y;
		myState = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		myState = 0;
		oldX = x;
		oldY = y;
		x_old_theta = xRot;
		y_old_theta = yRot;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		scalState = 1;
		oldX = x;
		oldY = y;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		scalState = 0;

	glutPostRedisplay();
}

//��갴���϶�
void MotionFunc(int x, int y)
{
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	
	if (myState == 1)
	{
		yRot = (x - oldX) / 3 + y_old_theta;
		xRot = (y - oldY) / 3 + x_old_theta;
	}
	if (scalState == 1)
	{
		if (y > oldY)
			rate += 0.02;
		else
		{
			rate -= 0.02;
			if (rate < 0.1)
				rate = 0.1;
		}
		oldX = x;
		oldY = y;
	}
	glutPostRedisplay();
}



//����ƶ�
void PassiveMotionFunc(int x, int y)
{
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	
}