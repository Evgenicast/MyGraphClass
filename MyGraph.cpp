#include "MyGraph.h"

MyGraph::MyGraph(size_t VerticesCNT, const AdjacencyMartixType & AdjecencyMatPars)
{
    m_VerticesVec.resize(VerticesCNT, StepState::NOTFOUND); // исходно все вершины равны
    m_VerticesQueue.push(0); // помещаем первую вершину в очередь(поиск в ширину)
    m_VerteciesStack.push(0); // помещаем первую вершину в очередь(поиск в глубину)
    m_AdjacencyMatPtr = &AdjecencyMatPars;
}

std::vector<int> MyGraph::MakeBFS()
{
    std::vector<int> res;
    while(!m_VerticesQueue.empty())
    {
        int Vertex = m_VerticesQueue.front();// извлекаем вершину и сохраняем ее итераторм
        // прохода по 1ому столбцу, проверяя соседей и добавляя их в очередь. Затем ниже
        // удаляется эта вершина, очередь двигается на след. самую близку вершину.
        // в конце выводим текущую вершину.

        m_VerticesQueue.pop();
        m_VerticesVec[Vertex] = StepState::VISITED; // отмечаем как посещенную

        const size_t size = m_VerticesVec.size();
        for(size_t i = 0; i < size; ++i)
        {//проверяем для нее все смежные вершины
            try
            {
                if(m_AdjacencyMatPtr->at(Vertex).at(i) == 1 && m_VerticesVec[i] == StepState::NOTFOUND )
                {
                    m_VerticesQueue.push(i);
                    m_VerticesVec[i] = StepState::FOUND;
                }
            }
            catch (...)
            {
                std::cout << "error (at) " << std::endl;
            }
        }
        res.push_back(Vertex + 1); //Vertex + 1 потому что индексы с нуля (первая вершина не 1, а ноль)
    }
    return res;
}

std::vector<int> MyGraph::MakeDFS()
{
    std::vector<int> res; const size_t size = m_VerticesVec.size() - 1; // 7ая вершина это 6-ой индекс
    while(!m_VerteciesStack.empty())
    {
        int Vertex = m_VerteciesStack.top();// извлекаем вершину и сохраняем ее итераторм
        // прохода по 1ому столбцу, проверяя соседей и добавляя их в очередь. Затем ниже
        // удаляется эта вершина, очередь двигается на след. самую близку вершину.
        // в конце выводим текущую вершину.

        m_VerteciesStack.pop();
        if(m_VerticesVec[Vertex] == StepState::VISITED)
            continue;
        m_VerticesVec[Vertex] = StepState::VISITED; // отмечаем как посещенную

        for(int i = size; i >= 0; --i)
        {//проверяем для нее все смежные вершины
            try
            {
                if(m_AdjacencyMatPtr->at(Vertex).at(i) == 1 && m_VerticesVec[i] != StepState::VISITED )
                {
                    m_VerteciesStack.push(i);
                    m_VerticesVec[i] = StepState::FOUND;
                }
            }
            catch (...)// correct! std::exception !
            {
                std::cout << "error (at) " << std::endl;
            }
        }
        res.push_back(Vertex + 1); //Vertex + 1 потому что индексы с нуля (первая вершина не 1, а ноль)
    }
    return res;
}

void MyGraph::RecursiveDFS(int beginVertex, int endVertex)
{
    m_SearchResVec.push_back(beginVertex + 1);
    m_VerticesVec[beginVertex] = StepState::FOUND;

    for(int i = 0; i < endVertex; ++i)
    {
        if(m_AdjacencyMatPtr->at(beginVertex).at(i) != 0 && m_VerticesVec[i] == StepState::NOTFOUND )
        {
            RecursiveDFS(i, endVertex);
        }
    }
}

