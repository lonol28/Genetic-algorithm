#pragma once
#include "Other.h"
#include "Individual.h"
#include "GeneticData.h"

//
// engine
//

template<class T>
class engine : public genetic_data
{
protected:
	bool findMax{ true };
	vector<individual<T>> vectorIndividuals;
	individual<T> champion;

public:
	virtual void setPopulation() = 0;
	void calculationFitnessAll();

	void setFindMaxOrMin(bool income);
	void championChek();

	//1-й этап: отбор
	void tournament(int k = 3); //X random => 1 winner

	//2-ой этап: скрещивание
	void crossingCut(); //
	void crossingSwap(); //—крещивание путем обмена каких либо параметров между двух индивидумов

	//3-ий этап: мутаци€
	void mutationNewRandomNumberForOneParam(); //Ќовое рандом значение дл€ одного параметра
	void mutationNewRandomNumberForRandomParams(); //Ќовое рандом значение дл€ рандомных параметров
};

template<class T>
void engine<T>::calculationFitnessAll()
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

template<class T>
void engine<T>::setFindMaxOrMin(bool income)
{
	findMax = income;
}

template<class T>
void engine<T>::championChek()
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

template<class T>
void engine<T>::tournament(int k)
{
	int sizeReal = getCountPopulation();
	vector<individual<T>> localPopulation;
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

		vector<individual<T>> bobrs;
		for (int i = 0; i < k; i++)
			bobrs.push_back(individual<T>(vectorIndividuals[nums[i]].getLeftLimit(), vectorIndividuals[nums[i]].getRightLimit(), vectorIndividuals[nums[i]].getValue(), vectorIndividuals[nums[i]].getFitness()));

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
		localPopulation.push_back(individual<T>(bobrs[numBobr].getLeftLimit(), bobrs[numBobr].getRightLimit(), bobrs[numBobr].getValue(), bobrs[numBobr].getFitness()));
	}
}

template<class T>
void engine<T>::crossingCut()
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

template<class T>
void engine<T>::crossingSwap()
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

template<class T>
void engine<T>::mutationNewRandomNumberForOneParam()
{
	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > getChanceOfMutation())
			continue;

		int local_rand_num = randomVal(0, getCountParams() - 1);
		vectorIndividuals[i].getValue().at(local_rand_num) = randomVal(vectorIndividuals[i].getLeftLimit().at(local_rand_num), vectorIndividuals[i].getRightLimit().at(local_rand_num));
	}
}

template<class T>
void engine<T>::mutationNewRandomNumberForRandomParams()
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