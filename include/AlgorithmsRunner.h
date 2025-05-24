#ifndef ALGORITHMS_RUNNER_H
#define ALGORITHMS_RUNNER_H

#include "Graph.h"

double runPrimMST(Graph* graph);
double runKruskalMST(Graph* graph);
double runDijkstraSP(Graph* graph, int source, int destination);
double runBellmanFordSP(Graph* graph, int source, int destination);

#endif // ALGORITHMS_RUNNER_H
