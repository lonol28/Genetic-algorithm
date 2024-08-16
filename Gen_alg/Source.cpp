#include "Engine_bool.h"
#include "Engine_double.h"
#include "Engine_int.h"
#include <chrono>

//при 10 парам, 50 популяции и 500 поколений без инлайн
//2.9
//2.745 с inline
//0.8 с inline release
//0.8 без инлайн релиз

void startGenetic()
{
	using std::chrono::steady_clock;
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	auto start1{ steady_clock::now() }; // Получаем текущее время

	engine_DOUBLE geneticEngine;

	geneticEngine.setCountParams(10);
	geneticEngine.setCountPopulation(50);
	geneticEngine.setMaxCountGenerations(500);
	geneticEngine.setFindMaxOrMin(false);//true - find max; false - find min
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

	auto end1{ steady_clock::now() }; // Получаем текущее время

	// Вычисляем и отображаем длительность сортировки в миллисекундах
	auto time1{ duration_cast<milliseconds>(end1 - start1) };
	std::cout << "Time: " << (time1.count() / 1000.0) << " seconds\n";
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