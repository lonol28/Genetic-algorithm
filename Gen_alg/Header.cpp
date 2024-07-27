#include "Header.h"
#include <random>
#include <iostream>
//#include <cmath>

int randomVal(const int left, const int right)
{
	default_random_engine randomEngine{ random_device{}() };
	if (left < right)
	{
		uniform_int_distribution<int> randomVal{ left, right };
		return randomVal(randomEngine);
	}
	else if (left > right)
	{
		uniform_int_distribution<int> randomVal{ right, left };
		return randomVal(randomEngine);
	}
	else
		return left;
}

double randomVal(const double left, const double right)
{

	default_random_engine randomEngine{ random_device{}() };
	if (left < right)
	{
		uniform_real_distribution<double> randomVal{ left, right };
		return randomVal(randomEngine);
	}
	else if (left > right)
	{
		uniform_real_distribution<double> randomVal{ right, left };
		return randomVal(randomEngine);
	}
	else
		return left;
}

int countMaxIdenticalIndividuums(vector<individual>& individuals)
{
	int count{ 0 };
	for (int i = 0; i < individuals.size(); ++i)
	{
		int countLocal = 0;
		for (int j = 0; j < individuals.size(); ++j)
		{
			if ((individuals[i].getValue() == individuals[j].getValue()) && i != j)
				countLocal++;
		}
		if (count < countLocal)
			count = countLocal;
	}
	return count;
}

double bestFitnes(vector<individual>& individuals, bool findMax)
{
	double bestResult = individuals.at(0).getFitness();
	for (int i = 0; i < individuals.size(); i++)
		if (findMax ? individuals.at(i).getFitness() > bestResult : individuals.at(i).getFitness() < bestResult)
			bestResult = individuals.at(i).getFitness();
	return bestResult;
}

int numberBestFitness(vector<individual>& individuals, bool findMax)
{
	double bestResult = individuals.at(0).getFitness();
	int k = 0;
	for (int i = 0; i < individuals.size(); i++)
		if (findMax ? individuals.at(i).getFitness() > bestResult : individuals.at(i).getFitness() < bestResult)
		{
			bestResult = individuals.at(i).getFitness();
			k = i;
		}	
	return k;
}

//
// genetic_data
//

genetic_data::genetic_data()
{}

genetic_data::genetic_data(int countParams, int count_population) :
	countParams{ countParams },
	count_population{ count_population }
{}

genetic_data::genetic_data(double chance1, double chance2, int maxgens) :
	chanceOfCrossover{ chance1 },
	chanceOfMutation{ chance2 },
	maxGenerations{ maxgens }
{}

genetic_data::genetic_data(int maxgens) :
	maxGenerations{ maxgens }
{}

int genetic_data::getCountParams()
{
	return countParams;
}

void genetic_data::setCountParams(int numberCountParams)
{
	countParams = numberCountParams;
}

void genetic_data::setCountPopulation(int numberCountPopulation)
{
	count_population = numberCountPopulation;
}

void genetic_data::setMaxCountGenerations(int newCountForPopulations)
{
	maxGenerations = newCountForPopulations;
}


double genetic_data::getChanceOfCrossover()
{
	return chanceOfCrossover;
}

double genetic_data::getChanceOfMutation()
{
	return chanceOfMutation;
}

int genetic_data::getCountPopulation()
{
	return count_population;
}

int genetic_data::getMaxGenerations()
{
	return maxGenerations;
}

int genetic_data::getCountGeneration()
{
	return countGenerations;
}

void genetic_data::plusCountGenerations()
{
	countGenerations++;
}

//
// individual
//

individual::individual() :
	leftLimits{ NULL },
	rightLimits{ NULL },
	values{ NULL },
	fitness{ NULL }
{}

individual::individual(vector<double> leftLimitIncome, vector<double> rightLimitIncome) :
	leftLimits{ leftLimitIncome },
	rightLimits{ rightLimitIncome }
{
	values.resize(leftLimitIncome.size());
	for (int i = 0; i < leftLimits.size(); ++i)
	{
		values[i] = randomVal(leftLimits[i], rightLimits[i]);
	}
	calculateFitness();
}

