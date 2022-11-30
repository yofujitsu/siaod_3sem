#include <iostream>
#include <string>
#include "Graph.h"
#include "Graph.cpp"

using namespace std;

int main()
{
    system("chcp 65001");
    setlocale(0, "rus");
    int n, a, b, w;

    cout << "Количество узлов: ";
    cin >> n;

    cout << "Количество граней: ";
    int e;
    cin >> e;

    Graph graph(n);

    int menu = -1;
    while (true) {
        cout << "Меню: " << endl;
        cout << "1) Ввод значений графа." << endl;
        cout << "2) Определить мосты графа." << endl;
        cout << "3) Построение остовного дерева алгоритмом Крускала + вывод." << endl;
        cout << "4) Вывод дерева на экран." << endl;
        cout << "0) Выход." << endl;
        cin >> menu;
        switch (menu) {
        case 1:
            cout << "Введите значения графа: " << endl;
            for (int i = 0; i < e; i++)
            {
                cin >> a;
                cin >> b;
                cin >> w;
                graph.addEdge(a, b, w);

            }
            break;
        case 2:
            cout << "Нахождение мостов в графе: " << endl;
            graph.findBridges();
            cout << "Вывод списка смежных вершин" << endl;
            graph.printGraphList();
            graph.toGraphviz("graph.gv");
            break;
        case 3: {
            Graph graph2 = graph.Kruksal();
            graph2.toGraphviz("graphKruksal.gv");

            cout << "Алгоритм Крускала: " << endl;
            graph2.printTree();
            break;
        }
        case 4:
            graph.printTree();
            break;
        case 0:
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}