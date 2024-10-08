#include "Engine_bool.h"
#include "Engine_double.h"
#include "Engine_int.h"

void startGenetic()
{
	engine_DOUBLE geneticEngine;

	geneticEngine.setCountParams(10);
	geneticEngine.setCountPopulation(20);
	geneticEngine.setMaxCountGenerations(100);
	geneticEngine.setFindMaxOrMin(false);//true - find max; false - find min
	geneticEngine.setPopulation();

	for (size_t start = geneticEngine.getCountGeneration(), end = geneticEngine.getMaxGenerations(); 
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