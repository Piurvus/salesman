#include "Way.h"
#include <random>
#include <algorithm>
#include <chrono>

Way::Way(Graphics * gfx, vector<D2D_POINT_2F>& Cities):
	gfx(gfx), Cities(Cities)
{
	for (auto &i : this->Cities) {
		currentWay.push_back(i);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(std::begin(currentWay), std::end(currentWay), e);


	//std::random_shuffle(currentWay.begin(), currentWay.end());

}

Way::~Way()
{
}

bool Way::sortByFitness(Way a, Way b)
{
	return a.fitness < b.fitness;
}

void Way::draw()
{
	for (auto &i : currentWay) {
		if ( &i != &currentWay.back() ) {
			gfx->DrawLine(i.x, i.y, std::next(&i)->x, std::next(&i)->y);	//(&i + sizeof(D2D_POINT_2F))->y
		}
		else {
			gfx->DrawLine(i.x, i.y, currentWay[0].x, currentWay[0].y);
		}
	}
}

long Way::sumup()
{
	sum = 0;

	for (auto &i : currentWay) {
		if (std::next(&i) != &currentWay.back()) {
			sum += sqrt(pow(i.x - std::next(&i)->x, 2) + pow(i.y - std::next(&i)->y, 2));
		}
		else {
			sum += sqrt(pow(i.x - currentWay.front().x, 2) + pow(i.y - currentWay.front().y, 2));
			fitness = 1.0 / sum;
			return sum;
		}
	}
}

void Way::mutate2()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10*Cities.size()); 

	int index = dist(rng) % (Cities.size() - 1);

	D2D_POINT_2F replacement = currentWay[index];
	D2D_POINT_2F city = Cities[dist(rng) % (Cities.size() - 1)];

	for (auto &i : currentWay) {
		if (i.x == city.x && i.y == city.y) {
			// i ist City
			i = replacement;
			currentWay[index] = city;
			break;
		}
	}
}

void Way::mutate()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10 * Cities.size());

	int index = dist(rng) % (Cities.size() - 1);
	int index2 = dist(rng) % (Cities.size() - 1);
	
	D2D_POINT_2F city = currentWay[index];
	currentWay.erase(currentWay.begin() + index);
	currentWay.insert(currentWay.begin() + index2, city);

}

void Way::crossover(Way & target, Way & usage, int length)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 7000);
	
	int crossovers = dist(rng) % 5;

	for (int i = 0; i < crossovers; i++) {
		int index = 0;
		int count = 0;
		while (index + count > length) {
			index = dist(rng) % length;
			count = dist(rng) % 20;
		}
		std::vector<D2D_POINT_2F> forLater;
		std::vector<D2D_POINT_2F> forRefill;
		
		//	add new crossover
		for (int i = 0; i < count; i++) {
			forRefill.push_back(target.currentWay[index + i]);
			target.currentWay[index + i] = usage.currentWay[index + i];
			forLater.push_back(usage.currentWay[index + i]);
		}

		//	fix the doubled points
		
		for (int i = 0; i < target.currentWay.size(); i++) {
			
			if (i < index || i > index + count) {

				for (auto &a : forLater) {
					if (a.x == target.currentWay[i].x && a.y == target.currentWay[i].y) {
						target.currentWay[i] = forRefill[0];
						forRefill.erase(forRefill.begin());
					}
				}
			}
		}
		
	}

}

