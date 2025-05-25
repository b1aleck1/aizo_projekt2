#include "../include/Kruskal.h"

struct Edge {
    int src, dest, weight;
};

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

    int mstEdges = 0;
    for (int i = 0; i < edgeIndex && mstEdges < V - 1; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int set_u = find(subsets, u);
        int set_v = find(subsets, v);

        if (set_u != set_v) {
            unite(subsets, set_u, set_v);
            ++mstEdges;
        }
    }

    delete[] edges;
    delete[] subsets;
}

void Kruskal::displayResult() const {
    // Optional
}
