#include "MyGraph.h"

using namespace std;

MyGraph_1_0::MyGraph_1_0(string filename_)
{
    ProcessInputDataForGraph(filename_);
}

//-----------------описание метода----------------//
/*
Обход в ширину, т.е. по родителям.
Нужно:
1. вектор статуса вершин(посещен или нет) равный размеру матрицы инцедентности по горизонтали (одномаерность),
чтобы при проверке потомков каждой последующей верешниы добавлять только не найденные. Пример: Из вершины 1 попадаем
в 2, 3 и 7. Помечаем их найденными. Далее переходим на вершину 2. Она ведет в уже найденные 1 и 3 и не найденную 4.
В очередь добавляем только 4-ю, ибо 2 и 3я уже там.
2. Нужна очередь вершин. Принцип заполнения - в цикле фор от 0 до размера вектора статуса вершины(7 в нашем случае)
заполняем в ширину, т.е. горизонтально. Т.е. в наешм примере после прохождения первой итерации вершины в очереди будут
1, 2, 6 (нумерация с 0), что соответствует первому горизонтальному сечению. Затем 2, 6, 3 и т.д.
*/
void MyGraph_1_0::TraverseAndSearchPathBFS(int Vertex_)
{
    Edge edge{};
    --Vertex_;
    m_VerticiesStatus.clear();
    m_VerticiesStatus.resize(m_VerticiesCount, StepState::NOTFOUND); // все вершины не найдены пока

    // первая вершина добавляется в очередь в конструкторе
    while(!m_VerticiesQueue.empty())
    {
        int Vertex = m_VerticiesQueue.front();
        m_VerticiesQueue.pop();
        m_VerticiesStatus[Vertex] = StepState::VISITED;

        const size_t size = m_VerticiesStatus.size();
        for (size_t i = 0; i < size; ++i)
        {
            try
            {
                if (m_AdjenceMatrix.at(Vertex).at(i) == 1 && m_VerticiesStatus[i] == StepState::NOTFOUND)
                {
                    m_VerticiesQueue.push(i);
                    m_VerticiesStatus[i] = StepState::FOUND;

                    edge.From = Vertex;
                    edge.To = i;
                    m_EdgesStack.push(edge);
                    if (Vertex == Vertex_)
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
        m_GraphVec.push_back(Vertex + 1);
    }
    SearchBFS(Vertex_);
}

void MyGraph_1_0::TraverseAndSearchPathDFS(int Vertex_) // lexicographical
{
    Edge edge{};
    --Vertex_;
    m_VerticiesStatus.clear();
    m_VerticiesStatus.resize(m_VerticiesCount, StepState::NOTFOUND); // все вершины не найдены пока

    // первая вершина добавляется в стек в конструкторе.
    while (!m_VerticiesStack.empty())
    {
        int vertex = m_VerticiesStack.top();
        m_VerticiesStack.pop();
        if (m_VerticiesStatus[vertex] == StepState::VISITED)
            continue;

        m_VerticiesStatus[vertex] = StepState::VISITED;

        for (int i = m_VerticiesStatus.size() - 1; i >= 0; --i)
        {
            try
            {
                if (m_AdjenceMatrix[vertex].at(i) == 1 && m_VerticiesStatus[i] == StepState::NOTFOUND)
                {
                    m_VerticiesStack.push(i);
                    m_VerticiesStatus[i] = StepState::FOUND;
                    edge.From = vertex;
                    edge.To = i;
                    m_EdgesStack.push(edge);
                    if (vertex == Vertex_)
                        break;
                }
            }
            catch (std::exception e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    SearchDFS(Vertex_);
}

void MyGraph_1_0::SearchBFS(int Vertex_)
{
    Edge edge;
    //++Vertex_; // нельзя. Нужно не менять значение, ибо в стеке все минус 1
    std::cout << "Path to vertex " << Vertex_ + 1 << std::endl;
    std::cout << Vertex_ + 1;
    while (!m_EdgesStack.empty())
    {
        edge = m_EdgesStack.top();
        m_EdgesStack.pop();
        if (edge.To == Vertex_)
        {
            Vertex_ = edge.From;
            //++Vertex_; // выше присвоили индекс (т.е. на один меньше)
            std::cout << " <- " << Vertex_ + 1;
        }
    }
    std::cout << std::endl;
}

void MyGraph_1_0::SearchDFS(int Vertex_)
{
    Edge edge;
    //++Vertex_; // нельзя. Нужно не менять значение, ибо в стеке все минус 1
    std::cout << "Path to vertex " << Vertex_ + 1 << std::endl;
    std::cout << Vertex_ + 1;
    while (!m_EdgesStack.empty())
    {
        edge = m_EdgesStack.top();
        m_EdgesStack.pop();
        if (edge.To == Vertex_)
        {
            Vertex_ = edge.From;
            std::cout << " <- " << Vertex_ + 1;
        }
    }
    std::cout << std::endl;
}
//----------Deikstra------------------//
void MyGraph_1_0::MakeShortestPathTo()
{
    constexpr size_t MAX_VALUE_INDEX = 10000;
    constexpr size_t MAX_VALUE_WEIGHT = 20000; // любое заранее большее, чем возможные веса ребрa, число. Для сравнения между ними. (Вспомни метод через макс.)
    m_PathWeightsSumVec.resize(m_VerticiesCount, MAX_VALUE_WEIGHT);
    vector<StepState> visited_edges_vec(m_VerticiesCount, StepState::NOTVISITED);
    int search_index;
    int min_weight;
    int weight_sum = 0;
    m_PathWeightsSumVec[0] = 0;

    do
    {
        search_index = MAX_VALUE_INDEX; //нужно постоянно инициализиривать тут, чтобы выполнялось условие выхода
        min_weight = MAX_VALUE_WEIGHT; // изначально всегда максимальное число

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
                if (m_AdjenceMatrix[search_index][i] > 0)
                {
                    weight_sum = min_weight + m_AdjenceMatrix[search_index][i];
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
}

void MyGraph_1_0::CreateWeightedGraphFromInputFile(ifstream & f_)
{
    int VertexFrom = 0;
    int	VertexTo = 0;
    int EdgeWeight = 0;
    int GraphSize = 0;
    string InputStatus;
    vector<int> VerticiesTo_vec;

    f_ >> GraphSize;
    m_AdjenceMatrix.resize(GraphSize);
    for (int i = 0; i < GraphSize; ++i)
    {
        m_AdjenceMatrix[i].resize(GraphSize);
    }

    m_VerticiesQueue.push(0); // первая вершина в очереднь. Равно нулю ибо в себя не приходит. Поиск в ширину. Идем по узлам, поэтому удаляется первая же.
    m_VerticiesStack.push(0); // первая вершина в стек. Поиск в глубину. Удаляетя последняя добавленная.
    m_VerticiesCount = GraphSize;

    for (int i = 0; i < GraphSize; ++i)
    {
        while (VertexTo != -1)
        {
            f_ >> VertexTo;  //f.ppek()
            if (VertexTo != -1)
            {
                f_ >> EdgeWeight;
                m_AdjenceMatrix[i][VertexTo - 1] = EdgeWeight;
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

    m_AdjenceMatrix.resize(GraphSize);
    for (int i = 0; i < GraphSize; ++i)
    {
        m_AdjenceMatrix[i].resize(GraphSize);
    }

    m_VerticiesQueue.push(0); // первая вершина в очереднь. Равно нулю ибо в себя не приходит. Поиск в ширину. Идем по узлам, поэтому удаляется первая же.
    m_VerticiesStack.push(0); // первая вершина в стек. Поиск в глубину. Удаляетя последняя добавленная.
    m_VerticiesCount = GraphSize;

    for (int i = 0; i < GraphSize; ++i)
    {
        while (VertexTo != -1)
        {
            f_ >> VertexTo;
            if (VertexTo != -1)
            {
                m_AdjenceMatrix[i][VertexTo - 1] = 1;
            }
        }
        VertexTo = 0;
    }
}

void MyGraph_1_0::PrintGraph()
{
    for (const auto & Vertices : m_GraphVec)
        std::cout << Vertices << std::endl;
    std::cout << std::endl;
}

void MyGraph_1_0::PrintTheShortestPathInWeightedGraph()
{
    cout << "The shortest path through all vertices is: ";

    for(const auto & path : m_PathWeightsSumVec)
    {
        cout << path << ' ';
    }
    cout << endl;
}

void MyGraph_1_0::ProcessAndPrintShortestPath()
{
    vector<int> shortest_path_vec(6);
    int end_index = shortest_path_vec.size() - 2; //идем с конца! индекс последней вершины
    shortest_path_vec[0] = end_index + 1; // Идем с конца! Последняя вершина
    int iterator = 1;
    int weight = m_PathWeightsSumVec[end_index]; // берем вес искомого ребара!!! ПОПРОБОВАТЬ ПЕРЕДАТЬ КАК ПАРАМЕТР

    while(end_index != 0)
    {
        for(int i = 0; i < m_VerticiesCount; ++i)
        {
            if(m_AdjenceMatrix[i][end_index] != 0)
            {
                int backward_sum = weight - m_AdjenceMatrix[i][end_index];
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
    copy(shortest_path_vec.rbegin() + 2, shortest_path_vec.rend(), ostream_iterator<int>(cout, " ") );
    cout << endl;
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

adjency matrix

   { 0 , 1 , 1 , 0 , 0 , 0 , 1 },
   { 1 , 0 , 1 , 1 , 0 , 0 , 0 },
   { 1 , 1 , 0 , 0 , 0 , 0 , 0 },
   { 0 , 1 , 0 , 0 , 1 , 0 , 0 },
   { 0 , 0 , 0 , 1 , 0 , 1 , 0 },
   { 0 , 0 , 0 , 0 , 1 , 0 , 1 },
   { 1 , 0 , 0 , 0 , 0 , 1 , 0 },
*/

/*
std::vector<std::vector<int>> AdjecentVect
{   { 0 , 7 , 9 , 0 , 0 , 14 },
    { 7 , 0 , 10 , 15 , 0 , 0 },
    { 9 , 10 , 0 , 11 , 0, 2 },
    { 0 , 15 , 11 , 0 , 6, 0 },
    { 0 , 0 , 0 , 6 , 0 , 0 },
    { 14, 0 , 2 , 0 , 9 , 0 },
};
*/
