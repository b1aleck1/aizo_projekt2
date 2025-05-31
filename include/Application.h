#pragma once

#include "Config.h"
#include "MatrixGraph.h"
#include "ListGraph.h"

class Application {
private:
    Config config;
    MatrixGraph* matrixGraph;
    ListGraph* listGraph;

public:
    Application();
    ~Application();
    void run();

private:
    bool loadGraphFromFile(const std::string& filename);
    void generateGraph();
    void runAlgorithms();
    void displayGraphs();
};
