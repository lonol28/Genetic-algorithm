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
	const int countParams = getCountParams();
	vector<double> leftLimit(countParams, -5.12);
	vector<double> rightLimit(countParams, 5.12);

	for (int i = 0; i < getCountPopulation(); ++i)
		vectorIndividuals.push_back(individual<double>(leftLimit, rightLimit));
}

void engine_DOUBLE::crossingBlend()
{
	static const double chanceCrossover{ getChanceOfCrossover() };
	static const int sizeReal{ getCountPopulation() };
	static const double procent{ 0.5 };
	static const double chanceForOneParam{ 0.5 };

	size_t i;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= chanceCrossover)
			continue;

		for (size_t j = 0; j < vectorIndividuals.at(i).getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) >= chanceForOneParam)
				continue;

			double leftValue{ vectorIndividuals.at(i).getValue().at(j) };
			double rightValue{ vectorIndividuals.at(i+1).getValue().at(j) };
			if (rightValue < leftValue)
				swap(leftValue, rightValue);

			const double plusMinus = procent * getDelta(leftValue, rightValue);

			const double leftLimit = vectorIndividuals.at(i).getLeftLimit().at(j);
			const double rightLimit = vectorIndividuals.at(i+1).getRightLimit().at(j);

			const double left{ leftValue - plusMinus > leftLimit ? leftValue - plusMinus : leftLimit };
			const double right{ rightValue + plusMinus < rightLimit ? rightValue + plusMinus : rightLimit };

			vectorIndividuals.at(i).getValue().at(j) = randomVal(left, right);
			vectorIndividuals.at(i+1).getValue().at(j) = randomVal(left, right);
		}
	}
}

void engine_DOUBLE::crossingBlendExperimental()
{
	static const double chanceCrossover{ getChanceOfCrossover() };
	static const int sizeReal = getCountPopulation();
	static const double chanceForOneParam{ 0.5 };

	double chanceForProcentage = (static_cast<double>(getCountGeneration())) / getMaxGenerations();
	if (chanceForProcentage <= 0.2)
		chanceForProcentage = 0.2;
	else if (chanceForProcentage >= 0.8)
		chanceForProcentage = 0.8;
	const double procent = (15.0 * (1 - chanceForProcentage)) / 100;

	size_t i;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= chanceCrossover)
			continue;

		for (size_t j = 0; j < vectorIndividuals.at(i).getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) >= chanceForOneParam)
				continue;

			const double leftLimit{ vectorIndividuals.at(i).getLeftLimit().at(j) };
			const double rightLimit{ vectorIndividuals.at(i+1).getRightLimit().at(j) };
			const double plusMinus{ getDelta(leftLimit, rightLimit) * procent };
			double leftValue{ vectorIndividuals.at(i).getValue().at(j) };
			double rightValue{ vectorIndividuals.at(i+1).getValue().at(j) };

			if (rightValue < leftValue)
				swap(leftValue, rightValue);

			const double left{ leftValue - plusMinus > leftLimit ? leftValue - plusMinus : leftLimit };
			const double right{ rightValue + plusMinus < rightLimit ? rightValue + plusMinus : rightLimit };

			vectorIndividuals.at(i).getValue().at(j) = randomVal(left, right);
			vectorIndividuals.at(i+1).getValue().at(j) = randomVal(left, right);
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

	const double procent = (25.0 * (1 - chanceForProcentage)) / 100;

	static const double chanceForOneParameter{ 0.50 };

	for (size_t i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > chanceGlobal)
			continue;

		const bool random{ (randomVal(0.0, 1.0) <= chanceForProcentage) ? false : true };

		for (size_t j = 0; j < vectorIndividuals.at(i).getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) > chanceForOneParameter)
				continue;

			const double leftLimit{ vectorIndividuals.at(i).getLeftLimit().at(j) };
			const double rightLimit{ vectorIndividuals.at(i).getRightLimit().at(j) };

			if (random)
				vectorIndividuals.at(i).getValue().at(j) = randomVal(leftLimit, rightLimit);
			else
			{
				const double value{ vectorIndividuals.at(i).getValue().at(j) };
				const double plusMinus{ getDelta(leftLimit, rightLimit) * procent };
				const double left{ value - plusMinus > leftLimit ? value - plusMinus : leftLimit };
				const double right{ value + plusMinus < rightLimit ? value + plusMinus : rightLimit };

				vectorIndividuals.at(i).getValue().at(j) = randomVal(left, right);
			}
		}
	}
}