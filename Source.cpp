//вариант 2 Иванов Евегний список смежности

#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

// Структура данных для хранения ребра Graph
template<typename Type1, typename Type2>
struct Edge {
    Type1 src, dest;
    Type2 weight;
};


// Класс для представления graphического объекта
template<typename Type1, typename Type2>
class Graph
{
public:
    // вектор векторов Pair для представления списка смежности
    map<Type1, list<pair<Type1, Type2>>> adjList;

    // Конструктор Graphа
    Graph(list<Edge<Type1, Type2>> const& edges = { {} })
    { 
        
        // добавляем ребра в ориентированный graph
        for (auto& edge : edges)
        {
            Type1 src = edge.src;
            Type1 dest = edge.dest;
            Type2 weight = edge.weight;

            // вставляем в конце
            adjList[src].push_back(make_pair(dest, weight));
        }
    }


    //конструктор копирования
    Graph(Graph &tmp)
    {
        adjList = tmp.adjList;
    }

    //конструктор перемещения
    Graph(Graph &&tmp) 
    {
        adjList = tmp.adjList;
        tmp.adjList.clear();
    }

    Graph& operator = (const Graph& tmp) {
        adjList = tmp.adjList;
        return *this;
    }

    Graph& operator = (Graph&& tmp)
    {
        if (this != &tmp) {
            adjList = tmp.adjList;
            tmp.adjList.clear();
        }
        return *this;
    }

    bool empty() {
        return(adjList.empty());
    }

    size_t size() {
        return(adjList.size());
    }

    void clear() {
        adjList.clear();
    }

    void swap(Graph& tmp) {
        adjList.swap(tmp.adjList);
    }

    auto begin() {
        return(adjList.begin());
    }

    auto cbegin() {
        return(adjList.cbegin());
    }

    auto end() {
        return(adjList.end());
    }

    auto cend() {
        return(adjList.cend());
    }

    size_t degree_in(Type1 n) {
        int col = 0;
        try {
            for (auto i : adjList)
            {
                for (auto v = i.second.begin(); v != i.second.end(); ++v) {
                    if ((*v).first == n)
                        col++;
                }
            }
            if (!col) {
                exception error("mismatched sizes");
                throw error;
            }
        }
        catch (exception& err) {
            cout << err.what() << "\n";
        }
        return col;
    }

    size_t degree_out(Type1 n) {
        int col = 0;
        try {
            for (auto i : adjList)
            {
                for (auto v = i.second.begin(); v != i.second.end(); ++v) {
                    if ((i).first == n)
                        col++;
                }
            }
            if (!col) {
                exception error("mismatched sizes");
                throw error;
            }
        }
        catch (exception& err) {
            cout << err.what() << "\n";
        }
        return col;
    }

    bool loop(int n) {
        int col = 0;
        try {
            for (auto i : adjList)
            {
                for (auto v = i.second.begin(); v != i.second.end(); ++v) {
                    if ((i).first == (*v).first && (*v).first == n)
                        col++;
                }
            }
            if (!col) {
                exception error("mismatched sizes");
                throw error;
            }
        }
        catch (exception& err) {
            cout << err.what() << "\n";
        }
        return (0 != col);
    }

    auto insert_node(Type1 tmp1, Type1 tmp2, Type2 tmp3) {
        list <pair<Type1, Type2>> tmp4 = { make_pair(tmp2, tmp3) };
        return ( adjList.insert( {tmp1, tmp4} ) );
        //adjList[src].push_back(make_pair(dest, weight));
    }

    auto insert_edge(Type1 key_from, Type1 key_to, Type2 weight) {
        bool found = true;
        try {
            if (!adjList.count(key_from) || !adjList.count(key_to)) {
                found = false;
                exception error("mismatched sizes");
                throw error;
            }            
        }
        catch (exception& err) {
            cout << err.what() << "\n";
        }

        list <pair<Type1, Type2>> tmp = { make_pair(key_to, weight) };
        adjList[key_from].push_back(make_pair(key_to, weight));
        
        
        return (make_pair(adjList.end(), found));
        
    }

};

template<typename Type1, typename Type2>
void swap(Graph<Type1, Type2>& tmp1, Graph<Type1, Type2>& tmp2) {
    tmp1.adjList.swap(tmp2.adjList);
}


