#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


struct GraphNode
{
	unsigned home;
	unsigned destination;
	int weight;
};

struct Graph
{
	unsigned numRoad;
	unsigned numNodes;
	std::vector<GraphNode> graphVector;
};

struct GrapthPath
{
	int sizePath;
	std::vector<GraphNode> graphVector;
};

std::vector<int> EnterIntWithSpaces(const std::string & string)
{
	std::vector<int> numbers;
	int m_number = 0;
	for (size_t i = 0; i <= string.length(); ++i)
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
	}
	if (m_number != 0)
	{
		numbers.push_back(m_number);
	}
	return numbers;
}

bool ReadFromFile(Graph & graphKraskal, const std::string & nameFile)
{
	
	GraphNode nodeGraph;
	std::ifstream inpFile(nameFile);
	if (!inpFile.is_open())
	{
		return false;
	}
	std::vector<GraphNode> graphz;
	size_t count = 0;
	std::string string;
	std::vector<int> vectorNumbers;
	while (!inpFile.eof())
	{
		string.clear();
		std::getline(inpFile, string);
		vectorNumbers = EnterIntWithSpaces(string);
		if (count == 0 && vectorNumbers.size() == 2)
		{
			graphKraskal.numNodes = vectorNumbers[0];
			graphKraskal.numRoad = vectorNumbers[1];
		}
		else if (count > 0 && vectorNumbers.size() == 3)
		{
			nodeGraph.home = vectorNumbers[0];
			nodeGraph.destination = vectorNumbers[1];
			nodeGraph.weight = vectorNumbers[2];
			graphKraskal.graphVector.push_back(nodeGraph);
		}
		count += 1;
	}
	return true;
}

bool compareWeight(GraphNode a, GraphNode b)
{
	return a.weight < b.weight;
}

void SortGraph(Graph & graphKraskal)
{
	std::sort(graphKraskal.graphVector.begin(), graphKraskal.graphVector.end(), compareWeight);
}

bool CheckNode(unsigned node, const GrapthPath & pathGrapth)
{
	for (auto i : pathGrapth.graphVector)
	{
		if (node == i.home || node == i.destination)
		{
			return true;
		}
	}
	return false;
}

GrapthPath CalcMinPath(const Graph & graphKraskal)
{
	GrapthPath pathGrapth;
	std::vector<GraphNode> vectorGrapth = graphKraskal.graphVector;
	pathGrapth.graphVector.push_back(vectorGrapth[0]);
	pathGrapth.sizePath = vectorGrapth[0].weight;
	for (size_t i = 0; i < graphKraskal.numNodes - 2; ++i)
	{
		for (auto j : vectorGrapth)
		{
			if ((!CheckNode(j.home, pathGrapth) && CheckNode(j.destination, pathGrapth)) || 
				(CheckNode(j.home, pathGrapth) && !CheckNode(j.destination, pathGrapth)))
			{
				pathGrapth.graphVector.push_back(j);
				pathGrapth.sizePath += j.weight;
				break;
			}
		}
	}
	return pathGrapth;
}

void RecordPathToOutputFile(const std::string & outputFileName, const GrapthPath & pathGrapth)
{
	std::ofstream outFile(outputFileName);
	outFile << pathGrapth.sizePath << std::endl;
	for (auto i : pathGrapth.graphVector)
	{
		outFile << i.home << " " << i.destination << std::endl;
	}
}

void PrintErrorReadFromFile()
{
	std::cout << "Error read input file!" << std::endl;
}

void PrintErrorSizeValues()
{
	std::cout << "the number of settlements and the roads are not in a range" << std::endl;
	std::cout << "correct range (1 <= settlements <= 10000) and (1 <= roads <= 100000)" << std::endl;
}

bool KraskalRoads(const std::string & inputFileName, const std::string & outputFileName)
{
	Graph graphKraskal;
	if (!ReadFromFile(graphKraskal, inputFileName))
	{
		PrintErrorReadFromFile();
		return false;
	}
	else if (!(graphKraskal.numNodes >= 1 && graphKraskal.numNodes <= 10000 &&
		graphKraskal.numRoad >= 1 && graphKraskal.numRoad <= 100000))
	{
		PrintErrorSizeValues();
		return false;
	}
	SortGraph(graphKraskal);
	GrapthPath pathGrapth;
	pathGrapth = CalcMinPath(graphKraskal);
	RecordPathToOutputFile(outputFileName, pathGrapth);
	return true;
}

void PrintExample()
{
	std::cout << "Input Failed" << std::endl;
	std::cout << "test.exe \"input.txt\" \"output.txt\"" << std::endl;
}

int main(int argc, char * argv[])
{
	/*std::string inputFileName = "input.txt";
	std::string outputFileName = "output.txt";
	*/
	if (argc == 3)
	{
		return KraskalRoads(/*inputFileName*/ argv[1], /*outputFileName*/ argv[2]);
	}
	else
	{
		PrintExample();
		return 1;
	}
	
}
