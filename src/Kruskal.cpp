#include "../include/Graph.h"
#include "../include/Timer.h"
#include <iostream>
#include <climits>

struct Edge {
    int src, dest, weight;
};

class DisjointSet {
    int* parent;
    int* rank;
    int n;
public:
    DisjointSet(int n) : n(n) {
        parent = new int[n];
        rank = new int[n]();
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unionSets(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else { parent[ry] = rx; rank[rx]++; }
    }
};

void quickSortEdges(Edge* edges, int low, int high) {
    if (low >= high) return;
    int pivot = edges[high].weight, i = low - 1;
    for (int j = low; j < high; j++)
        if (edges[j].weight <= pivot)
            std::swap(edges[++i], edges[j]);
    std::swap(edges[i + 1], edges[high]);
    quickSortEdges(edges, low, i);
    quickSortEdges(edges, i + 2, high);
}

double runKruskalMST(Graph* graph) {
    int V = graph->getVertexCount(), E = graph->getEdgeCount();
    Edge* edges = new Edge[E];
    int idx = 0;

    for (int i = 0; i < V; i++)
        for (int j = i + 1; j < V; j++)
            if (graph->hasEdge(i, j)) {
                edges[idx++] = { i, j, graph->getEdgeWeight(i, j) };
            }

    quickSortEdges(edges, 0, idx - 1);

    Edge* mst = new Edge[V - 1];
    DisjointSet ds(V);
    int e = 0, i = 0;
    Timer timer;
    timer.startTimer();

    while (e < V - 1 && i < idx) {
        Edge edge = edges[i++];
        if (ds.find(edge.src) != ds.find(edge.dest)) {
            mst[e++] = edge;
            ds.unionSets(edge.src, edge.dest);
        }
    }

    timer.stopTimer();
    double duration = timer.getElapsedMilliseconds();

    int total = 0;
    for (int j = 0; j < e; j++) {
        std::cout << mst[j].src << " - " << mst[j].dest << " (waga: " << mst[j].weight << ")\n";
        total += mst[j].weight;
    }
    std::cout << "Suma wag MST: " << total << std::endl;

    delete[] edges;
    delete[] mst;
    return duration;
}
