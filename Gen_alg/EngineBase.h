#pragma once
#include "Other.h"
#include "Individual.h"
#include "GeneticData.h"

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

	// Tournament selection
	void tournament(int k = 3);

	// Crossing
	void crossingCut();
	void crossingSwap();

	// Mutation
	void mutationNewRandomNumberForOneParam();
	void mutationNewRandomNumberForRandomParams();
	virtual void mutationSpecial() = 0;
};

//
// Methods
//

template<class T>
void engine<T>::calculationFitnessAll()
{
	double middle_res{ 0 };
	double best_res{ vectorIndividuals.at(0).getFitness() };
	for (auto& individ : vectorIndividuals)
	{
		individ.calculateFitness();
		T fitnessIndivid{ individ.getFitness() };
		middle_res += fitnessIndivid;

		if (findMax ? fitnessIndivid > best_res : fitnessIndivid < best_res)
			best_res = fitnessIndivid;
	}
	middle_res /= vectorIndividuals.size();

	cout << "=== " << getCountGeneration() << " generation ===" << endl;
	cout << "best fitness: " << best_res << endl;
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
		cout << "\nBest result is: " << champion.getFitness() << endl;
}

template<class T>
void engine<T>::tournament(int k)
{
	static const int sizeReal{ getCountPopulation() };
	vector<individual<T>> localPopulation;

	int sizeLocal{ 0 };
	while (sizeLocal < sizeReal)
	{
		vector<int> nums;
		for (int i = 0; i < k; ++i)
			nums.push_back(randomVal(0, sizeReal - 1));

		for (int i = 0; i < k - 1; ++i)
			for (int j = i + 1; j < k; ++j)
			{
				if (nums.at(i) == nums.at(j))
				{
					nums.at(i) = randomVal(0, sizeReal - 1);
					i = -1;
					break;
				}
			}

		int numberChampion = nums.at(0);
		for (int& number : nums)
		{
			const T& fitnessCandidate{ vectorIndividuals.at(number).getFitness() };
			const T& fitnessFromGlobalChampion{ vectorIndividuals.at(numberChampion).getFitness() };
			if (findMax)
			{
				if (fitnessCandidate > fitnessFromGlobalChampion)
					numberChampion = number;
			}
			else
			{
				if (fitnessCandidate < fitnessFromGlobalChampion)
					numberChampion = number;
			}
		}
		localPopulation.push_back(vectorIndividuals.at(numberChampion));
		++sizeLocal;
	}
	vectorIndividuals = localPopulation;
}

template<class T>
void engine<T>::crossingCut()
{
	static const int sizeReal = getCountPopulation();
	int i;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= getChanceOfCrossover())
			continue;

		int cutNum{ randomVal(1, getCountParams()) };

		for (int j = cutNum; j < getCountParams(); ++j)
			swap(vectorIndividuals.at(i).getValue()[j], vectorIndividuals[i + 1].getValue()[j]);
	}
}

template<class T>
void engine<T>::crossingSwap()
{
	static const int sizeReal = getCountPopulation();
	int i;
	for (sizeReal % 2 == 0 ? i = 0 : i = 1; i < sizeReal; i = i + 2)
	{
		if (randomVal(0.0, 1.0) >= getChanceOfCrossover())
			continue;

		for (int j = 0; j < vectorIndividuals.at(i).getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) >= 0.5)
				continue;

			swap(vectorIndividuals.at(i).getValue().at(j), vectorIndividuals[i + 1].getValue().at(j));
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
		vectorIndividuals.at(i).getValue().at(local_rand_num) = randomVal(vectorIndividuals.at(i).getLeftLimit().at(local_rand_num), vectorIndividuals.at(i).getRightLimit().at(local_rand_num));
	}
}

template<class T>
void engine<T>::mutationNewRandomNumberForRandomParams()
{
	static const double chanceForOneParam = 0.5;
	for (int i = 0; i < getCountPopulation(); i++)
	{
		if (randomVal(0.0, 1.0) > getChanceOfMutation())
			continue;

		for (int j = 0; j < vectorIndividuals.at(i).getValue().size(); ++j)
		{
			if (randomVal(0.0, 1.0) > chanceForOneParam)
				continue;
			vectorIndividuals.at(i).getValue().at(j) = randomVal(vectorIndividuals.at(i).getLeftLimit().at(j), vectorIndividuals.at(i).getRightLimit().at(j));
		}
	}
}