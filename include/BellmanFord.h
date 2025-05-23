#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "Graph.h"

class BellmanFord {
public:
    void run(Graph* graph, int src, int dest);
    void displayResult() const;
};

#endif // BELLMANFORD_H
