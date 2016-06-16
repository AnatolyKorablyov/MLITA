#include "stdafx.h"
#include "FindCommonElements.h"


FamilyNames ReadFromFile(const std::string & inputFileName)
{
	std::ifstream inpFile(inputFileName);
	FamilyNames family;
	inpFile >> family.fatherName;
	inpFile >> family.motherName;
	return family;
}

void RecordingInFile(const std::string & outputFileName, FamilyNames & family)
{
	std::ofstream outFile(outputFileName);
	outFile << family.sonName;
}

bool CheckNameRange(size_t sizeName)
{
	return (sizeName > 0 && sizeName < MAX_SIZE_NAME);
}



void FindMaxLenghtName(FamilyNames & family, const std::map<char, NamesCoordInFamily> & letters)
{
	auto it = letters.rbegin();
	size_t fIt = it->second.first;
	size_t mIt = it->second.second;
	family.sonName = it->first;
	while (fIt != family.fatherName.length() && mIt != family.motherName.length())
	{
		if (family.fatherName[fIt + 1] < family.motherName[mIt + 1])
		{
			++fIt;
		}
		else if (family.fatherName[fIt + 1] > family.motherName[mIt + 1])
		{
			++mIt;
		}
		else
		{
			++fIt;
			++mIt;
			family.sonName += family.fatherName[fIt];
		}
	}
	if (family.fatherName.back() == family.motherName.back()
		&& it->second.second != family.motherName.length() - 1
		&& it->second.first != family.fatherName.length() - 1)
	{
		family.sonName += family.fatherName.back();
	}
}

bool CommonElements(FamilyNames & family)
{
	size_t fIt = family.fatherName.length();
	size_t mIt = family.motherName.length();
	size_t coordFather = mIt;
	size_t coordMother = fIt;
	char letter = 'a';
	std::map<char, NamesCoordInFamily> letters;
	bool commonIsFound = false;
	if (!CheckNameRange(fIt) || !CheckNameRange(fIt))
	{
		return false;
	}
	for (size_t fIt = family.fatherName.length(); fIt > 0; --fIt)
	{
		for (size_t mIt = family.motherName.length(); mIt > 0; --mIt)
		{
			if (family.fatherName[fIt - 1] == family.motherName[mIt - 1] && family.fatherName[fIt - 1] >= letter)
			{
				coordMother = mIt - 1;
				coordFather = fIt - 1;
				letter = family.fatherName[fIt - 1];

				letters[letter] = { coordFather, coordMother };
				commonIsFound = true;
			}
		}
	}
	if (commonIsFound)
	{
		FindMaxLenghtName(family, letters);
	}
	return commonIsFound;
}
