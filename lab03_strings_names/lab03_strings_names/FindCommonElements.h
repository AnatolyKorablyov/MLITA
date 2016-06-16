#pragma once
#include "stdafx.h"

const unsigned MAX_SIZE_NAME = 100'000;

struct FamilyNames
{
	std::string fatherName = "";
	std::string motherName = "";
	std::string sonName = "";
};

typedef std::pair<size_t, size_t> NamesCoordInFamily;
FamilyNames ReadFromFile(const std::string & inputFileName);

void RecordingInFile(const std::string & outputFileName, FamilyNames & family);

bool CheckNameRange(size_t sizeName);

void FindMaxLenghtName(FamilyNames & family, const std::map<char, NamesCoordInFamily> & letters);

bool CommonElements(FamilyNames & family);
