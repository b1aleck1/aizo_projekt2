#include "../include/Graph.h"
#include "../include/Timer.h"

#include <iostream>
#include <climits>

// Prosty zbiór rozłączny (disjoint set) do Kruskala
class DisjointSet {
private:
    int* parent;
    int* rank;
    int n;

public:
    DisjointSet(int n) {
        this->n = n;
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

// Struktura reprezentująca krawędź
struct Edge {
    int src, dest, weight;
};

// Zamiana dwóch krawędzi
void swapEdges(Edge& a, Edge& b) {
    Edge temp = a;
    a = b;
    b = temp;
}

// Funkcja podziału dla QuickSort
int partition(Edge* edges, int low, int high) {
    int pivot = edges[high].weight;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (edges[j].weight <= pivot) {
            i++;
            swapEdges(edges[i], edges[j]);
        }
    }
    swapEdges(edges[i + 1], edges[high]);
    return i + 1;
}

// Rekurencyjny QuickSort
void quickSortEdges(Edge* edges, int low, int high) {
    if (low < high) {
        int pi = partition(edges, low, high);
        quickSortEdges(edges, low, pi - 1);
        quickSortEdges(edges, pi + 1, high);
    }
}

// Właściwa implementacja algorytmu Kruskala
void kruskalMST(Graph* graph) {
    int V = graph->getVertexCount();
    int E = graph->getEdgeCount();
    Edge* edges = new Edge[E];

    // Pobierz wszystkie krawędzie z grafu (tylko górny trójkąt dla nieskierowanego)
    int edgeIndex = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph->hasEdge(i, j)) {
                edges[edgeIndex].src = i;
                edges[edgeIndex].dest = j;
                edges[edgeIndex].weight = graph->getEdgeWeight(i, j);
                edgeIndex++;
            }
        }
    }

    // Sortowanie krawędzi według wagi QuickSortem
    quickSortEdges(edges, 0, edgeIndex - 1);

    Edge* mst = new Edge[V - 1];
    DisjointSet ds(V);
    int mstEdgeCount = 0;
    int i = 0;

    // Budowanie MST
    while (mstEdgeCount < V - 1 && i < edgeIndex) {
        Edge next_edge = edges[i++];
        int x = ds.find(next_edge.src);
        int y = ds.find(next_edge.dest);

        if (x != y) {
            mst[mstEdgeCount++] = next_edge;
            ds.unionSets(x, y);
        }
    }

    // Wypisanie MST
    std::cout << "Kruskal's MST:\n";
    int totalWeight = 0;
    for (int k = 0; k < mstEdgeCount; k++) {
        std::cout << "Edge: " << mst[k].src << " - " << mst[k].dest
                  << ", Weight: " << mst[k].weight << "\n";
        totalWeight += mst[k].weight;
    }
    std::cout << "Total MST Weight: " << totalWeight << std::endl;

    delete[] edges;
    delete[] mst;
}

// Funkcja do pomiaru czasu działania Kruskala
double runKruskalMST(Graph* graph) {
    Timer timer;

    timer.startTimer();
    kruskalMST(graph);
    timer.stopTimer();

    return timer.getElapsedMilliseconds();
}