individual::individual(vector<double> leftLimitIncome, vector<double> rightLimitIncome, vector<double> valueIncome) :
	leftLimits{ leftLimitIncome },
	rightLimits{ rightLimitIncome },
	values{ valueIncome }
{
	calculateFitness();
}

individual::individual(vector<double> leftLimitIncome, vector<double> rightLimitIncome, vector<double> valueIncome, double fitnessIncome) :
	leftLimits{ leftLimitIncome },
	rightLimits{ rightLimitIncome },
	values{ valueIncome },
	fitness{ fitnessIncome }
{}

vector<double>& individual::getLeftLimit()
{
	return leftLimits;
}

vector<double>& individual::getRightLimit()
{
	return rightLimits;
}

vector<double>& individual::getValue()
{
	return values;
}

double& individual::getFitness()
{
	return fitness;
}

void individual::changeValue(vector<double> valueIncome)
{
	values = valueIncome;
}

void individual::changeValue()
{
	for (int i = 0; i < leftLimits.size(); ++i)
	{
		values[i] = randomVal(leftLimits[i], rightLimits[i]);
	}
}

void individual::calculateFitness()
{
	int A = 10;
	fitness = A * values.size();
	for (int i = 0; i < values.size(); i++)
		fitness += pow(values[i], 2) - A * cos(2 * _Pi_val * values[i]);
}

//
// engine
//

void engine::calculationFitnessAll()
{
	double middle_res = 0;
	for (int i = 0; i < vectorIndividuals.size(); ++i)
	{
		vectorIndividuals[i].calculateFitness();
		middle_res += vectorIndividuals[i].getFitness();
	}
	middle_res /= vectorIndividuals.size();

	double bestRes = vectorIndividuals[0].getFitness();
	for (int i = 0; i < vectorIndividuals.size(); i++)
		if (findMax ? vectorIndividuals[i].getFitness() > bestRes : vectorIndividuals[i].getFitness() < bestRes)
			bestRes = vectorIndividuals[i].getFitness();
	
	cout << "=== " << getCountGeneration() << " generation ===" << endl;
	cout << "best fitness: " << bestRes << endl;
	cout << "avg fitness: " << middle_res << endl << endl;
}

void engine::setFindMaxOrMin(bool income)
{
	findMax = income;
}

void engine::setPopulation()
{
	int countParams = getCountParams();
	vector<double> leftLimit(countParams, -5.12);
	vector<double> rightLimit(countParams, 5.12);

	for (int i = 0; i < getCountPopulation(); ++i)
		vectorIndividuals.push_back(individual(leftLimit, rightLimit));
}

void engine::championChek()
{
	if (findMax ? 
		champion.getFitness() == NULL || bestFitnes(vectorIndividuals, findMax) > champion.getFitness() :
		champion.getFitness() == NULL || bestFitnes(vectorIndividuals, findMax) < champion.getFitness())
		champion = vectorIndividuals.at(numberBestFitness(vectorIndividuals, findMax));
	else
		vectorIndividuals.at(randomVal(0, getCountPopulation() - 1)) = champion;
	
	if (getCountGeneration() == getMaxGenerations() - 1)
		cout << "\Best result is: " << champion.getFitness() << endl;
}

/*
vector<individual>& engine::getVectorPopulation()
{
	return vectorIndividuals;
}
*/

