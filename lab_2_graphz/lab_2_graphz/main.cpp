#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

static const unsigned MAX_SETTLEMENTS = 10000;
static const unsigned MAX_ROADS = 100000;

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

struct GraphPath
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

bool ReadFromFile(Graph & KruskalGraph, const std::string & nameFile)
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
			KruskalGraph.numNodes = vectorNumbers[0];
			KruskalGraph.numRoad = vectorNumbers[1];
		}
		else if (count > 0 && vectorNumbers.size() == 3)
		{
			nodeGraph.home = vectorNumbers[0];
			nodeGraph.destination = vectorNumbers[1];
			nodeGraph.weight = vectorNumbers[2];
			KruskalGraph.graphVector.push_back(nodeGraph);
		}
		count += 1;
	}
	return true;
}

bool compareWeight(GraphNode a, GraphNode b) const
{
	return a.weight < b.weight;
}

void SortGraph(Graph & graphKraskal)
{
	std::sort(graphKraskal.graphVector.begin(), graphKraskal.graphVector.end(), compareWeight);
}

bool CheckNode(unsigned node, const GrapthPath & pathGraph)  const
{
	for (auto i : pathGraph.graphVector)
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
	GraphPath pathGraph;
	std::vector<GraphNode> vectorGrapth = graphKraskal.graphVector;
	pathGraph.graphVector.push_back(vectorGrapth[0]);
	pathGraph.sizePath = vectorGrapth[0].weight;
	for (size_t i = 0; i < graphKraskal.numNodes - 2; ++i)
	{
		for (auto j : vectorGrapth)
		{
			if ((!CheckNode(j.home, pathGraph) && CheckNode(j.destination, pathGraph)) || 
				(CheckNode(j.home, pathGraph) && !CheckNode(j.destination, pathGraph)))
			{
				pathGraph.graphVector.push_back(j);
				pathGraph.sizePath += j.weight;
				break;
			}
		}
	}
	return pathGraph;
}

void RecordPathToOutputFile(const std::string & outputFileName, const GrapthPath & pathGraph)
{
	std::ofstream outFile(outputFileName);
	outFile << pathGraph.sizePath << std::endl;
	for (auto i : pathGraph.graphVector)
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
	else if (!(graphKraskal.numNodes >= 1 && graphKraskal.numNodes <= MAX_SETTLEMENTS &&
		graphKraskal.numRoad >= 1 && graphKraskal.numRoad <= MAX_ROADS))
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
