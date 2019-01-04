#include "my_opengl.h"
#include <math.h>
#include <GL/glh_glut.h>
using namespace glh;



void OpenglInit(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowSize(800, 600);			//set window size
	glutInitWindowPosition(100, 150);		//set window position
	glutCreateWindow("Display");		//window name
	glutDisplayFunc(DisplayFunc);//屏幕显示的回调函数
	glutIdleFunc(IdleFunc);//闲置时回调函数（当没有消息时调用）
	glutKeyboardFunc(KeyboardFunc);//数字、字母键的按键检测的回调函数
	glutSpecialFunc(SpecialFunc);//特殊按键检测（F1~F12，控制键）
	glutMouseFunc(MouseFunc);//鼠标检测
	glutMotionFunc(MotionFunc);//鼠标按着拖动检测
	glutPassiveMotionFunc(PassiveMotionFunc);//鼠标移动检测


	glutMainLoop();
}


void DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color buffer
	glDisable(GL_DEPTH_TEST | GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

	glClearColor(0.6f, 0.6f, 0.6f , 0.1);	//can set the background


	float color = 0.0f;
	glBegin(GL_POINTS);
	for (float posY = -1.0f; posY <= 1.0f; posY += 0.001f)
	{
		color += 0.0005f;
		//设置点颜色
		glColor3f(pow(color,2), color, color); //设置点颜色
		for (float posX = 1.0f; posX >= -1.0f; posX -= 0.001f)
		{
			//绘制点
			glVertex2f(posX, posY);
		}
	}
	glEnd();
	glutSwapBuffers();	//swap buffer
}


void plot(vector<float>& x, vector<float>& y)
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

//闲置时调用的函数
void IdleFunc()
{
	glutPostRedisplay();//重新绘制（即调用DisplayFunc()函数）
}
//数字、字母键按键检测
void KeyboardFunc(unsigned char Key, int x, int y)
{
	if (Key == 'w' || Key == 'W')
	{
		
			
	}

	if (Key == 's' || Key == 'S')
	{
		
	}

	if (Key == 'a' || Key == 'A')
	{
	
	}

	if (Key == 'd' || Key == 'D')
	{
		
	}
}
//F1~F12、控制键检测
void SpecialFunc(int Key, int x, int y)
{
	if (Key == GLUT_KEY_UP)
	{
		
	}

	if (Key == GLUT_KEY_DOWN)
	{
		
	}

	if (Key == GLUT_KEY_LEFT)
	{
		
	}

	if (Key == GLUT_KEY_RIGHT)
	{
		
	}
}
//鼠标检测
void MouseFunc(int button, int state, int x, int y)
{
	//button  鼠标按键 0 -- 左键    1 -- 中键   2 -- 右键
	//state  鼠标状态  0 -- 按下  1 -- 抬起
	//x,y  鼠标的像素点坐标（以窗口的左上角为原点的坐标系）
	if (button == 0)
	{
		if (state == 0)
		{
	
		}
		if (state == 1)
		{
			
		}
	}
	if (button == 1)
	{
		if (state == 0)
		{
			
		}
		if (state == 1)
		{
			
		}
	}
	if (button == 2)
	{
		if (state == 0)
		{
			
		}
		if (state == 1)
		{
			
		}
	}
}
//鼠标按着拖动
void MotionFunc(int x, int y)
{
	//x,y  鼠标的像素点坐标（以窗口的左上角为原点的坐标系）
	
}
//鼠标移动
void PassiveMotionFunc(int x, int y)
{
	//x,y  鼠标的像素点坐标（以窗口的左上角为原点的坐标系）
	
}