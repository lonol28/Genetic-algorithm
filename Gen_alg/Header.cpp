#include "Header.h"
#include <random>
#include <iostream>

int randomInt(const int left, const int right)
{
	default_random_engine randomEngine{ random_device{}() };
	if (left < right)
	{
		uniform_int_distribution<int> randomInt{ left, right };
		return randomInt(randomEngine);
	}
	else if (left > right)
	{
		uniform_int_distribution<int> randomInt{ right, left };
		return randomInt(randomEngine);
	}
	else
		return left;
}

double randomDouble(const double left, const double right)
{

	default_random_engine randomEngine{ random_device{}() };
	if (left < right)
	{
		uniform_real_distribution<double> randomDouble{ left, right };
		return randomDouble(randomEngine);
	}
	else if (left > right)
	{
		uniform_real_distribution<double> randomDouble{ right, left };
		return randomDouble(randomEngine);
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
		values[i] = randomDouble(leftLimits[i], rightLimits[i]);
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
		values[i] = randomInt(leftLimits[i], rightLimits[i]);
	}
}

void individual::calculateFitness()
{
	fitness = 0;
	for (int i = 0; i < values.size(); i++)
		fitness += values[i];
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
	vector<double> leftLimit(countParams, -10.0);
	vector<double> rightLimit(countParams, 10.0);

	for (int i = 0; i < getCountPopulation(); ++i)
		vectorIndividuals.push_back(individual(leftLimit, rightLimit));
}

void engine::championChek()
{
	if (findMax ? 
		getCountGeneration() == 0 || bestFitnes(vectorIndividuals, findMax) > champion.getFitness() :
		getCountGeneration() == 0 || bestFitnes(vectorIndividuals, findMax) < champion.getFitness())
		champion = vectorIndividuals.at(numberBestFitness(vectorIndividuals, findMax));
	else
		vectorIndividuals.at(randomInt(0, getCountPopulation() - 1)) = champion;
	
	if (getCountGeneration() == getMaxGenerations() - 1)
		cout << "\Best result is: " << champion.getFitness() << endl;
}

/*
vector<individual>& engine::getVectorPopulation()
{
	return vectorIndividuals;
}
*/

void engine::tournament()
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

		int k = 3;
		vector<int> nums;
		for (int i = 0; i < k; ++i)
			nums.push_back(randomInt(0, sizeReal - 1));

		for (int i = 0; i < k - 1; ++i)
			for (int j = i + 1; j < k; ++j)
			{
				if (nums[i] == nums[j])
				{
					nums[i] = randomInt(0, sizeReal - 1);
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
		if (randomDouble(0, 1) >= getChanceOfCrossover())
			continue;

		int cutNum{ randomInt(1, getCountParams()) };

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
		if (randomDouble(0, 1) >= getChanceOfCrossover())
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomDouble(0, 1) >= 0.5)
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
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomDouble(0, 1) >= getChanceOfCrossover())
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomDouble(0, 1) >= 0.50)
				continue;

			double leftLimit{ vectorIndividuals[i].getLeftLimit().at(j) };
			double rightLimit{ vectorIndividuals[i].getRightLimit().at(j) };
			
			double chanceForProcentage = (static_cast<double>(getCountGeneration())) / getMaxGenerations();
			if (chanceForProcentage <= 0.2)
				chanceForProcentage = 0.2;
			else if (chanceForProcentage >= 0.8)
				chanceForProcentage = 0.8;

			double procent = (20.0 * (1 - chanceForProcentage)) / 100;
			
			//procent = 0.1;		

			double plusMinus{ getDelta(leftLimit, rightLimit) * procent };

			double leftValue{ vectorIndividuals[i].getValue().at(j) };
			double rightValue{ vectorIndividuals[i+1].getValue().at(j) };
			if (leftValue < rightValue)
			{
				double left{ leftValue - plusMinus > leftLimit ? leftValue - plusMinus : leftLimit };
				double right{ rightValue + plusMinus < rightLimit ? rightValue + plusMinus : rightLimit };

				vectorIndividuals[i].getValue().at(j) = randomDouble(left, right);
				vectorIndividuals[i+1].getValue().at(j) = randomDouble(left, right);
			}
			else
			{
				double left{ rightValue - plusMinus > leftLimit ? rightValue - plusMinus : leftLimit };
				double right{ leftValue + plusMinus < rightLimit ? leftValue + plusMinus : rightLimit };

				vectorIndividuals[i].getValue().at(j) = randomDouble(left, right);
				vectorIndividuals[i + 1].getValue().at(j) = randomDouble(left, right);
			}
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
		if (randomDouble(0, 1) > chanceGlobal)
			continue;

		bool random{ (randomDouble(0, 1) <= chanceForProcentage) ? false : true };

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomDouble(0, 1) > chanceForOneParameter)
				continue;

			double leftLimit{ vectorIndividuals[i].getLeftLimit().at(j) };
			double rightLimit{ vectorIndividuals[i].getRightLimit().at(j) };

			if (random)
				vectorIndividuals[i].getValue().at(j) = randomDouble(leftLimit, rightLimit);
			else
			{
				double value{ vectorIndividuals[i].getValue().at(j) };
				double plusMinus{ getDelta(leftLimit, rightLimit) * procent };
				double left{ value - plusMinus > leftLimit ? value - plusMinus : leftLimit };
				double right{ value + plusMinus < rightLimit ? value + plusMinus : rightLimit };

				vectorIndividuals[i].getValue().at(j) = randomDouble(left, right);
			}
		}
	}
}

void engine::mutationNewRandomNumberForOneParam()
{
	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomDouble(0, 1) > getChanceOfMutation())
			continue;

		int local_rand_num = randomInt(0, getCountParams() - 1);
		vectorIndividuals[i].getValue().at(local_rand_num) = randomDouble(vectorIndividuals[i].getLeftLimit().at(local_rand_num), vectorIndividuals[i].getRightLimit().at(local_rand_num));
	}
}

void engine::mutationNewRandomNumberForRandomParams()
{
	double chanceForOneParam = 0.5;
	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomDouble(0, 1) > getChanceOfMutation())
			continue;

		for (int j = 0; j < vectorIndividuals[i].getValue().size(); ++j)
		{
			if (randomDouble(0, 1) > chanceForOneParam)
				continue;
			vectorIndividuals[i].getValue().at(j) = randomDouble(vectorIndividuals[i].getLeftLimit().at(j), vectorIndividuals[i].getRightLimit().at(j));
		}
	}
}