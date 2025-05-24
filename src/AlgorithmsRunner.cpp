#include "AlgorithmsRunner.h"
#include "Timer.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

double runPrimMST(Graph* graph) {
    Timer timer;
    timer.startTimer();
    Prim prim;
    prim.run(graph);
    timer.stopTimer();
    prim.displayResult();
    return timer.getElapsedMilliseconds();
}

double runKruskalMST(Graph* graph) {
    Timer timer;
    timer.startTimer();
    Kruskal kruskal;
    kruskal.run(graph);
    timer.stopTimer();
    kruskal.displayResult();
    return timer.getElapsedMilliseconds();
}

double runDijkstraSP(Graph* graph, int src, int dest) {
    Timer timer;
    timer.startTimer();
    Dijkstra dijkstra;
    dijkstra.run(graph, src, dest);
    timer.stopTimer();
    dijkstra.displayResult();
    return timer.getElapsedMilliseconds();
}

double runBellmanFordSP(Graph* graph, int src, int dest) {
    Timer timer;
    timer.startTimer();
    BellmanFord bf;
    bf.run(graph, src, dest);
    timer.stopTimer();
    bf.displayResult();
    return timer.getElapsedMilliseconds();
}
