#include "Engine_bool.h"
#include "Engine_double.h"
#include "Engine_int.h"
#include <chrono>

//��� 10 �����, 50 ��������� � 500 ��������� ��� ������
//2.9
//2.745 � inline
//0.8 � inline release
//0.8 ��� ������ �����

void startGenetic()
{
	using std::chrono::steady_clock;
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	auto start1{ steady_clock::now() }; // �������� ������� �����

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

	auto end1{ steady_clock::now() }; // �������� ������� �����

	// ��������� � ���������� ������������ ���������� � �������������
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