#include "MyGraph.h"

using namespace std;

int main()
{
    int vertex_to_find;
    cout << "Enter the vertex to find(BFS) the path to " << endl;
    cin >> vertex_to_find;

    MyGraph_1_0 MyGraph("input.txt");
    MyGraph.TraverseAndSearchPathBFS(vertex_to_find);
    MyGraph.PrintGraph();

    cout << "Enter the vertex to find(DFS) the path to " << endl;
    cin >> vertex_to_find;

    MyGraph_1_0 MyGraph0("input.txt");
    MyGraph0.TraverseAndSearchPathDFS(vertex_to_find);
    MyGraph.PrintGraph();

    MyGraph_1_0 MyGraph_1("Deikstra.txt");
    MyGraph_1.MakeShortestPathTo();
    MyGraph_1.PrintTheShortestPathInWeightedGraph();
    MyGraph_1.ProcessAndPrintShortestPath();

    MyGraph_1_0 MyGraph_2("JSON.json");
    MyGraph_2.MakeShortestPathTo();
    MyGraph_2.PrintTheShortestPathInWeightedGraph();
    MyGraph_2.ProcessAndPrintShortestPath();
    cout << "done" << endl;
    return 0;
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
    { 0 , 0 , 0 , 6 , 0 , 9},
    { 14, 0 , 2 , 0 , 9 , 0 },
};
*/

