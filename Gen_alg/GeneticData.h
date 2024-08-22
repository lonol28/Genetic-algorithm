#pragma once
#include <iostream>
#include <vector>

using namespace std;

class genetic_data
{
private:
	int countParams{ 4 };
	int count_population{ 20 }; // How many individs in population
	int maxGenerations{ 50 }; // How many populations
	int countGenerations{ 0 }; // Count current population
	const double chanceOfCrossover{ 0.8 };
	const double chanceOfMutation{ 0.15 };

public:
	genetic_data();

	void setCountParams(int numberCountParams);
	int getCountParams();
	void setCountPopulation(int numberCountPopulation);
	int getCountPopulation();
	void setMaxCountGenerations(int newCountForPopulations);
	int getMaxGenerations();
	void plusCountGenerations();
	int getCountGeneration();
	double getChanceOfCrossover();
	double getChanceOfMutation();
};

//
// Methods
//

genetic_data::genetic_data()
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

inline void genetic_data::plusCountGenerations()
{
	++countGenerations;
}