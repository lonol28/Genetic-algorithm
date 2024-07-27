#pragma once
#include <iostream>
#include <vector>

using namespace std;

class genetic_data
{
private:
	int countParams{ 4 }; //Количество параметров индивидума
	int count_population{ 20 }; //Количество индивидумов в поколении
	int maxGenerations{ 50 }; //Количество поколений [1:бесконечность]
	int countGenerations{ 0 }; //Счетчик поколения
	const double chanceOfCrossover{ 0.8 }; //базовая вероятность скрещивания [0.0:1.0]
	const double chanceOfMutation{ 0.15 }; //базовая вероятность мутации индивидуума [0.0:1.0]

public:
	genetic_data();
	genetic_data(int countParams, int count_population);
	genetic_data(double chance1, double chance2, int maxgens);
	genetic_data(int maxgens);

	int getCountParams();
	void setCountParams(int numberCountParams);
	void setCountPopulation(int numberCountPopulation);
	void setMaxCountGenerations(int newCountForPopulations);
	double getChanceOfCrossover();
	double getChanceOfMutation();
	int getCountPopulation();
	int getMaxGenerations();
	int getCountGeneration();
	void plusCountGenerations();
};

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