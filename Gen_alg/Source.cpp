#include "Header.h"
#include <iostream>

void startGenetic()
{
	engine geneticEngine;

	geneticEngine.setCountParams(10);
	geneticEngine.setCountPopulation(20);
	geneticEngine.setMaxCountGenerations(100);
	geneticEngine.setPopulation();

	for (int start = geneticEngine.getCountGeneration(), end = geneticEngine.getMaxGenerations(); 
		start < end; ++start, geneticEngine.plusCountGenerations())
	{
		geneticEngine.tournament();
		geneticEngine.crossingBlend();
		geneticEngine.mutationNewRandomNumberForOneParam();

		geneticEngine.calculationFitnessAll();
		geneticEngine.championChek();
	}
}

int main()
{
	startGenetic();
}