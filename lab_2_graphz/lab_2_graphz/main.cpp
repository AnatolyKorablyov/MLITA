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

bool comp(GraphNode a, GraphNode b)
{
	return a.weight < b.weight;
}

void SortGraph(Graph & graphKraskal)
{
	std::sort(graphKraskal.graphVector.begin(), graphKraskal.graphVector.end(), comp);
}

void CalcMinPath(Graph & graphKraskal)
{
	GrapthPath pathGrapth;
	std::vector<GraphNode> vectorGrapth = graphKraskal.graphVector;

}
bool Kraskal(const std::string & inputFileName, const std::string & outputFileName)
{
	Graph graphKraskal;
	if (!ReadFromFile(graphKraskal, inputFileName))
	{
		return false;
	}
	std::cout << graphKraskal.numNodes << " " << graphKraskal.numRoad << std::endl;
	for (auto i : graphKraskal.graphVector)
	{
		std::cout << i.home << " " << i.destination << " " << i.weight << std::endl;
	}
	SortGraph(graphKraskal);
}

int main()
{
	std::string inputFileName = "input.txt";
	std::string outputFileName = "output.txt";
	return Kraskal(inputFileName, outputFileName);
}