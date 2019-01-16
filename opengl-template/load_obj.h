#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "main.h"
using namespace std;

class Patch {
public:
	vector<int> vertex_id_;
	vector<int> texture_id_;
	vector<int> normal_id_;
	Vec3f normal_;
	Vec3f color_;
};

class Obj {	
	void get_radius();
public:
	float radius_;

	string filename;
	vector<Vec3f> points_;
	vector<Patch> faces_;
	vector<Vec3f> vn_;
	vector<Vec3f> vt_;
	Obj(string filename);
	void Init(string filename);
	Obj() {};
	bool LoadObjFile();
	
};

extern Obj obj1;
