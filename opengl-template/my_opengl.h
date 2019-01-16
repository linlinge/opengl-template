#pragma once
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
//#include <gl/glut.h>
#include <vector>
#include "main.h"
using namespace std;

void OpenglInit(int argc, char** argv);
void DisplayFunc();//��ʾ����
void IdleFunc();//����ʱ���õĺ���
void KeyboardFunc(unsigned char Key, int x, int y);//���֡���ĸ���������
void SpecialFunc(int Key, int x, int y);//F1~F12�����Ƽ����
void MouseFunc(int button, int state, int x, int y);//�����
void MotionFunc(int x, int y);//��갴���϶�
void PassiveMotionFunc(int x, int y);//����ƶ�
void ReshapeFunc(GLsizei width, GLsizei height);



void AddLight();
void DrawString(const char* str);
void SetBackground1();
void Plot(vector<float>& x, vector<float>& y);
void Mesh(vector<vector<Vec3f>>& dat);
