#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class individual
{
private:
	vector<T> leftLimits;
	vector<T> rightLimits;
	vector<T> values;
	double fitness;

public:
	individual();
	individual(vector<T> leftLimitIncome, vector<T> rightLimitIncome);
	individual(vector<T> leftLimitIncome, vector<T> rightLimitIncome, vector<T> valueIncome);
	individual(vector<T> leftLimitIncome, vector<T> rightLimitIncome, vector<T> valueIncome, double fitnessIncome);

	vector<T>& getLeftLimit();
	vector<T>& getRightLimit();
	vector<T>& getValue();
	double& getFitness();

	void changeValue(vector<T> valueIncome);
	void changeValue();
	void calculateFitness();
};

//
// Methods
//

template<class T>
individual<T>::individual() :
	leftLimits{ NULL },
	rightLimits{ NULL },
	values{ NULL },
	fitness{ NULL }
{}

template<class T>
individual<T>::individual(vector<T> leftLimitIncome, vector<T> rightLimitIncome) :
	leftLimits{ leftLimitIncome },
	rightLimits{ rightLimitIncome }
{
	values.resize(leftLimitIncome.size());
	for (int i = 0; i < values.size(); ++i)
	{
		values.at(i) = randomVal(leftLimits.at(i), rightLimits.at(i));
	}

	calculateFitness();
}

template<class T>
individual<T>::individual(vector<T> leftLimitIncome, vector<T> rightLimitIncome, vector<T> valueIncome) :
	leftLimits{ leftLimitIncome },
	rightLimits{ rightLimitIncome },
	values{ valueIncome }
{
	calculateFitness();
}

template<class T>
individual<T>::individual(vector<T> leftLimitIncome, vector<T> rightLimitIncome, vector<T> valueIncome, double fitnessIncome) :
	leftLimits{ leftLimitIncome },
	rightLimits{ rightLimitIncome },
	values{ valueIncome },
	fitness{ fitnessIncome }
{}

template<class T>
vector<T>& individual<T>::getLeftLimit()
{
	return leftLimits;
}

template<class T>
vector<T>& individual<T>::getRightLimit()
{
	return rightLimits;
}

template<class T>
vector<T>& individual<T>::getValue()
{
	return values;
}

template<class T>
double& individual<T>::getFitness()
{
	return fitness;
}

template<class T>
void individual<T>::changeValue(vector<T> valueIncome)
{
	values = valueIncome;
}
template<class T>
void individual<T>::changeValue()
{
	for (int i = 0; i < leftLimits.size(); ++i)
	{
		values.at(i) = randomVal(leftLimits.at(i), rightLimits.at(i));
	}
}

template<class T>
void individual<T>::calculateFitness()
{
	static constexpr int A = 10;
	static constexpr double Pi_value = 3.1415926535898;
	fitness = A * static_cast<int> (values.size());
	for (const T& value : values)
		fitness += pow(value, 2) - A * cos(2 * Pi_value * value);
}

template<class T>
int countMaxIdenticalIndividuums(vector<individual<T>>& individuals)
{
	int countIdentical{ 0 };
	for (int identicalIndivids{ 0 }; auto& individOuter : individuals)
	{
		vector<T>& valuesIndividOuter{ individOuter.getValue() };
		for (identicalIndivids = 0; auto& individInner : individuals)
		{
			if ((valuesIndividOuter == individInner.getValue()) && &individOuter != &individInner)
				++identicalIndivids;
		}

		if (countIdentical < identicalIndivids)
			countIdentical = identicalIndivids;
	}

	return countIdentical;
}

template<class T>
double bestFitnes(vector<individual<T>>& individuals, bool findMax)
{
	double bestResult = individuals.at(0).getFitness();

	for (auto& individ : individuals)
		if (const T& fitnessOfIndivid{ static_cast<T>(individ.getFitness()) }; 
			findMax ? fitnessOfIndivid > bestResult : fitnessOfIndivid < bestResult)
			bestResult = fitnessOfIndivid;

	return bestResult;
}

template<class T>
int numberBestFitness(vector<individual<T>>& individuals, bool findMax)
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