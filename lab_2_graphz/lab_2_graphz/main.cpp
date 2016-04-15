#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

static const unsigned MAX_SETTLEMENTS = 10000;
static const unsigned MAX_ROADS = 100000;

struct GraphNode
{
	unsigned home = 0;
	unsigned destination = 0;
	int weight = 0;
};

struct Graph
{
	int sizePath = 0;
	unsigned numNodes = 0;
	std::vector<GraphNode> graphVector;
};

void PrintErrorSizeValues()
{
	std::cout << "the number of settlements and the roads are not in a range" << std::endl;
	std::cout << "correct range (1 <= settlements <= 10000) and (1 <= roads <= 100000)" << std::endl;
}

bool isBetween(int value, const std::pair<int, int> & rangeValue)
{
	return (value >= rangeValue.first && value <= rangeValue.second);
}

bool ReadFromFile(Graph & graphKraskal, const std::string & nameFile)
{
	GraphNode nodeGraph;
	std::ifstream inpFile(nameFile);
	
	if (!inpFile.is_open())
	{
		return false;
	}
	
	int numRoads;
	inpFile >> graphKraskal.numNodes;
	inpFile >> numRoads;
	
	if (!isBetween(graphKraskal.numNodes, { 1, MAX_SETTLEMENTS }) || !isBetween(numRoads, { 1, MAX_ROADS }))
	{
		PrintErrorSizeValues();
		return false;
	}

	while (inpFile)
	{
		inpFile >> nodeGraph.home >> nodeGraph.destination >> nodeGraph.weight;
		graphKraskal.graphVector.push_back(nodeGraph);
	}
	return true;
}

void SortGraph(Graph & graphKraskal)
{
	auto compare = [](const GraphNode &a, const GraphNode &b) {
		return a.weight < b.weight;
	};
	std::sort(graphKraskal.graphVector.begin(), graphKraskal.graphVector.end(), compare);
}

bool CheckNode(unsigned node, const Graph & pathGrapth)
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

Graph CalcMinPath(const Graph & graphKraskal)
{
	Graph pathGrapth;
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

void RecordPathToOutputFile(const std::string & outputFileName, const Graph & pathGrapth)
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

bool KraskalRoads(const std::string & inputFileName, const std::string & outputFileName)
{
	Graph graphKraskal;
	if (!ReadFromFile(graphKraskal, inputFileName))
	{
		PrintErrorReadFromFile();
		return false;
	}
	SortGraph(graphKraskal);
	Graph pathGrapth = CalcMinPath(graphKraskal);
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