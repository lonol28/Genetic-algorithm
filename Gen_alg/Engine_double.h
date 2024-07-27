#pragma once
#include "EngineBase.h"

class engine_DOUBLE : public engine<double>
{
public:
	void setPopulation();

	// Crossing
	void crossingBlend();
	void crossingBlendExperimental();

	// Mutation
	void mutationSpecial();
};

//
// Methods
//

void engine_DOUBLE::setPopulation()
{
	int countParams = getCountParams();
	vector<double> leftLimit(countParams, -5.12);
	vector<double> rightLimit(countParams, 5.12);

	for (int i = 0; i < getCountPopulation(); ++i)
		vectorIndividuals.push_back(individual<double>(leftLimit, rightLimit));
}

void engine_DOUBLE::crossingBlend()
{
	int sizeReal = getCountPopulation();
	int i;
	double procent = 0.5;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= getChanceOfCrossover())
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) >= 0.50)
				continue;

			double leftValue{ vectorIndividuals[i].getValue().at(j) };
			double rightValue{ vectorIndividuals[i + 1].getValue().at(j) };
			if (rightValue < leftValue)
				swap(leftValue, rightValue);

			double plusMinus = procent * getDelta(leftValue, rightValue);

			double leftLimit = vectorIndividuals[i].getLeftLimit()[j];
			double rightLimit = vectorIndividuals[i + 1].getRightLimit()[j];

			double left{ leftValue - plusMinus > leftLimit ? leftValue - plusMinus : leftLimit };
			double right{ rightValue + plusMinus < rightLimit ? rightValue + plusMinus : rightLimit };

			vectorIndividuals[i].getValue().at(j) = randomVal(left, right);
			vectorIndividuals[i + 1].getValue().at(j) = randomVal(left, right);
		}
	}
}

void engine_DOUBLE::crossingBlendExperimental()
{
	int sizeReal = getCountPopulation();

	double chanceForProcentage = (static_cast<double>(getCountGeneration())) / getMaxGenerations();
	if (chanceForProcentage <= 0.2)
		chanceForProcentage = 0.2;
	else if (chanceForProcentage >= 0.8)
		chanceForProcentage = 0.8;
	double procent = (15.0 * (1 - chanceForProcentage)) / 100;

	int i;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= getChanceOfCrossover())
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) >= 0.50)
				continue;

			double leftLimit{ vectorIndividuals[i].getLeftLimit().at(j) };
			double rightLimit{ vectorIndividuals[i + 1].getRightLimit().at(j) };
			double plusMinus{ getDelta(leftLimit, rightLimit) * procent };
			double leftValue{ vectorIndividuals[i].getValue().at(j) };
			double rightValue{ vectorIndividuals[i + 1].getValue().at(j) };

			if (rightValue < leftValue)
				swap(leftValue, rightValue);

			double left{ leftValue - plusMinus > leftLimit ? leftValue - plusMinus : leftLimit };
			double right{ rightValue + plusMinus < rightLimit ? rightValue + plusMinus : rightLimit };

			vectorIndividuals[i].getValue().at(j) = randomVal(left, right);
			vectorIndividuals[i + 1].getValue().at(j) = randomVal(left, right);
		}
	}
}

void engine_DOUBLE::mutationSpecial()
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

	double chanceForOneParameter{ 0.50 };

	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > chanceGlobal)
			continue;

		bool random{ (randomVal(0.0, 1.0) <= chanceForProcentage) ? false : true };

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) > chanceForOneParameter)
				continue;

			double leftLimit{ vectorIndividuals[i].getLeftLimit().at(j) };
			double rightLimit{ vectorIndividuals[i].getRightLimit().at(j) };

			if (random)
				vectorIndividuals[i].getValue().at(j) = randomVal(leftLimit, rightLimit);
			else
			{
				double value{ vectorIndividuals[i].getValue().at(j) };
				double plusMinus{ getDelta(leftLimit, rightLimit) * procent };
				double left{ value - plusMinus > leftLimit ? value - plusMinus : leftLimit };
				double right{ value + plusMinus < rightLimit ? value + plusMinus : rightLimit };

				vectorIndividuals[i].getValue().at(j) = randomVal(left, right);
			}
		}
	}
}