void MyGraph::SearchTheShortestPath(std::istream & is)
{
    if(!is)
    {
        std::cout << "Error. Currpted stream" << std::endl;
        return;
    }

    Edge edge;

    int VertexToFind;
    is >> VertexToFind;
    --VertexToFind; // index and vertecies dont coincide.

    //m_VerticesQueue.push(0); // помещаем в очередь первую вершину !! не нужно, ибо в новом объекте в конструкторе

    while(!m_VerticesQueue.empty())
    {
        int CurVertex = m_VerticesQueue.front();
        m_VerticesQueue.pop();
        m_VerticesVec[CurVertex] = StepState::VISITED;

        const size_t size = m_VerticesVec.size();
        for(int i = 0; i < size; ++i)
        {
            if(m_AdjacencyMatPtr->at(CurVertex).at(i) == 1 && m_VerticesVec[i] == StepState::NOTFOUND)
            {
                m_VerticesQueue.push(i);
                m_VerticesVec[i] = StepState::FOUND;
                edge.m_Begin = CurVertex;
                edge.m_End = i; // получится расстояние, т.к. заходим сюда, если есть сосед/потомок
                m_EdgesStack.push(edge);
                if(CurVertex == VertexToFind)
                    break;
            }
        }
        //std::cout << CurVertex + 1 << std::endl;  можно вывести номера вершин(пукт черз них всех)
    }

    //--------search-------------//

    m_SearchResVec.push_back(VertexToFind + 1); // Serched vertex;
    while(!m_EdgesStack.empty())
    {
        edge = m_EdgesStack.top();
        m_EdgesStack.pop();
        if(edge.m_End == VertexToFind)
        {
            VertexToFind = edge.m_Begin;
            m_SearchResVec.push_back(VertexToFind + 1);
        }
    }
}

void MyGraph::SearchLexocographicalOfTheFirstPath(std::istream &is)
{
    if(!is)
    {
        std::cout << "Error. Currpted stream" << std::endl;
        return;
    }

    Edge edge;

    int VertexToFind;
    is >> VertexToFind;
    --VertexToFind;

    while(!m_VerteciesStack.empty())
    {
        int CurVertex = m_VerteciesStack.top();
        m_VerteciesStack.pop();
        if(m_VerticesVec[CurVertex] == StepState::VISITED)
            continue;
        m_VerticesVec[CurVertex] = StepState::VISITED; // отмечаем как посещенную

        const size_t size = m_VerticesVec.size() - 1;
        for(int i = size; i >= 0; --i)
        {
            if(m_AdjacencyMatPtr->at(CurVertex).at(i) == 1 && m_VerticesVec[i] == StepState::NOTFOUND)
            {
                m_VerteciesStack.push(i);
                m_VerticesVec[i] = StepState::FOUND;
                edge.m_Begin = CurVertex;
                edge.m_End = i; // получится расстояние, т.к. заходим сюда, если есть сосед/потомок
                m_EdgesStack.push(edge);
                if(CurVertex == VertexToFind)
                    break;
            }
        }
        //std::cout << CurVertex + 1 << std::endl;  можно вывести номера вершин(пукт черз них всех)
    }

    //--------search-------------//

    m_SearchResVec.push_back(VertexToFind + 1); // Serched vertex;
    while(!m_EdgesStack.empty())
    {
        edge = m_EdgesStack.top();
        m_EdgesStack.pop();
        if(edge.m_End == VertexToFind)
        {
            VertexToFind = edge.m_Begin;
            m_SearchResVec.push_back(VertexToFind + 1);
        }
    }

}

void MyGraph::ClearVector()
{
    m_VerticesVec.clear();
}

void MyGraph::ClearQueue()
{
    std::queue<int> emptyQue;
    std::swap(m_VerticesQueue, emptyQue);
}

void MyGraph::PrintDFS(std::ostream & os)
{
    for(const auto & Vertices : MakeDFS())
        os << Vertices << std::endl;
            os << std::endl;
}

void MyGraph::PrintBFS(std::ostream &os)
{
    for(const auto & Vertices : MakeBFS())
        os << Vertices << std::endl;
           os << std::endl;
}

void MyGraph::PrintSearchRes()
{
    std::cout << std::endl;
    if(!m_SearchResVec.empty())
    {
        auto end = m_SearchResVec.rend()-1;
        std::cout << "The way to the verice " << *end << " is: " << std::endl;
        for(auto begin = m_SearchResVec.rbegin(); begin != m_SearchResVec.rend(); ++begin)
        {
            std::cout << *begin;
            if(begin != end)
            {
                std::cout << "->";
            }
        }
        std::cout << std::endl;
    }
    //std::copy(m_SearchResVec.rbegin(), m_SearchResVec.rend(), std::ostream_iterator<int>(std::cout, "\n"));
    std::cout << std::endl;
}

void MyGraph::PrintLexSearchRes()
{
    std::cout << std::endl;
    if(!m_SearchResVec.empty())
    {
        auto end = m_SearchResVec.rend()-1;
        std::cout << "The way to the verice " << *end << " is: " << std::endl;
        for(auto begin = m_SearchResVec.rbegin(); begin != m_SearchResVec.rend(); ++begin)
        {
            std::cout << *begin;
            if(begin != end)
            {
                std::cout << "->";
            }
        }
        std::cout << std::endl;
    }
    //std::copy(m_SearchResVec.rbegin(), m_SearchResVec.rend(), std::ostream_iterator<int>(std::cout, "\n"));
    std::cout << std::endl;
}
