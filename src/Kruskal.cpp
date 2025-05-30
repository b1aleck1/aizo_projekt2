#include "../include/Kruskal.h"
#include <iostream>

struct Subset {
    int parent, rank;
};

static int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

static void unite(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

Edge* Kruskal::mst = nullptr;
int Kruskal::mstSize = 0;
int Kruskal::totalWeight = 0;

void Kruskal::run(Graph* graph) {
    int V = graph->getVertexCount();
    int E = graph->getEdgeCount();
    Edge* edges = new Edge[E];
    int edgeIndex = 0;

    for (int u = 0; u < V; u++) {
        for (int v = u + 1; v < V; v++) {
            int w = graph->getEdgeWeight(u, v);
            if (w > 0) {
                edges[edgeIndex++] = {u, v, w};
            }
        }
    }

    for (int i = 0; i < edgeIndex - 1; i++) {
        for (int j = 0; j < edgeIndex - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge* result = new Edge[V - 1];
    int e = 0;

    for (int i = 0; i < edgeIndex && e < V - 1; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int set_u = find(subsets, u);
        int set_v = find(subsets, v);

        if (set_u != set_v) {
            result[e++] = edges[i];
            unite(subsets, set_u, set_v);
        }
    }

    mst = result;
    mstSize = e;
    totalWeight = 0;
    for (int i = 0; i < e; i++)
        totalWeight += mst[i].weight;

    delete[] edges;
    delete[] subsets;
}

void Kruskal::displayResult() const {
    std::cout << "Edges MST (Kruskal):\n";
    for (int i = 0; i < mstSize; i++) {
        std::cout << mst[i].src << " - " << mst[i].dest << " (" << mst[i].weight << ")\n";
    }
    std::cout << "Total cost: " << totalWeight << "\n";
}
