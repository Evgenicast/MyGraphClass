#include "MyGraph.h"

using namespace std;

MyGraph_1_0::MyGraph_1_0(string filename_)
{
    ProcessInputDataForGraph(filename_);
}

void MyGraph_1_0::ProcessInputDataForGraph(std::string filename_)
{
    if (filename_ == "input.txt")
    {
        ifstream f(filename_);
        if (!f)
        {
            cout << "Error! File not open" << endl;
            return;
        }
        CreateNotWeightedGraphFromInputFile(f);

    }
    else if(filename_ == "Deikstra.txt")
    {
        ifstream f(filename_);
        if (!f)
        {
            cout << "Error! File not open" << endl;
            return;
        }
        CreateWeightedGraphFromInputFile(f);
    }
    else if(filename_ == "JSON.json")
    {
        ifstream f(filename_);
        if (!f)
        {
            cout << "Error! File not open" << endl;
            return;
        }
        ProcessGraphSettingsFromJSON(f);
    }
}

void MyGraph_1_0::TraverseAndSearchPathBFS(int vertex_)
{
    Edge edge;
    --vertex_;
    m_VerticiesStatus.clear();
    m_VerticiesStatus.resize(m_VerticiesCount, StepState::NOTFOUND); // все вершины не найдены пока

    while(!m_VerticiesQueueBFS.empty())
    {
        int vertex = m_VerticiesQueueBFS.front();
        m_VerticiesQueueBFS.pop();
        m_VerticiesStatus[vertex] = StepState::VISITED;

        for (size_t i = 0; i < m_VerticiesStatus.size(); ++i)
        {
            try
            {
                if (m_AdjacencyMatrix.at(vertex).at(i) == 1 && m_VerticiesStatus[i] == StepState::NOTFOUND)
                {
                    m_VerticiesQueueBFS.push(i);
                    m_VerticiesStatus[i] = StepState::FOUND;

                    edge.From = vertex;
                    edge.To = i;
                    m_EdgesStack.push(edge);
                    if (vertex == vertex_)
                    {
                        break;
                    }
                }
            }
            catch (std::out_of_range e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        m_VerteciesToPrintVec.push_back(vertex + 1);
    }
    SearchBFS(vertex_);
}

void MyGraph_1_0::TraverseAndSearchPathDFS(int vertex_) // lexicographical
{
    Edge edge;
    --vertex_;
    m_VerticiesStatus.clear();
    m_VerticiesStatus.resize(m_VerticiesCount, StepState::NOTFOUND); // все вершины не найдены пока

    while (!m_VerticiesStackDFS.empty())
    {
        int vertex = m_VerticiesStackDFS.top();
        m_VerticiesStackDFS.pop();
        if (m_VerticiesStatus[vertex] == StepState::VISITED)
            continue;

        m_VerticiesStatus[vertex] = StepState::VISITED;

        for (int i = m_VerticiesStatus.size() - 1; i >= 0; --i)
        {
            try
            {
                if (m_AdjacencyMatrix.at(vertex).at(i) == 1 && m_VerticiesStatus[i] == StepState::NOTFOUND)
                {
                    m_VerticiesStackDFS.push(i);
                    m_VerticiesStatus[i] = StepState::FOUND;
                    edge.From = vertex;
                    edge.To = i;
                    m_EdgesStack.push(edge);
                    if (vertex == vertex_)
                        break;
                }
            }
            catch (std::exception e)
            {
                std::cout << e.what() << std::endl;
            }
            m_VerteciesToPrintVec.push_back(vertex + 1);
        }
    }
    SearchDFS(vertex_);
}

void MyGraph_1_0::SearchBFS(int vertex_)
{
    Edge edge;
    std::cout << "Path to vertex " << vertex_ + 1 << std::endl;
    std::cout << vertex_ + 1;
    while (!m_EdgesStack.empty())
    {
        edge = m_EdgesStack.top();
        m_EdgesStack.pop();
        if (edge.To == vertex_)
        {
            vertex_ = edge.From;
            std::cout << " <- " << vertex_ + 1;
        }
    }
    std::cout << std::endl;
}

void MyGraph_1_0::SearchDFS(int vertex_)
{
    Edge edge;
    std::cout << "Path to vertex " << vertex_ + 1 << std::endl;
    std::cout << vertex_ + 1;
    while (!m_EdgesStack.empty())
    {
        edge = m_EdgesStack.top();
        m_EdgesStack.pop();
        if (edge.To == vertex_)
        {
            vertex_ = edge.From;
            std::cout << " <- " << vertex_ + 1;
        }
    }
    std::cout << std::endl;
}

//----------Deikstra------------------//
void MyGraph_1_0::MakeShortestPathTo()
{
    constexpr size_t MAX_VALUE_INDEX = 10000;
    constexpr size_t MAX_VALUE_WEIGHT = 20000; // любое заранее большее, чем возможные веса ребрa, число. Для сравнения между ними.
    m_PathWeightsSumVec.resize(m_VerticiesCount, MAX_VALUE_WEIGHT);
    vector<StepState> visited_edges_vec(m_VerticiesCount, StepState::NOTVISITED);
    int search_index;
    int min_weight;
    int weight_sum = 0;
    m_PathWeightsSumVec[0] = 0;

    do
    {
        search_index = MAX_VALUE_INDEX;
        min_weight = MAX_VALUE_WEIGHT;

        for (int i = 0; i < m_VerticiesCount; ++i)
        {
            if (visited_edges_vec[i] == StepState::NOTVISITED && m_PathWeightsSumVec[i] < min_weight) // выбираем вершину с минимальным весом из не посещенных, но посчитанных во втором цикле
            {
                min_weight = m_PathWeightsSumVec[i]; //выбираем минимальный вес из переданных ниже вершин.
                search_index = i; // передается индекс следующей минимальной вершины.
            }
        }
        if (search_index != MAX_VALUE_INDEX)
        {
            for (int i = 0; i < m_VerticiesCount; ++i)
            {
                if (m_AdjacencyMatrix[search_index][i] > 0)
                {
                    weight_sum = min_weight + m_AdjacencyMatrix[search_index][i];
                    if (weight_sum < m_PathWeightsSumVec[i])
                    {
                        m_PathWeightsSumVec[i] = weight_sum; // записываем веса вершин, куда ведет текущая
                    }
                }
            }
            visited_edges_vec[search_index] = StepState::VISITED;
        }
    } while (search_index < MAX_VALUE_INDEX);
}

//----------Deikstra------------------//

void MyGraph_1_0::CreateWeightedGraphFromInputFile(ifstream & f_)
{
    int VertexFrom = 0;
    int	VertexTo = 0;
    int EdgeWeight = 0;
    int GraphSize = 0;
    string InputStatus;
    vector<int> VerticiesTo_vec;

    f_ >> GraphSize;
    AdjenceMatrixInitialisation(GraphSize);

    m_VerticiesQueueBFS.push(0);
    m_VerticiesStackDFS.push(0);
    m_VerticiesCount = GraphSize;

    for (int i = 0; i < GraphSize; ++i)
    {
        while (VertexTo != -1)
        {
            f_ >> VertexTo;
            if (VertexTo != -1)
            {
                f_ >> EdgeWeight;
                m_AdjacencyMatrix[i][VertexTo - 1] = EdgeWeight;
            }
        }
        VertexTo = 0;
    }
}

void MyGraph_1_0::CreateNotWeightedGraphFromInputFile(ifstream & f_)
{
    int VertexFrom;
    int	VertexTo = 0;
    int GraphSize;

    f_ >> GraphSize;

    AdjenceMatrixInitialisation(GraphSize);

    m_VerticiesQueueBFS.push(0);
    m_VerticiesStackDFS.push(0);
    m_VerticiesCount = GraphSize;

    for (int i = 0; i < GraphSize; ++i)
    {
        while (VertexTo != -1)
        {
            f_ >> VertexTo;
            if (VertexTo != -1)
            {
                m_AdjacencyMatrix[i][VertexTo - 1] = 1;
            }
        }
        VertexTo = 0;
    }
}

void MyGraph_1_0::ProcessGraphSettingsFromJSON(std::ifstream & s)
{
    m_GraphInputSettingsJson = json::Load(s).GetRoot().AsDict();
    CreateGraphFromJSON();
}

void MyGraph_1_0::CreateGraphFromJSON()
{
    AdjenceMatrixInitialisation(m_GraphInputSettingsJson.find("vertices_count")->second.AsInt());
    const auto graph_settings = m_GraphInputSettingsJson.find("graph_settings");

    if(graph_settings != m_GraphInputSettingsJson.end())
    {
        for(const auto & data : graph_settings->second.AsDict())
        {
            int vertex_from;
            const auto VertecesMap = data.second.AsDict();
            vertex_from = ExtractDigitFromString(data.first).value();
            for(auto it = VertecesMap.begin(); it != VertecesMap.end(); ++it)
            {
                int vertex_to;
                vertex_to = ExtractDigitFromString(it->first).value();
                int weight = it->second.AsInt();
                m_AdjacencyMatrix[vertex_from - 1][vertex_to - 1] = weight;
            }
        }
    }
}

void MyGraph_1_0::PrintGraph()
{
    for (const auto & Vertices : m_VerteciesToPrintVec)
        std::cout << Vertices << std::endl;
    std::cout << std::endl;
}

void MyGraph_1_0::PrintTheShortestPathInWeightedGraph() const
{
    cout << "The shortest path through all vertices is: ";

    for(const auto & path : m_PathWeightsSumVec)
    {
        cout << path << ' ';
    }
    cout << endl;
}

void MyGraph_1_0::ProcessAndPrintShortestPath() const
{
    vector<int> shortest_path_vec(6);
    int end_index = shortest_path_vec.size() - 2;
    shortest_path_vec[0] = end_index + 1;
    int iterator = 1;
    int weight = m_PathWeightsSumVec[end_index]; // берем вес искомого ребара!!! ПОПРОБОВАТЬ ПЕРЕДАТЬ КАК ПАРАМЕТР

    while(end_index != 0)
    {
        for(int i = 0; i < m_VerticiesCount; ++i)
        {
            if(m_AdjacencyMatrix[i][end_index] != 0)
            {
                int backward_sum = weight - m_AdjacencyMatrix[i][end_index];
                if(backward_sum == m_PathWeightsSumVec[i])
                {
                    weight = backward_sum;
                    end_index = i;
                    shortest_path_vec[iterator] = i + 1;
                    ++iterator;
                }
            }
        }
    }

    cout << "The shortest path for the first to the last is: ";

    for(int i = iterator - 1; i >= 0; --i)
    {
        cout << shortest_path_vec[i] << ' ';
    }

    cout << endl;
    cout << "The shortest path for the first to the last is(copy method): ";
    copy(shortest_path_vec.rbegin() + 2, shortest_path_vec.rend(), ostream_iterator<int>(cout, " ")); // просто интересный способ вывода
    cout << endl;
}

std::optional<int> MyGraph_1_0::ExtractDigitFromString(const std::string & str_)
{
    optional<int> digit;
    for(int i = 0; i < str_.length(); ++i)
    {
        if(std::isdigit(str_[i]))
        {
            return digit = str_[i] - '0';
        }
    }
    return digit;
}

void MyGraph_1_0::AdjenceMatrixInitialisation(int vertices_count_)
{
    m_VerticiesCount = vertices_count_;
    m_AdjacencyMatrix.resize(m_VerticiesCount);
    for (int i = 0; i < m_VerticiesCount; ++i)
    {
        m_AdjacencyMatrix[i].resize(m_VerticiesCount);
    }
}

/*
           *5*
        *       *
    6*             *4
    *               *
    *      *1*      *
    *   *   *  *    *
    7*      *    *  *
            3* * * *2


Graph

adjacency matrix

   { 0 , 1 , 1 , 0 , 0 , 0 , 1 },
   { 1 , 0 , 1 , 1 , 0 , 0 , 0 },
   { 1 , 1 , 0 , 0 , 0 , 0 , 0 },
   { 0 , 1 , 0 , 0 , 1 , 0 , 0 },
   { 0 , 0 , 0 , 1 , 0 , 1 , 0 },
   { 0 , 0 , 0 , 0 , 1 , 0 , 1 },
   { 1 , 0 , 0 , 0 , 0 , 1 , 0 },
*/

/*
std::vector<std::vector<int>> AdjacencyVec
{   { 0 , 7 , 9 , 0 , 0 , 14 },
    { 7 , 0 , 10 , 15 , 0 , 0 },
    { 9 , 10 , 0 , 11 , 0, 2 },
    { 0 , 15 , 11 , 0 , 6, 0 },
    { 0 , 0 , 0 , 6 , 0 , 9 },
    { 14, 0 , 2 , 0 , 9 , 0 },
};
*/
