#pragma once
#include <vector>

using namespace std;

int randomInt(int left, int right);
double randomDouble(double left, double right);

class genetic_data
{
private:
	int countParams{ 4 }; //���������� ���������� ����������
	int count_population{ 20 }; //���������� ����������� � ���������
	int maxGenerations{ 50 }; //���������� ��������� [1:�������������]
	int countGenerations{ 0 }; //������� ���������
	const double chanceOfCrossover{ 0.8 }; //������� ����������� ����������� [0.0:1.0]
	const double chanceOfMutation{ 0.15 }; //������� ����������� ������� ����������� [0.0:1.0]

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
	void setPopulation(); //�������� ������ ��������� � ����������� �� ������������ ��������
	void championChek(); //��������� � ���������� � ����� ��������� ������������� 1 �������
	//vector<individual>& getVectorPopulation(); //������������� ������ ������ � ������� �����������

	void calculationFitnessAll();
	//1-� ����: �����
	void tournament(int k = 3); //X random => 1 winner

	//2-�� ����: �����������
	void crossingCut(); //
	void crossingSwap(); //����������� ����� ������ ����� ���� ���������� ����� ���� �����������
	void crossingBlend(); //Blend crossover - BLX | ����������� ���������
	void crossingBlendExperimental();

	//3-�� ����: �������
	void mutationSpecial(); 
	void mutationNewRandomNumberForOneParam(); //����� ������ �������� ��� ������ ���������
	void mutationNewRandomNumberForRandomParams(); //����� ������ �������� ��� ��������� ����������
};