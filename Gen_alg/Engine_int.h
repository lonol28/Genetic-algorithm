#pragma once
#include "EngineBase.h"

class engine_INT : public engine<int>
{
public:
	void setPopulation();

	// Mutation
	void mutationSpecial();
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

void engine_INT::mutationSpecial()
{
	double chanceGlobal{ 1 - 3.0 / countMaxIdenticalIndividuums(vectorIndividuals) };
	if (chanceGlobal <= 0.0)
		chanceGlobal = getChanceOfMutation();

	double chanceForProcentage = (static_cast<double>(getCountGeneration())) / getMaxGenerations();
	if (chanceForProcentage <= 0.2)
		chanceForProcentage = 0.2;
	else if (chanceForProcentage >= 0.8)
		chanceForProcentage = 0.8;

	double procent = (25.0 * (1 - chanceForProcentage)) / 100;

	static const double chanceForOneParameter{ 0.50 };

	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > chanceGlobal)
			continue;

		bool random{ (randomVal(0.0, 1.0) <= chanceForProcentage) ? false : true };

		for (int j = 0; j < vectorIndividuals.at(i).getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) > chanceForOneParameter)
				continue;

			int leftLimit{ vectorIndividuals.at(i).getLeftLimit().at(j) };
			int rightLimit{ vectorIndividuals.at(i).getRightLimit().at(j) };

			if (random)
				vectorIndividuals.at(i).getValue().at(j) = randomVal(leftLimit, rightLimit);
			else
			{
				int value{ vectorIndividuals.at(i).getValue().at(j) };
				int plusMinus{ static_cast<int>(getDelta(leftLimit, rightLimit) * procent )};
				int left{ value - plusMinus > leftLimit ? value - plusMinus : leftLimit };
				int right{ value + plusMinus < rightLimit ? value + plusMinus : rightLimit };

				vectorIndividuals.at(i).getValue().at(j) = randomVal(left, right);
			}
		}
	}
}