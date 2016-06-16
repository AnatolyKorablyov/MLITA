// lab03_strings_names.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FindCommonElements.h"

void PrintExample()
{
	std::cout << "An incorrect number of arguments!" << std::endl;
	std::cout << "Example: lab.exe input.txt output.txt" << std::endl;
}

int main(int argc, char * argv[])
{
	if (argc == 3)
	{
		FamilyNames family = ReadFromFile(argv[1]);
		if (!CommonElements(family))
		{
			std::cout << "no matches found" << std::endl;
		}
		RecordingInFile(argv[2], family);
		return 1;
	}
	return 0;
}

