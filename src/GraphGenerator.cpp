#include "../include/Graph.h"
#include <stdlib.h> // For rand()
#include <time.h>   // For time()

// Generate a random connected graph with specified number of vertices and density
void generateConnectedGraph(Graph* graph, int vertices, double density) {
    // First create a spanning tree to ensure connectivity
    // Then add random edges to achieve desired density

    // Initialize with random seed
    srand(time(NULL));

    // Generate a spanning tree
    bool* visited = new bool[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    // Start with vertex 0
    visited[0] = true;
    int visitedCount = 1;

    // Add edges to form a spanning tree
    while (visitedCount < vertices) {
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (visited[u] && !visited[v]) {
            graph->addEdge(u, v, rand() % 100 + 1); // Weight between 1-100
            visited[v] = true;
            visitedCount++;
        } else if (visited[v] && !visited[u]) {
            graph->addEdge(v, u, rand() % 100 + 1);
            visited[u] = true;
            visitedCount++;
        }
    }

    delete[] visited;

    // Calculate max edges for the given graph type
    int maxEdges = graph->isDirected() ? vertices * (vertices - 1) : vertices * (vertices - 1) / 2;

    // Calculate target number of edges based on density
    int targetEdges = (int)(maxEdges * density);

    // Add random edges until desired density is reached
    while (graph->getEdgeCount() < targetEdges) {
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (u != v && !graph->hasEdge(u, v)) {
            graph->addEdge(u, v, rand() % 100 + 1);
        }
    }
}