// Функция для печати представления списка смежности Graph
template<typename Type1, typename Type2>
void printGraph(Graph<Type1,Type2> const& graph)
{
    for (auto i : graph.adjList)
    {
        // Функция для печати всех соседних вершин данной вершины
        for (auto v = i.second.begin(); v != i.second.end(); ++v) {
            cout << i.first << " -> " << (*v).first << "(" << (*v).second << ")  ";
        }
        /*for (Pair v : graph.adjList[i]) {
            cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
        }*/
        cout << endl;
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    list<Edge<int, int>> edges =
    {
        // (x, y, w) —> ребро от `x` до `y` с весом `w`
        {0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {5, 4, 1}, {4, 5, 3}
    };
    // построить Graph
    Graph<int, int> graph(edges);
    // вывести представление списка смежности Graph
    cout << "graph:" << endl;
    printGraph(graph);
    cout << endl;

    Graph<int, int> graph1; //проверка дефолтного конструктора
    cout << "graph1:" << endl;
    printGraph(graph1);
    cout << endl;

    Graph<int, int> graph2(graph);
    cout << "graph2: graph2(graph)" << endl;
    printGraph(graph2); //Проверка конструктра копирования
    cout << endl;
    graph2.adjList[0].push_back(make_pair(2, 3));
    cout << endl << "Proverka" << endl;
    cout << "graph:" << endl;
    printGraph(graph);
    cout << endl << "Proverka" << endl;
    cout << "graph2: После добавления элемента" << endl;
    printGraph(graph2); //Проверка конструктра копирования
    cout << endl;

    Graph<int, int> graph5(move(graph));
    cout << "graph5: graph(move(graph))" << endl;
    printGraph(graph5); //Проверка конструктра перемещения
    cout << endl;
    cout << "graph:" << endl;
    printGraph(graph);
    cout << endl;

    graph = graph5;
    cout << "graph: graph = graph5" << endl;
    printGraph(graph);
    cout << endl;

    graph = move(graph2);
    cout << "graph: graph = move(graph2)" << endl;
    printGraph(graph);
    cout << endl;
    cout << "grap2: graph = move(graph2) Proverka" << endl;
    printGraph(graph2);
    cout << endl;

    cout << "Пустой ли graph2: " << graph2.empty() << endl;
    cout << "Пустой ли graph: " << graph.empty() << endl << endl;

    cout << "Количество узлов graph2: " << graph2.size() << endl;
    cout << "Количество узлов graph: " << graph.size() << endl << endl;

    graph.clear();
    cout << "Очищаем graph.clear():" << endl;
    printGraph(graph);
    cout << "Пустой ли graph: " << graph.empty() << endl;
    cout << "Количество узлов graph: " << graph.size() << endl << endl;


    cout << "graph.swap(graph5):" << endl;
    graph.swap(graph5);
    printGraph(graph);
    cout << "Пустой ли graph: " << graph.empty() << endl;
    cout << "Количество узлов graph: " << graph.size() << endl << endl;
    printGraph(graph5);
    cout << "Пустой ли graph5: " << graph5.empty() << endl;
    cout << "Количество узлов graph5: " << graph5.size() << endl << endl;

    cout << "swap(graph5, graph):" << endl;
    swap(graph5, graph);
    printGraph(graph);
    cout << "Пустой ли graph: " << graph.empty() << endl;
    cout << "Количество узлов graph: " << graph.size() << endl << endl;
    printGraph(graph5);
    cout << "Пустой ли graph5: " << graph5.empty() << endl;
    cout << "Количество узлов graph5: " << graph5.size() << endl << endl;

    cout << "Количество ребер входящих в 0 узел graph5: " << graph5.degree_in(0) << endl;
    cout << "Количество ребер входящих в 2 узел graph5: " << graph5.degree_in(2) << endl;
    cout << "Количество ребер входящих в 4 узел graph5: " << graph5.degree_in(4) << endl << endl;
    cout << "Количество ребер входящих в 10 узел graph5: " << graph5.degree_in(10) << endl << endl;

    cout << "Количество ребер исходящих из 0 узел graph5: " << graph5.degree_out(0) << endl;
    cout << "Количество ребер исходящих из 2 узел graph5: " << graph5.degree_out(2) << endl;
    cout << "Количество ребер исходящих из 4 узел graph5: " << graph5.degree_out(4) << endl << endl;
    cout << "Количество ребер исходящих из 10 узел graph5: " << graph5.degree_out(10) << endl << endl;


    cout << "graph5:" << endl;
    printGraph(graph5);
    cout << endl;
    cout << "Есть ли петля у graph5 в 2 узле: " << graph.loop(2) << endl << endl;
    list<Edge<int, int>> edges3 = { { 0, 0, 6 } };
    Graph<int, int> graph6(edges3);
    cout << "graph6:" << endl;
    printGraph(graph6);
    cout << endl;
    cout << "Есть ли петля у graph6 в 0 узле: " << graph6.loop(0) << endl << endl;
    cout << "Есть ли петля у graph6 в 1 узле: " << graph6.loop(1) << endl << endl;


    graph6.insert_node(1,1,1);
    cout << "graph6: После добавления вершины" << endl;
    printGraph(graph6);
    cout << endl;

    graph6.insert_edge(1, 0, 1);
    cout << "graph6: После добавления ребра 1 -> 0(1)" << endl;
    printGraph(graph6);
    cout << endl;

    graph6.insert_edge(5, 0, 1);
    cout << "graph6: После добавления ребра 5 -> 0(1)" << endl;
    printGraph(graph6);
    cout << endl;



    list<Edge<int, double>> edges1 =
    {
        // (x, y, w) —> ребро от `x` до `y` с весом `w`
        {0, 1, 6.5}, {1, 2, 7.5}, {2, 0, 5.5}, {2, 1, 4.5}, {3, 2, 10.5}, {5, 4, 1.5}, {4, 5, 3.5}
    };
    // построить Graph
    Graph<int, double> graph3(edges1);
    // вывести представление списка смежности Graph
    cout << "graph3: дробные веса" << endl;
    printGraph(graph3);
    cout << endl;

    list<Edge<double, int>> edges2 =
    {
        // (x, y, w) —> ребро от `x` до `y` с весом `w`
        {0.5, 1.5, 6}, {1.5, 2.5, 7}, {2.5, 0.5, 5}, {2.5, 1.5, 4}, {3.5, 2.5, 10}, {5.5, 4.5, 1}, {4.5, 5.5, 3}
    };
    // построить Graph
    Graph<double, int> graph4(edges2);
    // вывести представление списка смежности Graph
    cout << "graph4: дробные вершины" << endl;
    printGraph(graph4);
    cout << endl;






    return 0;
}
