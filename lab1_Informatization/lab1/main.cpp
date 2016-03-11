// Кораблёв Анатолий, ПС-22
// lab_1 1.5 Информатизация садоводства (7)
//1.5.Информатизация садоводства(8)
//
//Дачный участок Степана Петровича имеет форму прямоугольника размером a  b.На участке
//
//имеется n построек, причем основание каждой постройки — прямоугольник со сторонами,
//
//параллельными сторонам участка.
//
//Вдохновленный успехами соседей, Степан Петрович хочет посадить на своем участке m видов
//
//плодовых культур(участок Степана Петровича находится в северной местности, поэтому m = 1
//
//	или m = 2).Для каждого вида растений Степан Петрович хочет выделить отдельную
//
//	прямоугольную грядку со сторонами, параллельными сторонам участка.Само собой, грядки не
//
//	могут занимать территорию, занятую постройками или другими грядками.
//
//	Степан Петрович хочет расположить грядки таким образом, чтобы их суммарная площадь была
//
//	максимальной.Грядки не должны пересекаться, но могут касаться друг друга.
//
//	грядка №1
//
//	сарай
//
//	Требуется написать программу, которая по заданным размерам участка и координатам
//
//	построек определяет оптимальное расположение планируемых грядок.
//
//	Ввод.В первой строке входного файла содержатся два целых числа n и m(0 ≤ n ≤ 10; 1 ≤ m ≤ 2).
//
//	Во второй строке содержатся два целых числа a и b(1 ≤ a, b ≤ 10000).Далее следуют n строк,
//
//	каждая из которых содержит четыре целых числа xi, 1, yi, 1, xi, 2, yi, 2 –координаты двух
//
//	противоположных углов постройки(0  xi, 1 < xi, 2  a, 0  yi, 1 < yi, 2   b).Различные постройки не могут
//
//	пересекаться, но могут касаться друг друга.
//
//	Вывод.Необходимо вывести m строк, каждая из которых содержит координаты двух
//
//	противоположных углов предполагаемой грядки.Координаты должны быть целыми(всегда
//
//		можно добиться максимальной суммарной площади грядок, располагая их в прямоугольниках с
//
//		целыми координатами).В случае, если в вашем решении Степану Петровичу следует расположить
//
//	менее m грядок, необходимо вывести для грядок, которые не следует сажать, строку «0 0 0 0»(см.
//
//		второй пример).
//
//	Примеры
//
//	Ввод 1         Ввод 2
//
//	2 2            3 2
//
//	7 5            4 4
//
//	4 2 6 4        0 0 4 1
//
//	0 1 2 2        0 1 1 4
//
//	3 1 4 4
//
//	Вывод 1        Вывод 2
//
//	0 2 4 5        1 1 3 4
//
//	2 0 7 2        0 0 0 0

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct CGarden
{
	int numCrops; // m - Количество культур 1 <= m <= 2
	int numBuildings; // n - Количество построек 0 <= n <= 10
	int length; // a, b - длина и ширина участка 1 <= a, b <= 10000
	int width;
	int areaGarden = 0;
	vector<pair<pair<int, int>, pair<int, int>>> doths; // Координаты постройки doths[0].first = первая точка; doths[0].first.first = x1
	vector<pair<pair<int, int>, pair<int, int>>> crops;
};

vector<int> EnterWithSpaces(string string)
{
	vector<int> numbers;
	int len = string.length();
	int i = 0;
	int m_number = 0;
	while (i <= len)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			m_number = m_number * 10 + (string[i] - '0');
		}
		else
		{
			numbers.push_back(m_number);
			m_number = 0;
		}
		i++;
	}
	return numbers;
}


