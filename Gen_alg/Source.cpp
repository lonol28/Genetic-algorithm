#include "Header.h"
#include <iostream>

void startGenetic()
{
	engine geneticEngine;

	geneticEngine.setCountParams(10);
	geneticEngine.setCountPopulation(20);
	geneticEngine.setMaxCountGenerations(100);
	geneticEngine.setPopulation();

	for (int i = 0; i < geneticEngine.getMaxGenerations(); ++i)
	{
		geneticEngine.tournament();
		geneticEngine.crossingBlend();
		geneticEngine.mutationNewRandomNumberForOneParam();

		geneticEngine.calculationFitnessAll();
		geneticEngine.championChek();
		geneticEngine.plusCountGenerations();
	}
}

int main()
{
	startGenetic();
}