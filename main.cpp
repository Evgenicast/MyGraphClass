#include <iostream>
#include "GraphBFS.h"
#include "GraphDFS.h"

using namespace std;

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
*/




int main()
{
    size_t VerticesCNT;
    //std::cin >> VerticesCNT;
    const std::vector<std::vector<int>> AdjecencyMatrix
   {
       { 0 , 1 , 1 , 0 , 0 , 0 , 1 },
       { 1 , 0 , 1 , 1 , 0 , 0 , 0 },
       { 1 , 1 , 0 , 0 , 0 , 0 , 0 },
       { 0 , 1 , 0 , 0 , 1 , 0 , 0 },
       { 0 , 0 , 0 , 1 , 0 , 1 , 0 },
       { 0 , 0 , 0 , 0 , 1 , 0 , 1 },
       { 1 , 0 , 0 , 0 , 0 , 1 , 0 },
   };
    //------Обход в ширину--------//
    VerticesCNT = AdjecencyMatrix.size();
    MyGraph GraphBFS(VerticesCNT, AdjecencyMatrix);
    GraphBFS.PrintBFS(cout);

    //------Обход в глубину-------//
    MyGraph GraphDFS(VerticesCNT, AdjecencyMatrix);
    GraphDFS.PrintDFS(cout);

    //-------------Поиск кратчайшего пути -----------//
    MyGraph search(VerticesCNT, AdjecencyMatrix);
    cout << "Enter a vertice a path to find for ";
    search.SearchTheShortestPath(cin);
    search.PrintSearchRes();

    //-------------Поиск лексекографически первого пути -----------//
    MyGraph LexSearch(VerticesCNT, AdjecencyMatrix);
    cout << "Enter a vertice a path to find for ";
    LexSearch.SearchLexocographicalOfTheFirstPath(cin);
    LexSearch.PrintSearchRes();

    //-------------Рекурсивный поиск в глубину -----------//
    MyGraph RecursiveSearch(VerticesCNT, AdjecencyMatrix);
    RecursiveSearch.RecursiveDFS(0,6);
    RecursiveSearch.PrintSearchRes(); // не корректно работает, но для понимания норм.


	return 0;

}
