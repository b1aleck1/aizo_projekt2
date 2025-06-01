#include "../include/BellmanFord.h"
#include <climits>
#include <iostream>

// Statyczne pola przechowujące wyniki i stan
int* BellmanFord::distances = nullptr;
int* BellmanFord::previous = nullptr;
int BellmanFord::vertexCount = 0;
int BellmanFord::start = -1;
int BellmanFord::end = -1;

// Główna funkcja algorytmu Bellmana-Forda
void BellmanFord::run(Graph* graph, int startVertex, int endVertex) {
    start = startVertex;
    end = endVertex;
    vertexCount = graph->getVertexCount();

    // Alokacja tablic dla odległości i poprzedników
    int* dist = new int[vertexCount];
    int* prev = new int[vertexCount];

    // Inicjalizacja: wszystkie odległości jako nieskończone, brak poprzedników
    for (int i = 0; i < vertexCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[start] = 0; // Odległość do wierzchołka startowego to 0

    // Relaksacja wszystkich krawędzi (V - 1) razy
    for (int i = 1; i <= vertexCount - 1; i++) {
        for (int u = 0; u < vertexCount; u++) {
            int neighborCount = graph->getNeighborCount(u);
            for (int j = 0; j < neighborCount; j++) {
                int v = graph->getNeighbor(u, j);
                int weight = graph->getEdgeWeight(u, v);
                if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }
    }

    // Sprawdzenie cyklu o ujemnej wadze
    for (int u = 0; u < vertexCount; u++) {
        int neighborCount = graph->getNeighborCount(u);
        for (int j = 0; j < neighborCount; j++) {
            int v = graph->getNeighbor(u, j);
            int weight = graph->getEdgeWeight(u, v);
            if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                std::cout << "Graph contains a negative weight cycle\n";
                delete[] dist;
                delete[] prev;
                return;
            }
        }
    }

    // Zapisanie wyników do pól statycznych
    if (distances) delete[] distances;
    if (previous) delete[] previous;
    distances = dist;
    previous = prev;
}

// Funkcja wyświetlająca wynik działania algorytmu Bellmana-Forda
void BellmanFord::displayResult() const {
    std::cout << "Shortest path from " << start << " to " << end << ": ";
    if (!distances || distances[end] == INT_MAX) {
        std::cout << "NO PATH\n";
        return;
    }

    std::cout << distances[end] << "\nPath: ";

    int* path = new int[vertexCount];
    int temp = end, length = 0;

    // Rekonstrukcja ścieżki od końca
    while (temp != -1) {
        path[length++] = temp;
        temp = previous[temp];
    }

    // Wyświetlenie ścieżki w poprawnej kolejności
    for (int i = length - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i > 0) std::cout << " -> ";
    }
    std::cout << "\n";

    delete[] path;
}
