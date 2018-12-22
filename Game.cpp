#include "Game.h"
#include "Way.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>

using namespace std;


Game::Game(Graphics * gfx) :
	gfx(gfx)
{
	
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	
	input.open("lelz.txt");

	int a;
	int b;
	while (input >> a) {
		input >> b;
		Cities.push_back(D2D1::Point2F(a, b));
	}

	myfile.open("lelz.txt");
	for (auto &a : Cities) {
		myfile << a.x << std::endl;
		myfile << a.y << std::endl;
	}

	for (int i = 0; i < size; i++) {
		ways.push_back(Way(gfx, Cities));
	}


}

Game::~Game()
{
}

void Game::Run()
{
	gfx->BeginDraw();
	UpdateModel();
	ComposeFrame();
	gfx->EndDraw();
}

void Game::UpdateModel()
{
	/*GetCursorPos(&point);

	if (GetAsyncKeyState(VK_LBUTTON) & 1) {
		Cities.push_back(D2D1::Point2F(point.x, point.y));
		myfile << point.x << endl; 
		myfile << point.y << endl;
	}
	*/

	for (auto &i : ways) {
		i.sumup();
	}

	std::sort(ways.begin(), ways.end(), Way::sortByFitness);

	for (int i = 0; i < int(ways.size()/2); i++) {
		ways[i].mutate();
		ways[i].mutate();
		ways[i].mutate();
		ways[i].mutate();
		ways[i].mutate2();
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(ways.size() / 2, ways.size() - 1);
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
	}

	for (int i = ways.size() / 2; i < ways.size() -1; i++) {
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(ways.size() / 2, ways.size() - 1);
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		Way::crossover(ways[i], ways[dist(rng)], ways.size());
		ways[i].mutate();
		ways[i].mutate();
	}

	std::sort(ways.begin(), ways.end(), Way::sortByFitness);

	for (int i = 0; i < int(ways.size() / 5); i++) {
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 11);

		ways[i] = ways[ways.size() - 1];

		if (dist(rng) >= 10) {
			ways[i].mutate2();
		}

		for (int j = 0; j < dist(rng); j++) {
			ways[i].mutate();
		}
	}
}

void Game::ComposeFrame()
{
	
	gfx->ClearScreen(255, 255, 255);
	ways[size - 1].draw();
	std::cout << ways[size - 1].sumup() << std::endl;
	
	for (auto &a : Cities) {
		gfx->DrawCircle(a.x, a.y, 3.0f, 0, 0, 0, 1.0f);
	}

	
}
