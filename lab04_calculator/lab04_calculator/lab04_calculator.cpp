// lab04_calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

bool CalcNumber(unsigned maxNumber, unsigned number)
{
	if (number % 2 == 0)
	{
		std::cout << "True" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}
	return true;
}

int main()
{
	unsigned maxNum;
	unsigned number;
	std::cin >> maxNum;
	std::cin >> number;
	CalcNumber(maxNum, number);
    return 0;
}