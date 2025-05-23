#include "../include/Graph.h"
#include "../include/Timer.h"

#include <iostream>
#include <climits>

// Struktura reprezentująca krawędź
struct Edge {
    int src, dest, weight;
};

// Implementacja algorytmu Bellmana-Forda
void bellmanFordSP(Graph* graph, int src, int dest) {
    int V = graph->getVertexCount();
    int E = graph->getEdgeCount();

    // Tablica wszystkich krawędzi
    Edge* edges = new Edge[E];

    // Zbieranie krawędzi z grafu
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

    int* dist = new int[V];
    int* parent = new int[V];

    // Inicjalizacja odległości i rodziców
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Relaksowanie krawędzi |V|-1 razy
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Sprawdzenie cykli ujemnych
    bool hasNegativeCycle = false;
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
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

        // Odtwarzanie ścieżki
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

// Funkcja wywoływana w main.cpp z pomiarem czasu
double runBellmanFordSP(Graph* graph, int src, int dest) {
    Timer timer;
    timer.startTimer();
    bellmanFordSP(graph, src, dest);
    timer.stopTimer();
    return timer.getElapsedMilliseconds();
}
