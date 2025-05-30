#ifndef PRIM_H
#define PRIM_H

#include "Graph.h"

class Prim {
public:
    void run(Graph* graph);
    void displayResult() const;

private:
    static int* mstParent;
    static int totalWeight;
    static int vertexCount;
};

#endif // PRIM_H
