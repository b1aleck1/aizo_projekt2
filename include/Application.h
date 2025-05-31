#pragma once

#include "Config.h"
#include "MatrixGraph.h"
#include "ListGraph.h"

class Application {

public:
    Application();
    ~Application();
    void run();

private:
    Config config;
    MatrixGraph* matrixGraph;
    ListGraph* listGraph;

    bool loadGraphFromFile(const std::string& filename);
    void generateGraph();
    void runAlgorithms();
    void runPerformanceTests();
    void displayGraphs();
};
