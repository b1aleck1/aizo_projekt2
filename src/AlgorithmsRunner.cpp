#include "../include/AlgorithmsRunner.h"
#include "../include/Prim.h"
#include "../include/Kruskal.h"
#include "../include/Dijkstra.h"
#include "../include/BellmanFord.h"
#include "../include/Timer.h"

double runPrimMST(Graph* graph) {
    Timer timer;
    Prim prim;
    timer.start();
    prim.run(graph);
    timer.stop();
    return timer.getElapsedTime();
}

double runKruskalMST(Graph* graph) {
    Timer timer;
    Kruskal kruskal;
    timer.start();
    kruskal.run(graph);
    timer.stop();
    return timer.getElapsedTime();
}

double runDijkstraSP(Graph* graph, int source, int destination) {
    Timer timer;
    Dijkstra dijkstra;
    timer.start();
    dijkstra.run(graph, source, destination);
    timer.stop();
    return timer.getElapsedTime();
}

double runBellmanFordSP(Graph* graph, int source, int destination) {
    Timer timer;
    BellmanFord bellman;
    timer.start();
    bellman.run(graph, source, destination);
    timer.stop();
    return timer.getElapsedTime();
}
