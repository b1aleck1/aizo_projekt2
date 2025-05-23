#ifndef ALGORITHMSRUNNER_H
#define ALGORITHMSRUNNER_H

#include "Graph.h"

double runPrimMST(Graph* graph);
double runKruskalMST(Graph* graph);
double runDijkstraSP(Graph* graph, int src, int dest);
double runBellmanFordSP(Graph* graph, int src, int dest);

#endif // ALGORITHMSRUNNER_H
