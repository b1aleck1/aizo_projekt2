#include "AlgorithmsRunner.h"
#include "Timer.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

double runPrimMST(Graph* graph) {
    Timer timer;
    timer.start();
    Prim prim;
    prim.run(graph);
    timer.stop();
    prim.displayResult();
    return timer.elapsedMilliseconds();
}

double runKruskalMST(Graph* graph) {
    Timer timer;
    timer.start();
    Kruskal kruskal;
    kruskal.run(graph);
    timer.stop();
    kruskal.displayResult();
    return timer.elapsedMilliseconds();
}

double runDijkstraSP(Graph* graph, int src, int dest) {
    Timer timer;
    timer.start();
    Dijkstra dijkstra;
    dijkstra.run(graph, src, dest);
    timer.stop();
    dijkstra.displayResult();
    return timer.elapsedMilliseconds();
}

double runBellmanFordSP(Graph* graph, int src, int dest) {
    Timer timer;
    timer.start();
    BellmanFord bf;
    bf.run(graph, src, dest);
    timer.stop();
    bf.displayResult();
    return timer.elapsedMilliseconds();
}
