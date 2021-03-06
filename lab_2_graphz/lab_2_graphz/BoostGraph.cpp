﻿#include "stdafx.h"
#include "BoostGraph.h"

const unsigned MAX_SETTLEMENTS = 10000;
const unsigned MAX_ROADS = 100000;

CBoostGraph::CBoostGraph()
{
}


CBoostGraph::~CBoostGraph()
{
}

// Устанавливает функцию-обработчик шага алгоритма.
// Функция принимает строку - сериализованное в dot состояние графа.
void CBoostGraph::SetStepHandler(const CBoostGraph::StepHandler &handler)
{
    m_stepHandler = handler;
}

bool CBoostGraph::ReadText(std::istream & in)
{
	size_t edgeCount = 0;
	size_t vertexCount = 0;
    if (!(in >> vertexCount >> edgeCount))
    {
        return false;
    }

	if (edgeCount > MAX_SETTLEMENTS || vertexCount > MAX_ROADS)
	{
		return false;
	}

	for (size_t i = 0; i < vertexCount; ++i)
	{
		// add_vertex() возвращает индекс вершины (size_t).
		boost::add_vertex(m_graph);
	}

	for (size_t i = 0; i < edgeCount; ++i)
	{
		Edge edge;
		size_t start = 0;
		size_t end = 0;
        if (!(in >> start >> end >> edge.price))
		{
			return false;
        }
		if (start == 0 || end == 0 || start > vertexCount || end > vertexCount)
		{
			return false;
		}
        // индексы уменьшаем на единицу, т.к. индексация вершин начинается с 0.
        --start;
        --end;

		// add_edge(...) возвращает пару {индексатор ребра, bool}.
		auto result = boost::add_edge(start, end, m_graph);
		m_graph[result.first] = edge;
	}

	return true;
}

void CBoostGraph::RunKraskal()
{
	SerializeCurrentStep();

	auto vertices = m_graph.vertex_set();
	std::unordered_set<size_t> remainingIds(vertices.begin(), vertices.end());

	// Определим вспомогательную λ-функцию, отмечающую вершину как пройденную.
	auto markVertex = [&](size_t vertexId) {
		remainingIds.erase(vertexId);
		m_graph[vertexId].accepted = true;
	};

	std::vector<edge_descriptor> candidates;

	for (const auto &edge : boost::make_iterator_range(boost::edges(m_graph)))
	{
		candidates.push_back(edge);
	}
	auto compareFn = [this](const edge_descriptor &a, const edge_descriptor &b) {
		return m_graph[a].price < m_graph[b].price;
	};
	std::sort(candidates.begin(), candidates.end(), compareFn);

	markVertex(candidates.front().m_source);
	SerializeCurrentStep();
	m_minimalTree.push_back(candidates.front());
	m_graph[candidates.front()].accepted = true;

	markVertex(candidates.front().m_target);
	SerializeCurrentStep();

	while (!remainingIds.empty())
	{
		for (auto j : candidates)
		{
			if (m_graph[j.m_source].accepted && !(m_graph[j.m_target].accepted))
			{
				m_graph[j].accepted = true;
				m_minimalTree.push_back(j);
				markVertex(j.m_target);
				SerializeCurrentStep();
				break;
			}
			if (!(m_graph[j.m_source].accepted) && m_graph[j.m_target].accepted)
			{
				m_graph[j].accepted = true;
				m_minimalTree.push_back(j);
				markVertex(j.m_source);
				SerializeCurrentStep();
				break;
			}
			if (!(m_graph[j.m_source].accepted) && !(m_graph[j.m_target].accepted))
			{
				m_graph[j].accepted = true;
				m_minimalTree.push_back(j);
				markVertex(j.m_source);
				markVertex(j.m_target);
				SerializeCurrentStep();
				break;
			}
			if (m_graph[j.m_source].accepted && m_graph[j.m_target].accepted && !m_graph[j].accepted)
			{
				m_graph[j].accepted = true;
				m_minimalTree.push_back(j);
				SerializeCurrentStep();
				break;
			}
		}
	}
}

void CBoostGraph::SerializeCurrentStep() const
{
    if (!m_stepHandler)
    {
        return;
    }
    std::stringstream out;

    auto vertexWriter = [&](std::ostream& out, size_t vertexId) {
        const char *color = (m_graph[vertexId].accepted ? "FF0000" : "C0FFC0");
        out << "[style=\"filled\", fillcolor=\"#" << color << "\"]";
    };
    auto edgeWriter = [&](std::ostream& out, edge_descriptor edgeId) {
        auto &edge = m_graph[edgeId];
        unsigned width = (edge.accepted ? 5 : 2);
        out << "[penwidth=" << width << ", label=\"" << std::to_string(edge.price) << "\"]";

    };

    boost::write_graphviz(out, m_graph, vertexWriter, edgeWriter);
    m_stepHandler(out.str());
}

bool CBoostGraph::PrintResults(std::ostream & out)
{
    std::vector<edge_descriptor> edges(m_minimalTree);
    int64_t cost = 0;

    for (edge_descriptor & edge : edges)
    {
        cost += m_graph[edge].price;
        if (edge.m_source > edge.m_target)
        {
            std::swap(edge.m_source, edge.m_target);
        }
    }
    std::sort(edges.begin(), edges.end(), [](const edge_descriptor &a, const edge_descriptor &b) {
        return a.m_source < b.m_source || (a.m_source == b.m_source && a.m_target < b.m_target);
    });

    out << cost << std::endl;
    for (edge_descriptor & edge : edges)
    {
        out << (edge.m_source + 1) << " " << (edge.m_target + 1) << std::endl;
    }
    return bool(out);
}
