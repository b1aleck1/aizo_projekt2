#include "../include/Graph.h"
#include "../include/Timer.h"

#include <iostream>


// Simple implementation of disjoint-set for Kruskal's algorithm
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
            parent[i] = i;  // Each vertex is its own parent initially
            rank[i] = 0;    // Initial rank is 0
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }

    // Find the representative (root) of the set that contains x
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Merge two sets
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return;

        // Union by rank
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

// Structure to represent an edge
struct Edge {
    int src, dest, weight;

    // For sorting edges
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Implementation of Kruskal's algorithm for MST
void kruskalMST(Graph* graph) {
    int V = graph->getVertexCount();
    Edge* edges = new Edge[graph->getEdgeCount()];

    // Collect all edges from the graph
    int edgeIndex = 0;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) { // For undirected graph, only consider upper triangle
            if (graph->hasEdge(i, j)) {
                edges[edgeIndex].src = i;
                edges[edgeIndex].dest = j;
                edges[edgeIndex].weight = graph->getEdgeWeight(i, j);
                edgeIndex++;
            }
        }
    }

    // Sort all edges in non-decreasing order of their weight
    for (int i = 0; i < edgeIndex - 1; i++) {
        for (int j = 0; j < edgeIndex - i - 1; j++) {
            if (edges[j].weight > edges[j+1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }

    // Allocate memory for MST
    Edge* mst = new Edge[V-1];

    DisjointSet ds(V);
    int mstEdgeCount = 0;
    int i = 0;

    // Process edges one by one
    while (mstEdgeCount < V - 1 && i < edgeIndex) {
        Edge next_edge = edges[i++];

        int x = ds.find(next_edge.src);
        int y = ds.find(next_edge.dest);

        // If including this edge doesn't cause a cycle, add it to MST
        if (x != y) {
            mst[mstEdgeCount++] = next_edge;
            ds.unionSets(x, y);
        }
    }

    // Print the MST
    std::cout << "Kruskal's MST:\n";
    int totalWeight = 0;
    for (i = 0; i < mstEdgeCount; i++) {
        std::cout << "Edge: " << mst[i].src << " - " << mst[i].dest
                  << ", Weight: " << mst[i].weight << std::endl;
        totalWeight += mst[i].weight;
    }
    std::cout << "Total MST Weight: " << totalWeight << std::endl;

    delete[] edges;
    delete[] mst;
}

// Function to run Kruskal's algorithm with time measurement
double runKruskalMST(Graph* graph) {
    Timer timer;

    timer.startTimer();
    kruskalMST(graph);
    timer.stopTimer();

    return timer.getElapsedMilliseconds();
}
