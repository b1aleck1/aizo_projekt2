#ifndef APPLICATION_H
#define APPLICATION_H

#include "Config.h"
#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Timer.h"

class Application {
private:
    Config config;
    MatrixGraph* matrixGraph;
    ListGraph* listGraph;
    Timer timer;

    bool loadGraphFromFile(const char* filename);
    bool generateRandomGraph(int vertices, double density);

    void runMSTPrim(Graph* graph);
    void runMSTKruskal(Graph* graph);
    void runSPDijkstra(Graph* graph, int source, int destination);
    void runSPBellmanFord(Graph* graph, int source, int destination);
    void runPerformanceTests();

public:
    Application();
    ~Application();

    void run();
};

#endif // APPLICATION_H
