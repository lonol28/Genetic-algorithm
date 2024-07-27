#pragma once
#include "EngineBase.h"

class engine_BOOL : public engine<int>
{
public:
	void setPopulation();

	// Mutation
	void mutationSpecial();
};

//
// Methods
//

void engine_BOOL::setPopulation()
{
	int countParams = getCountParams();
	vector<int> leftLimit(countParams, 0);
	vector<int> rightLimit(countParams, 1);

	for (int i = 0; i < getCountPopulation(); ++i)
		vectorIndividuals.push_back(individual<int>(leftLimit, rightLimit));
}

inline void engine_BOOL::mutationSpecial()
{
	double chanceGlobal{ 1 - 3.0 / countMaxIdenticalIndividuums(vectorIndividuals) };
	if (chanceGlobal <= 0.0)
		chanceGlobal = getChanceOfMutation();

	double chanceForOneParam = (static_cast<double>(getCountGeneration())) / getMaxGenerations();
	if (chanceForOneParam <= 0.2)
		chanceForOneParam = 0.2;
	else if (chanceForOneParam >= 0.9)
		chanceForOneParam = 0.9;

	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > chanceGlobal)
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) < chanceForOneParam)
				continue;

			if (vectorIndividuals[i].getValue().at(j) == 0)
				vectorIndividuals[i].getValue().at(j) = 1;
			else
				vectorIndividuals[i].getValue().at(j) = 0;
		}
	}
}
