#pragma once
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <stack>
#include <iterator>

struct Edge
{
    int m_Begin;
    int m_End;
};

enum class StepState
{
    NOTFOUND = 0,
    FOUND = 1,
    VISITED = 2,
};

static constexpr int VISITED = 2;
using AdjacencyMartixType = std::vector<std::vector<int>>;
class MyGraph
{
private:

protected:
    //---------------------проход вершин---------------//
    const AdjacencyMartixType * m_AdjacencyMatPtr = nullptr;
    std::vector<StepState> m_VerticesVec; // вершины графа
    std::queue<int> m_VerticesQueue; // для BFS
    std::stack<int> m_VerteciesStack; // for DFS

    //-----------------поиск кратчайшего пути-----------//
    std::stack<Edge> m_EdgesStack;
    std::vector<int> m_SearchResVec;

public:
    MyGraph(size_t VerticesCNT, const AdjacencyMartixType & AdjecencyMatPars);

    std::vector<int> MakeBFS();
    std::vector<int> MakeDFS();
    void RecursiveDFS(int beginVertex, int endVertex);

    void SearchTheShortestPath(std::istream & is);
    void SearchLexocographicalOfTheFirstPath(std::istream & is);

    void ClearVector();

    void ClearQueue();

    void PrintBFS(std::ostream & os);
    void PrintDFS(std::ostream & os);
    void PrintSearchRes();
    void PrintLexSearchRes();

};

