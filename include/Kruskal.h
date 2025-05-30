#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Graph.h"

struct Edge {
    int src, dest, weight;
};

class Kruskal {
public:
    void run(Graph* graph);
    void displayResult() const;

private:
    static Edge* mst;
    static int mstSize;
    static int totalWeight;
};

#endif // KRUSKAL_H
