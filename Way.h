#pragma once
#include <vector>
#include "Graphics.h"
#include <random>
#include <iostream>

using namespace std;

class Way {

	Graphics* gfx;
	vector<D2D_POINT_2F> currentWay; 
	vector<D2D_POINT_2F> Cities;

	int i = 0;
	double fitness = 1;
	long sum;


public:
	Way(Graphics* gfx, vector<D2D_POINT_2F> &Cities);
	~Way();

	static bool sortByFitness(Way a, Way b);
	void draw();
	long sumup();
	void mutate2();
	void mutate();
	static void crossover(Way &target, Way &usage, int length);

};