#pragma once
#include <vector>

using namespace std;

int randomInt(int left, int right);
double randomDouble(double left, double right);

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

class individual
{
private:
	vector<double> leftLimits;
	vector<double> rightLimits;
	vector<double> values;
	double fitness;

public:
	individual();
	individual(vector<double> leftLimitIncome, vector<double> rightLimitIncome);
	individual(vector<double> leftLimitIncome, vector<double> rightLimitIncome, vector<double> valueIncome);
	individual(vector<double> leftLimitIncome, vector<double> rightLimitIncome, vector<double> valueIncome, double fitnessIncome);

	vector<double>& getLeftLimit();
	vector<double>& getRightLimit();
	vector<double>& getValue();
	double& getFitness();

	void changeValue(vector<double> valueIncome);
	void changeValue();
	void calculateFitness();
};

int countMaxIdenticalIndividuums(vector<individual>& individuals);
double bestFitnes(vector<individual>& individuals, bool findMax);
int numberBestFitness(vector<individual>& individuals, bool findMax);

class engine : public genetic_data
{
private:
	bool findMax{ true };
	vector<individual> vectorIndividuals;
	individual champion;

public:
	void setFindMaxOrMin(bool income);
	void setPopulation(); //Создание рандом популяции в зависимости от выставленных настроек
	void championChek(); //Сохраняет и закидывает в новое поколение гарантировано 1 лучшего
	//vector<individual>& getVectorPopulation(); //Предоставляет прямой доступ к вектору индивидумов

	void calculationFitnessAll();
	//1-й этап: отбор
	void tournament(int k = 3); //X random => 1 winner

	//2-ой этап: скрещивание
	void crossingCut(); //
	void crossingSwap(); //Скрещивание путем обмена каких либо параметров между двух индивидумов
	void crossingBlend(); //Blend crossover - BLX | скрещивания смешением
	void crossingBlendExperimental();

	//3-ий этап: мутация
	void mutationSpecial(); 
	void mutationNewRandomNumberForOneParam(); //Новое рандом значение для одного параметра
	void mutationNewRandomNumberForRandomParams(); //Новое рандом значение для рандомных параметров
};