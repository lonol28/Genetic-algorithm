#pragma once
#include "EngineBase.h"

class engine_BOOL : public engine<int>
{
public:
	void setPopulation();
};

void engine_BOOL::setPopulation()
{
	int countParams = getCountParams();
	vector<int> leftLimit(countParams, 0);
	vector<int> rightLimit(countParams, 1);

	for (int i = 0; i < getCountPopulation(); ++i)
		vectorIndividuals.push_back(individual<int>(leftLimit, rightLimit));
}