CGarden ReadFile(string inputFile)
{
	std::ifstream inpFile(inputFile);
	if (!inpFile.is_open())
	{
		std::cout << "Error open file\n";
		system("pause");
		exit(1);
	}
	int count = 0;
	CGarden garden;
	while (!inpFile.eof())
	{
		vector<int> numbers;
		std::string string;
		std::getline(inpFile, string);
		if (count == 0)
		{
			numbers = EnterWithSpaces(string);
			garden.numBuildings = numbers[0];
			garden.numCrops = numbers[1];
		}
		else if (count == 1)
		{
			numbers = EnterWithSpaces(string);
			garden.length = numbers[0];
			garden.width = numbers[1];
		}
		else
		{
			numbers = EnterWithSpaces(string);
			int x1 = numbers[0];
			int y1 = numbers[1];
			int x2 = numbers[2];
			int y2 = numbers[3];
			garden.doths.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
		}
		count++;
	}
	return garden;
}

bool СheckEmptyCell(const CGarden & gard, const int & x, const int & y)
{
	for (auto dot : gard.doths)
	{
		if (dot.first.first <= x && dot.second.first - 1 >= x && dot.first.second <= y && dot.second.second - 1 >= y)
		{
			return false;
		}
	}
	return true;
}

void FindSecondCoordinate(CGarden & yard, int x, int y)
{
	int x1 = x;
	int y1 = y;
	vector<std::pair<int, int>> coordinateLst;
	coordinateLst.push_back(std::make_pair(x, y));
	int borderX = yard.length;
	int borderY = yard.width;
	bool empty = СheckEmptyCell(yard, x, y);
	if (empty)
	{
		while (coordinateLst.size() > 0)
		{
			int x = coordinateLst[0].first;
			int y = coordinateLst[0].second;
			if (x < borderX && y < borderY)
			{
				yard.areaGarden += 1;
				if (x < yard.length - 1)
				{
					empty = СheckEmptyCell(yard, x + 1, y);
					if (empty)
					{
						coordinateLst.push_back(std::make_pair(x + 1, y));
					}
					else
					{
						if (x + 1 < borderX)
						{
							borderX = x + 1;
						}
					}
				}
				if (y < yard.width - 1)
				{
					empty = СheckEmptyCell(yard, x, y + 1);
					if (empty)
					{
						coordinateLst.push_back(std::make_pair(x, y + 1));
					}
					else
					{
						if (y + 1 < borderY)
						{
							borderY = y + 1;
						}
					}
				}
			}
			coordinateLst.erase(coordinateLst.begin());
		}
		int x2 = borderX;
		int y2 = borderY;
		yard.doths.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
		yard.crops.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
	}
}

CGarden FindNewGardenBed(const CGarden & garden)
{
	CGarden result;
	for (int i = 0; i < garden.width; i++)
	{
		for (int j = 0; j < garden.length; j++)
		{
			CGarden yard = garden;
			FindSecondCoordinate(yard, j, i);
			if (yard.areaGarden > result.areaGarden)
			{
				result = yard;
			}
		}
	}
	return result;
}

void FilindToOutput(const CGarden & gard)
{
	ofstream outFile("output.txt");
	for (auto i : gard.crops)
	{
		outFile << i.first.first << " " << i.first.second << " ";
		outFile << i.second.first << " " << i.second.second << endl;
	}
	for (size_t i = 0; i < gard.numCrops - gard.crops.size(); i++)
	{
		outFile << "0 0 0 0" << endl;
	}
}

void MakeGarden(const CGarden & gard)
{
	CGarden result = gard;
	for (int i = 0; i < gard.width; i++)
	{
		for (int j = 0; j < gard.length; j++)
		{
			CGarden garden = gard;
			FindSecondCoordinate(garden, j, i);
			if (garden.numCrops > 1 && garden.areaGarden > 0)
			{
				garden = FindNewGardenBed(garden);
			}
			if (garden.areaGarden > result.areaGarden)
			{
				result = garden;
			}
		}
	}
	FilindToOutput(result);
}

int main()
{	
	string nameFile = "input.txt";
	CGarden garden;
	garden = ReadFile(nameFile);
	MakeGarden(garden);
	return 0;
}	