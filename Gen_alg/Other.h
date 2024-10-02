#pragma once
#include <iostream>
#include <random>

using namespace std;

int randomVal(const int left, const int right)
{
	default_random_engine randomEngine{ random_device{}() };
	if (left < right)
	{
		uniform_int_distribution<int> randomVal{ left, right };
		return randomVal(randomEngine);
	}
	else if (left > right)
	{
		uniform_int_distribution<int> randomVal{ right, left };
		return randomVal(randomEngine);
	}
	else
		return left;
}

double randomVal(const double left, const double right)
{

	default_random_engine randomEngine{ random_device{}() };
	if (left < right)
	{
		uniform_real_distribution<double> randomVal{ left, right };
		return randomVal(randomEngine);
	}
	else if (left > right)
	{
		uniform_real_distribution<double> randomVal{ right, left };
		return randomVal(randomEngine);
	}
	else
		return left;
}

double getDelta(double min, double max)
{
	if (max > min)
		return (max - min);
	else
		return (min - max);
}