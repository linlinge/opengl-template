#pragma once
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

extern void OpenglInit(int argc, char** argv);
struct Vector2D
{
	float fX;
	float fY;
};

extern Vector2D g_vector2D;

void DisplayFunc();//��ʾ����

void IdleFunc();//����ʱ���õĺ���

void KeyboardFunc(unsigned char Key, int x, int y);//���֡���ĸ���������

void SpecialFunc(int Key, int x, int y);//F1~F12�����Ƽ����

void MouseFunc(int button, int state, int x, int y);//�����

void MotionFunc(int x, int y);//��갴���϶�

void PassiveMotionFunc(int x, int y);//����ƶ�
