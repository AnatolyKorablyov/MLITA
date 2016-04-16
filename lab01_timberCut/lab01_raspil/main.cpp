// Кораблёв Анатолий, ПС-22
// 14.10. Распил бруса 2 (9)
//На пилораму привезли брус длиной L метров.Требуется сделать N распилов.Распилы делят
//
//брус на части, длина которых выражается натуральными числами.Стоимость одного распила
//
//равна длине распиливаемого бруса.Определить минимальную стоимость распила.
//
//Ввод.В первой строке содержатся через пробел натуральные числа L(2 ≤ L ≤ 10^5) и N(N < L) –
//
//	длина бруса и число распилов.
//
//	Вывод.В единственной строке вывести минимальную стоимость распилов.
//
//	Примеры
//
//	Ввод 1         Ввод 2
//
//	100 3          10 4
//
//	Вывод 1        Вывод 2
//
//	105            18

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

static const unsigned MIN_LENGTH = 2;
static const unsigned MAX_LENGTH = 200'000;


struct Timber
{
	unsigned length = 0;
	unsigned numCut = 0;
};

bool isBetween(unsigned value, const std::pair<unsigned, unsigned> & rangeValue)
{
	return (value >= rangeValue.first && value <= rangeValue.second);
}

void PrintErrorSizeValues()
{
	std::cout << "Incorrect length of the value and number of cuts" << std::endl;
	std::cout << "Correct: (2 <= length <= 10^5) and (num of cuts < length)" << std::endl;
}

bool ReadFromFile(Timber & timber, const std::string & nameFile)
{
	std::ifstream inpFile(nameFile);

	if (!inpFile.is_open())
	{
		std::cout << "File not found!" << std::endl;
		return false;
	}
	
	inpFile >> timber.length;
	inpFile >> timber.numCut;

	if (!isBetween(timber.length, { MIN_LENGTH, MAX_LENGTH }) || !isBetween(timber.numCut, { 1, timber.length - 1}))
	{
		PrintErrorSizeValues();
		return false;
	}
	return true;
}

void RecordMinPrice(unsigned value, const std::string & nameFile)
{
	std::ofstream outFile(nameFile);
	outFile << value;
}

unsigned CalcBisection(const Timber & timber)
{
	unsigned numCuts = timber.numCut;
	unsigned length = timber.length;
	unsigned price = 0;

	std::vector<unsigned> partsOfTimber = { length };

	while (numCuts > 0)
	{
		if (partsOfTimber[0] >= MIN_LENGTH)
		{
			price += partsOfTimber[0];
			length = partsOfTimber[0];
			partsOfTimber.push_back(length / 2);
			partsOfTimber.push_back(length - length / 2);
			--numCuts;
			partsOfTimber.erase(partsOfTimber.begin());
		}
		else
		{
			partsOfTimber.erase(partsOfTimber.begin());
		}

	}
	return price;
}

unsigned GumUpTimber(const Timber & timber)
{
	unsigned numCuts = timber.numCut;
	unsigned length = timber.length;
	unsigned price = 0;

	price += numCuts / 2 * MIN_LENGTH;

	std::map<unsigned, unsigned> timberGlueMap;
	timberGlueMap.emplace(length, 0);
	timberGlueMap.emplace(MIN_LENGTH, numCuts / 2);
	if (numCuts % 2 != 0)
	{
		timberGlueMap.emplace(MIN_LENGTH - 1, 1);
	}
	timberGlueMap[length - numCuts] += 1;

	unsigned value = 0;
	unsigned amount = 0;

	while (timberGlueMap.size() >= 2)
	{
		value = timberGlueMap.begin()->first;
		amount = timberGlueMap.begin()->second;

		price += amount / 2 * value * 2;

		auto it = timberGlueMap.find(value);
		timberGlueMap.erase(it);
		if (amount / 2 != 0)
		{
			timberGlueMap.emplace(value * 2, amount / 2);
		}
		if (amount % 2 != 0)
		{
			price += timberGlueMap.begin()->first + value;
			timberGlueMap.begin()->second -= 1;
			timberGlueMap[timberGlueMap.begin()->first + value] += 1;
		}
	}
	return price;
}

bool CutTimber(const std::string & inputFileName, const std::string & outputFileName)
{
	Timber plank;
	if (!ReadFromFile(plank, inputFileName))
	{
		return false;
	}

	unsigned price = 0;
	
	if (plank.length == plank.numCut + 1)
	{
		price = CalcBisection(plank);
	}
	else
	{
		price = GumUpTimber(plank);
	}
	RecordMinPrice(price, outputFileName);
	return true;
}

int main(int argc, char * argv[])
{
	if (argc == 3)
	{
		return CutTimber(argv[1], argv[2]);
	}
	else
	{
		std::cout << "Example: lab.exe \"input.txt\" \"output.txt\"" << std::endl;
	}
}