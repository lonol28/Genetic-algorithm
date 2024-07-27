#include "Engine_bool.h"
#include "Engine_double.h"
#include "Engine_int.h"

void startGenetic()
{
	engine_INT geneticEngine;

	geneticEngine.setCountParams(10);
	geneticEngine.setCountPopulation(20);
	geneticEngine.setMaxCountGenerations(100);
	geneticEngine.setFindMaxOrMin(false);//true - find max; false - find min
	geneticEngine.setPopulation();

	for (int start = geneticEngine.getCountGeneration(), end = geneticEngine.getMaxGenerations(); 
		start < end; ++start, geneticEngine.plusCountGenerations())
	{
		geneticEngine.tournament();
		geneticEngine.crossingSwap();
		geneticEngine.mutationSpecial();

		geneticEngine.calculationFitnessAll();
		geneticEngine.championChek();
	}
}

void test()
{
	cout << "Int " << sizeof(int) << endl;
	cout << "Double " << sizeof(double) << endl;
	cout << "Char " << sizeof(char) << endl;
	cout << "String " << sizeof(string) << endl;
	cout << "Long int " << sizeof(long int) << endl;
	cout << "Long long int " << sizeof(long long int) << endl;
	cout << "Long double " << sizeof(long double) << endl;
}

int main()
{
	//test();
	startGenetic();
}