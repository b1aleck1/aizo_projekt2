#ifndef PRIM_H
#define PRIM_H

#include "Graph.h"
#include "MinHeap.h"

class Prim {
private:
    Graph* graph;
    int* parent;
    int* key;
    bool* inMST;
    int totalCost;

public:
    Prim();                          // Domyślny konstruktor
    ~Prim();

    void run(Graph* graph);          // Główna funkcja uruchamiająca algorytm
    void displayResult() const;      // Wyświetlenie wyniku
};

#endif // PRIM_H