void engine::tournament(int k)
{
	int sizeReal = getCountPopulation();
	vector<individual> localPopulation;
	while (true)
	{
		int sizeLocal = localPopulation.size();
		if (sizeLocal == sizeReal)
		{
			vectorIndividuals = localPopulation;
			break;
		}

		vector<int> nums;
		for (int i = 0; i < k; ++i)
			nums.push_back(randomVal(0, sizeReal - 1));

		for (int i = 0; i < k - 1; ++i)
			for (int j = i + 1; j < k; ++j)
			{
				if (nums[i] == nums[j])
				{
					nums[i] = randomVal(0, sizeReal - 1);
					i = -1;
					break;
				}
			}

		vector<individual> bobrs;
		for (int i = 0; i < k; i++)
			bobrs.push_back(individual(vectorIndividuals[nums[i]].getLeftLimit(), vectorIndividuals[nums[i]].getRightLimit(), vectorIndividuals[nums[i]].getValue(), vectorIndividuals[nums[i]].getFitness()));

		int numBobr = 0;
		for (int i = 0; i < bobrs.size() - 1; ++i)
		{
			for (int j = i + 1; j < bobrs.size(); ++j)
			{
				if (findMax)
				{
					if (bobrs.at(j).getFitness() > bobrs.at(numBobr).getFitness() && bobrs.at(j).getFitness() > bobrs.at(i).getFitness())
						numBobr = j;
				}
				else
				{
					if (bobrs.at(j).getFitness() < bobrs.at(numBobr).getFitness() && bobrs.at(j).getFitness() < bobrs.at(i).getFitness())
						numBobr = j;
				}
			}
		}
		localPopulation.push_back(individual(bobrs[numBobr].getLeftLimit(), bobrs[numBobr].getRightLimit(), bobrs[numBobr].getValue(), bobrs[numBobr].getFitness()));
	}
}

void engine::crossingCut()
{
	int sizeReal = getCountPopulation();
	int i;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= getChanceOfCrossover())
			continue;

		int cutNum{ randomVal(1, getCountParams()) };

		for (int j = cutNum; j < getCountParams(); ++j)
			swap(vectorIndividuals[i].getValue()[j], vectorIndividuals[i + 1].getValue()[j]);
	}
}

void engine::crossingSwap()
{
	int sizeReal = getCountPopulation();
	int i;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= getChanceOfCrossover())
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) >= 0.5)
				continue;

			swap(vectorIndividuals[i].getValue().at(j), vectorIndividuals[i + 1].getValue().at(j));
		}
	}
}

double getDelta(double left, double right)
{
	if (right < left)
		swap(left, right);

	if ((left >= 0.0 && right >= 0.0) || (left < 0 && right >= 0.0))
		return right - left;
	else if (left < 0 && right < 0.0)
		return (abs(right)) - left;	
}

void engine::crossingBlend()
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
			double rightLimit = vectorIndividuals[i+1].getRightLimit()[j];

			double left{ leftValue - plusMinus > leftLimit ? leftValue - plusMinus : leftLimit };
			double right{ rightValue + plusMinus < rightLimit ? rightValue + plusMinus : rightLimit };

			vectorIndividuals[i].getValue().at(j) = randomVal(left, right);
			vectorIndividuals[i + 1].getValue().at(j) = randomVal(left, right);
		}
	}
}

void engine::crossingBlendExperimental()
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
			double rightLimit{ vectorIndividuals[i+1].getRightLimit().at(j) };
			double plusMinus{ getDelta(leftLimit, rightLimit) * procent };
			double leftValue{ vectorIndividuals[i].getValue().at(j) };
			double rightValue{ vectorIndividuals[i+1].getValue().at(j) };

			if (rightValue < leftValue)
				swap(leftValue, rightValue);

			double left{ leftValue - plusMinus > leftLimit ? leftValue - plusMinus : leftLimit };
			double right{ rightValue + plusMinus < rightLimit ? rightValue + plusMinus : rightLimit };

			vectorIndividuals[i].getValue().at(j) = randomVal(left, right);
			vectorIndividuals[i + 1].getValue().at(j) = randomVal(left, right);
		}
	}
}

void engine::mutationSpecial()
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

void engine::mutationNewRandomNumberForOneParam()
{
	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > getChanceOfMutation())
			continue;

		int local_rand_num = randomVal(0, getCountParams() - 1);
		vectorIndividuals[i].getValue().at(local_rand_num) = randomVal(vectorIndividuals[i].getLeftLimit().at(local_rand_num), vectorIndividuals[i].getRightLimit().at(local_rand_num));
	}
}

void engine::mutationNewRandomNumberForRandomParams()
{
	double chanceForOneParam = 0.5;
	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > getChanceOfMutation())
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) > chanceForOneParam)
				continue;
			vectorIndividuals[i].getValue().at(j) = randomVal(vectorIndividuals[i].getLeftLimit().at(j), vectorIndividuals[i].getRightLimit().at(j));
		}
	}
}