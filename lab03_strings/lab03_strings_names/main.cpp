// lab03_strings_names.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct FamilyNames
{
	std::string fatherName = "";
	std::string motherName = "";
	std::vector<char> sonName;
};

FamilyNames ReadFromFile(const std::string & inputFileName)
{
	std::ifstream inpFile(inputFileName);
	FamilyNames family;
	inpFile >> family.fatherName;
	inpFile >> family.motherName;
	return family;
}


void CommonElements(FamilyNames & family)
{
	size_t fIt = family.fatherName.length();
	size_t mIt = family.motherName.length();

	while (fIt > 0 && mIt > 0)
	{
		if (family.fatherName[fIt - 1] < family.motherName[mIt - 1])
		{
			--fIt;
		}
		else if (family.fatherName[fIt - 1] > family.motherName[mIt - 1])
		{
			--mIt;
		}
		else if (family.fatherName[fIt - 1] == family.motherName[mIt - 1])
		{
			--fIt;
			--mIt;
			family.sonName.push_back(family.fatherName[fIt]);
		}
	}
	for (auto &i : family.sonName)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char * argv[])
{
	FamilyNames family = ReadFromFile("input5.txt");
	std::cout << family.fatherName << std::endl;
	std::cout << family.motherName << std::endl;
	CommonElements(family);
    return 0;
}

