#include "../include/Graph.h"
#include "../include/Timer.h"

#include <iostream>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Implementation of Bellman-Ford algorithm
void bellmanFordSP(Graph* graph, int src, int dest) {
    int V = graph->getVertexCount();
    int E = graph->getEdgeCount();

    // Create an array of all edges
    Edge* edges = new Edge[E];

    // Collect all edges from the graph
    int edgeIndex = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph->hasEdge(i, j)) {
                edges[edgeIndex].src = i;
                edges[edgeIndex].dest = j;
                edges[edgeIndex].weight = graph->getEdgeWeight(i, j);
                edgeIndex++;
            }
        }
    }

    // Distance array and parent array
    int* dist = new int[V];
    int* parent = new int[V];

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[src] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    bool hasNegativeCycle = false;
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        std::cout << "Graph contains negative weight cycle. Shortest path not guaranteed.\n";
    } else if (dist[dest] == INT_MAX) {
        std::cout << "No path from " << src << " to " << dest << std::endl;
    } else {
        std::cout << "Bellman-Ford Shortest Path from " << src << " to " << dest << ":\n";
        std::cout << "Total Distance: " << dist[dest] << std::endl;

        // Print the path
        std::cout << "Path: ";
        int* path = new int[V];
        int pathLen = 0;
        int current = dest;

        while (current != -1) {
            path[pathLen++] = current;
            current = parent[current];
        }

        for (int i = pathLen - 1; i >= 0; i--) {
            std::cout << path[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << std::endl;

        delete[] path;
    }

    delete[] dist;
    delete[] parent;
    delete[] edges;
}

// Function to run Bellman-Ford algorithm with time measurement
double runBellmanFordSP(Graph* graph, int src, int dest) {
    Timer timer;

    timer.startTimer();
    bellmanFordSP(graph, src, dest);
    timer.stopTimer();

    return timer.getElapsedMilliseconds();
}
