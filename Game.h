#pragma once
#include "Graphics.h"
#include "Way.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Game {

	Graphics* gfx;
	Way* way;
	ofstream myfile;
	ifstream input;
	vector<Way> ways;
	vector<D2D_POINT_2F> Cities;// = { D2D1::Point2F(600, 324), D2D1::Point2F(1231, 243),  D2D1::Point2F(20, 800), D2D1::Point2F(59, 29) };

	POINT point;
	bool safed = false;
	float length = 567354230;
	int size = 80;

public:
	
	
	Game(Graphics* gfx);
	~Game();

	void Run();
	void UpdateModel();
	void ComposeFrame();
};