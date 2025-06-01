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
    Prim();
    ~Prim();

    void run(Graph* graph);
    void displayResult() const;
};

#endif // PRIM_H
