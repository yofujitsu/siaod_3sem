#include "Graph.h"

Graph::Graph(int size) {
    this->size = size;
    for (int i = 0; i < size; ++i) {
        adjacent adjacent1;
        adjacent1.vertex = i;
        graph.push_back(adjacent1);
    }
}

void Graph::addEdge(int vertex1, int vertex2, int weight, bool doRepeat) {

    if (vertex1 >= size || vertex2 >= size) {
        cerr << "Error: vertex out of range" << endl;
        return;
    }

    edge newEdge;
    newEdge.vertexEdge = vertex2;
    newEdge.weight = weight;

    if (vertex1 != vertex2 and doRepeat) {
        edge newEdge2;
        newEdge2.vertexEdge = vertex1;
        newEdge2.weight = weight;
        graph[vertex2].edges.push_back(newEdge2);
    }

    graph[vertex1].edges.push_back(newEdge);

}

void Graph::printGraphList() {
    for (int i = 0; i < graph.size(); ++i) {
        cout << graph[i].vertex << ": ";
        for (int j = 0; j < graph[i].edges.size(); ++j) {
            cout << graph[i].edges[j].vertexEdge << "(" << graph[i].edges[j].weight << ") ";
        }
        cout << endl;
    }
}

void Graph::findBridges() {
    vector<int> timeIn(size, -1);
    vector<int> fup(size, -1);
    vector<bool> visited(size, false);
    vector<int> parent(size, -1);
    int timer = 0;

    for (int i = 0; i < size; ++i) {
        if (!visited[i]) {
            dfs(i, visited, timeIn, fup, parent, timer);
        }
    }
}

void Graph::dfs(int v, vector<bool>& visited, vector<int>& timeIn, vector<int>& fup, vector<int>& parent, int& timer) {
    visited[v] = true;
    timeIn[v] = fup[v] = timer++;
    for (int i = 0; i < graph[v].edges.size(); ++i) {
        int to = graph[v].edges[i].vertexEdge;
        if (to == parent[v]) {
            continue;
        }
        if (visited[to]) {
            fup[v] = min(fup[v], timeIn[to]);
        }
        else {
            parent[to] = v;
            dfs(to, visited, timeIn, fup, parent, timer);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] > timeIn[v]) {
                cout << "BRIDGE " << v << " " << to << endl;
            }
        }
    }
}

Graph Graph::Kruksal() {

    vector<edge2way> edgesKruskal;

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].edges.size(); ++j) {
            edge2way edge;
            edge.vertex1 = graph[i].vertex;
            edge.vertex2 = graph[i].edges[j].vertexEdge;
            edge.weight = graph[i].edges[j].weight;
            edgesKruskal.push_back(edge);
        }
    }
    //удаление узлов-дупликатов
    for (int i = 0; i < edgesKruskal.size(); ++i) {
        for (int j = i + 1; j < edgesKruskal.size(); ++j) {
            if (edgesKruskal[i].vertex1 == edgesKruskal[j].vertex2 && edgesKruskal[i].vertex2 == edgesKruskal[j].vertex1) {
                edgesKruskal.erase(edgesKruskal.begin() + j);
                j--;
            }
        }
    }

    //сортировка по весу
    sort(edgesKruskal.begin(), edgesKruskal.end(), [](edge2way a, edge2way b) {
        return a.weight < b.weight;
        });

    Graph graphKruskal(size);

    //добавление узлов если они не образуют цикл
    for (int i = 0; i < edgesKruskal.size(); ++i) {
        vector<bool> visited(size, false);
        graphKruskal.addEdge(edgesKruskal[i].vertex1, edgesKruskal[i].vertex2, edgesKruskal[i].weight, true);
        if (graphKruskal.isCycled(edgesKruskal[i].vertex1, visited)) {
            cout << "CYCLE " << edgesKruskal[i].vertex1 << " " << edgesKruskal[i].vertex2 << endl;
            graphKruskal.removeEdge(edgesKruskal[i].vertex1, edgesKruskal[i].vertex2);
        }
    }
    return graphKruskal;
}

void Graph::removeEdge(int vertex1, int vertex2) {
    for (int i = 0; i < graph[vertex1].edges.size(); ++i) {
        if (graph[vertex1].edges[i].vertexEdge == vertex2) {
            graph[vertex1].edges.erase(graph[vertex1].edges.begin() + i);
            break;
        }
    }
    for (int i = 0; i < graph[vertex2].edges.size(); ++i) {
        if (graph[vertex2].edges[i].vertexEdge == vertex1) {
            graph[vertex2].edges.erase(graph[vertex2].edges.begin() + i);
            break;
        }
    }
}

//check acyclic using dfs
bool Graph::isCycled(int v, vector<bool>& visited, int parent) {
    visited[v] = true;
    for (int i = 0; i < graph[v].edges.size(); ++i) {
        int to = graph[v].edges[i].vertexEdge;
        if (to == parent) {
            continue;
        }
        if (visited[to]) {
            return true;
        }
        else {
            if (isCycled(to, visited, v)) {
                return true;
            }
        }
    }
    return false;

}

void Graph::toGraphviz(std::string filename) {
    ofstream file;
    file.open(filename);
    file << "digraph G {" << endl;
    file << "layout=circo;" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < graph[i].edges.size(); ++j) {
            file << graph[i].vertex << " -> " << graph[i].edges[j].vertexEdge << " [label=" << graph[i].edges[j].weight << "]" << endl;
        }
    }
    file << "}";
    file.close();
}

void Graph::printTree(std::string prefix, bool root, int vertex) {
    if (root) {
        PrintVisited = vector<bool>(size, false);
        cout << vertex << endl;
    }

    PrintVisited[vertex] = true;
    adjacent element = graph[vertex];
    int adj_start = element.vertex;

    for (edge ed : element.edges) {
        int adj_end = ed.vertexEdge;
        if (!PrintVisited[adj_end]) {
            cout << prefix;
            if (root) {
                cout << "|__";
            }
            else {
                cout << "|--";
            }
            cout << adj_end << endl;
            printTree(prefix + (root ? "|   " : "|   "), false, adj_end);
        }
        PrintVisited[adj_end] = true;
    }
}