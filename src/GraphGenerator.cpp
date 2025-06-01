#include "../include/Graph.h"
#include <stdlib.h>
#include <time.h>

// Generowanie losowego spójnego grafu z określoną liczbą wierzchołków i gęstością
void generateConnectedGraph(Graph* graph, int vertices, double density) {
    // Najpierw tworzony jest rozpinający graf (drzewo), aby zapewnić spójność
    // Następnie dodawane są losowe krawędzie, by osiągnąć zadaną gęstość

    // Inicjalizacja generatora liczb losowych
    srand(time(NULL));

    // Generowanie drzewa rozpinającego
    bool* visited = new bool[vertices];
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    // Start od wierzchołka 0
    visited[0] = true;
    int visitedCount = 1;

    // Dodawanie krawędzi tworzących drzewo rozpinające
    while (visitedCount < vertices) {
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (visited[u] && !visited[v]) {
            graph->addEdge(u, v, rand() % 100 + 1); // Waga z zakresu 1–100
            visited[v] = true;
            visitedCount++;
        } else if (visited[v] && !visited[u]) {
            graph->addEdge(v, u, rand() % 100 + 1);
            visited[u] = true;
            visitedCount++;
        }
    }

    delete[] visited;

    // Obliczenie maksymalnej liczby krawędzi dla danego typu grafu
    int maxEdges = graph->isDirected() ? vertices * (vertices - 1) : vertices * (vertices - 1) / 2;

    // Obliczenie docelowej liczby krawędzi na podstawie gęstości
    int targetEdges = (int)(maxEdges * density);

    // Dodawanie losowych krawędzi aż do osiągnięcia zadanej gęstości
    while (graph->getEdgeCount() < targetEdges) {
        int u = rand() % vertices;
        int v = rand() % vertices;

        if (u != v && !graph->hasEdge(u, v)) {
            graph->addEdge(u, v, rand() % 100 + 1);
        }
    }
}
