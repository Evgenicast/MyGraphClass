#pragma once
#include <vector>
#include <stack>
#include <iostream>
#include <iterator>
#include <queue>
#include <exception>
#include <fstream>
#include <optional>
#include "json.h"

struct Edge
{
    int From;
    int To;
};

enum class StepState
{
    NOTFOUND = 0,
    FOUND = 1,
    VISITED = 2,
    NOTVISITED = 3,
};

class MyGraph_1_0
{
private:
    std::vector<std::vector<int>> m_AdjacencyMatrix; // граф (матрица инцендентности)
    std::vector<StepState> m_VerticiesStatus; // вершины графа (NOTFOUND, FOUND, VISITED, NOTVISITED)
    std::queue<int> m_VerticiesQueueBFS; // для BFS
    std::stack<int> m_VerticiesStackDFS; // для DFS
    std::vector<int> m_VerteciesToPrintVec; // для вывода
    int m_VerticiesCount;
    //-------------Search------------//
    std::stack<Edge> m_EdgesStack;
    std::vector<int> m_SearchResultVec;
    //-------------Deikstra----------//
    std::vector<int> m_PathWeightsSumVec;    
    //------------input-------------//
    json::Dict m_GraphInputSettingsJson;
public:
    MyGraph_1_0() = default;
    MyGraph_1_0(std::string filename_);

    void TraverseAndSearchPathBFS(int vertex_);
    void SearchBFS(int vertex_);

    void TraverseAndSearchPathDFS(int vertex_); //lexicographical
    void SearchDFS(int vertex_);

    //---------------Deikstra---------------//
    void MakeShortestPathTo();

    //---------------input-----------------//
    void ProcessInputDataForGraph(std::string filename_);
    void CreateWeightedGraphFromInputFile(std::ifstream & f_);
    void CreateNotWeightedGraphFromInputFile(std::ifstream & f_);
    void ProcessGraphSettingsFromJSON(std::ifstream & s);
    void CreateGraphFromJSON();

    //-------------Print--------------//
    void PrintGraph();
    void PrintTheShortestPathInWeightedGraph() const; // Through all vertecies
    void ProcessAndPrintShortestPath() const; //From first to the last

    //-------------utilites-------------//
    std::optional<int> ExtractDigitFromString(const std::string & str_);
    void AdjenceMatrixInitialisation(int vertices_count_);
};

