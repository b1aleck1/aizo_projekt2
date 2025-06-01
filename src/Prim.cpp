#include "../include/Prim.h"
#include <iostream>
#include <climits>

// Konstruktor inicjalizujący wskaźniki na nullptr i koszt MST zerem
Prim::Prim() : graph(nullptr), parent(nullptr), key(nullptr), inMST(nullptr), totalCost(0) {}

// Destruktor zwalniający pamięć zaalokowaną dla tablic
Prim::~Prim() {
    delete[] parent;
    delete[] key;
    delete[] inMST;
}

// Główna funkcja uruchamiająca algorytm Prima
void Prim::run(Graph* graph) {
    this->graph = graph;
    int V = graph->getVertexCount();

    // Alokacja pamięci dla tablic potrzebnych do działania algorytmu
    parent = new int[V];
    key = new int[V];
    inMST = new bool[V];

    // Inicjalizacja tablic: klucze ustawione na nieskończoność,
    // w MST żaden wierzchołek jeszcze nie jest, rodzice -1
    for (int i = 0; i < V; ++i) {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    // Startujemy od wierzchołka 0 (klucz = 0)
    key[0] = 0;
    MinHeap heap(V);
    heap.insert(0, 0);

    // Pętla wykonująca algorytm Prima
    while (!heap.isEmpty()) {
        VertexDistance* minNode = heap.extractMin();  // Pobierz wierzchołek o najmniejszym kluczu
        int u = minNode->vertex;
        delete minNode;

        if (inMST[u]) // Jeśli wierzchołek jest już w MST, pomiń go
            continue;

        inMST[u] = true; // Dodaj wierzchołek do MST

        // Sprawdź wszystkie sąsiednie wierzchołki v
        for (int v = 0; v < V; ++v) {
            if (graph->hasEdge(u, v) && !inMST[v]) {
                int weight = graph->getEdgeWeight(u, v);
                // Jeśli znaleźliśmy mniejszą wagę krawędzi, zaktualizuj dane
                if (weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    if (heap.isInHeap(v)) {
                        heap.decreaseKey(v, weight);  // Zmniejsz klucz w kopcu
                    } else {
                        heap.insert(v, weight);        // Wstaw nowy wierzchołek do kopca
                    }
                }
            }
        }
    }

    // Oblicz całkowity koszt MST
    totalCost = 0;
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            totalCost += graph->getEdgeWeight(i, parent[i]);
        }
    }
}

// Funkcja do wyświetlania wyniku działania algorytmu
void Prim::displayResult() const {
    int V = graph->getVertexCount();
    std::cout << "MST (Prim):\n";
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i
                      << " (weight: " << graph->getEdgeWeight(i, parent[i]) << ")\n";
        }
    }
    std::cout << "Total cost: " << totalCost << "\n";
}
