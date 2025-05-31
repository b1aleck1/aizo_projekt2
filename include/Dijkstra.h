#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

class Dijkstra {
private:
    static int* distances;
    static int* previous;
    static int vertexCount;
    static int start;
    static int end;

    // MinHeap do zarządzania kolejką priorytetową
    class MinHeap {
    private:
        int* heap;       // tablica wierzchołków
        int* pos;        // pozycja wierzchołka w kopcu
        int* dist;       // odległości (klucze)
        int size;
        int capacity;

        void swap(int i, int j);
        void heapifyDown(int i);
        void heapifyUp(int i);

    public:
        MinHeap(int capacity, int* dist);
        ~MinHeap();

        void insert(int v);
        bool empty() const;
        int extractMin();
        void decreaseKey(int v);
        bool contains(int v) const;
    };

public:
    Dijkstra() = default;
    ~Dijkstra();

    void run(Graph* graph, int startVertex, int endVertex);
    void displayResult() const;
};

#endif // DIJKSTRA_H
