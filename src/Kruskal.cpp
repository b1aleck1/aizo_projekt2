#include "../include/Kruskal.h"
#include <iostream>

// ===== STRUKTURA DO UNION-FIND =====
// Struktura reprezentująca podzbiory z rodzicem i rangą (dla optymalizacji)
struct Subset {
    int parent, rank;
};

// ===== WŁASNY QUICKSORT =====
// Funkcja zamieniająca miejscami dwie krawędzie
static void swap(Edge &a, Edge &b) {
    Edge temp = a;
    a = b;
    b = temp;
}

// Funkcja dzieląca tablicę na części wokół pivotu (waga krawędzi)
static int partition(Edge arr[], int low, int high) {
    int pivot = arr[high].weight;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].weight < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Rekurencyjne sortowanie szybkie krawędzi wg wagi
static void quicksort(Edge arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}
// ============================

// Znajdź reprezentanta zbioru z optymalizacją ścieżki
static int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Połącz dwa zbiory według rangi
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

// ===== STATYCZNE POLA =====
Edge* Kruskal::mst = nullptr;   // Tablica przechowująca krawędzie MST
int Kruskal::mstSize = 0;       // Rozmiar MST
int Kruskal::totalWeight = 0;   // Całkowity koszt MST

// ===== GŁÓWNA FUNKCJA ALGORYTMU KRUSKALA =====
void Kruskal::run(Graph* graph) {
    int V = graph->getVertexCount();
    int E = graph->getEdgeCount();
    Edge* edges = new Edge[E];
    int edgeIndex = 0;

    // Pobierz wszystkie krawędzie z grafu
    for (int u = 0; u < V; u++) {
        for (int v = u + 1; v < V; v++) {
            int w = graph->getEdgeWeight(u, v);
            if (w > 0) {
                edges[edgeIndex++] = {u, v, w};
            }
        }
    }

    // Posortuj krawędzie wg wagi rosnąco
    quicksort(edges, 0, edgeIndex - 1);

    // Inicjalizacja zbiorów disjoint-set
    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge* result = new Edge[V - 1]; // MST może mieć maksymalnie V-1 krawędzi
    int e = 0;  // licznik krawędzi MST

    // Przetwarzaj krawędzie w kolejności rosnącej wagi
    for (int i = 0; i < edgeIndex && e < V - 1; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int set_u = find(subsets, u);
        int set_v = find(subsets, v);

        // Jeśli nie tworzą cyklu, dodaj krawędź do MST i połącz zbiory
        if (set_u != set_v) {
            result[e++] = edges[i];
            unite(subsets, set_u, set_v);
        }
    }

    // Zapisz MST i jego rozmiar oraz oblicz sumę wag
    mst = result;
    mstSize = e;
    totalWeight = 0;
    for (int i = 0; i < e; i++)
        totalWeight += mst[i].weight;

    delete[] edges;
    delete[] subsets;
}

// ===== WYŚWIETLANIE WYNIKÓW MST =====
void Kruskal::displayResult() const {
    std::cout << "Edges MST (Kruskal):\n";
    for (int i = 0; i < mstSize; i++) {
        std::cout << mst[i].src << " - " << mst[i].dest << " (" << mst[i].weight << ")\n";
    }
    std::cout << "Total MST cost: " << totalWeight << "\n";
}
