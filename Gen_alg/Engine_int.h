#pragma once
#include "EngineBase.h"

class engine_INT : public engine<int>
{
public:
	void setPopulation();
};

//
// Methods
//

void engine_INT::setPopulation()
{
	int countParams = getCountParams();
	vector<int> leftLimit(countParams, -5);
	vector<int> rightLimit(countParams, 5);

	for (int i = 0; i < getCountPopulation(); ++i)
		vectorIndividuals.push_back(individual<int>(leftLimit, rightLimit));
}