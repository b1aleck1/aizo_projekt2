#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include "Graph.h"
#include "Config.h"

class GraphGenerator {
public:
    // Generuje graf w zależności od konfiguracji
    static Graph* generateGraph(const Config& config, bool useMatrix);
};

#endif // GRAPHGENERATOR_H
