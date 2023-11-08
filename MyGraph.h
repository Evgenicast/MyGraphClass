#pragma once
#include <vector>
#include <stack>
#include <iostream>
#include <iterator>
#include <queue>
#include <exception>
#include <fstream>

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
    std::vector<std::vector<int>> m_AdjenceMatrix; // граф (матрица инцендентности)
    std::vector<StepState> m_VerticiesStatus; // вершины графа (NOTFOUND, FOUND, VISITED, NOTVISITED)
    std::queue<int> m_VerticiesQueue; // для BFS
    std::stack<int> m_VerticiesStack; // для DFS
    std::vector<int> m_GraphVec;
    int m_VerticiesCount;
    //-------------Search------------//
    std::stack<Edge> m_EdgesStack;
    std::vector<int> m_SearchResultVec;
    //-------------Deikstra----------//
    std::vector<int> m_PathWeightsSumVec;
public:
    MyGraph_1_0() = default;
    MyGraph_1_0(std::string filename_);

    void TraverseAndSearchPathBFS(int Vertex_);
    void SearchBFS(int Vertex_);

    void TraverseAndSearchPathDFS(int Vertex_);
    void SearchDFS(int Vertex_);

    //---------------Deikstra---------------//
    void MakeShortestPathTo();

    //---------------input-----------------//
    void ProcessInputDataForGraph(std::string filename_);
    void CreateWeightedGraphFromInputFile(std::ifstream & f_);
    void CreateNotWeightedGraphFromInputFile(std::ifstream & f_);

    //-------------Print--------------//
    void PrintGraph();
    void PrintTheShortestPathInWeightedGraph(); // Through all vertecies
    void ProcessAndPrintShortestPath(); //From first to the last
};

