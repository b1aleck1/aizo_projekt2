#ifndef CONFIG_H
#define CONFIG_H

#include <string>

enum ProblemType {
    MST,    // Minimum Spanning Tree
    SP      // Shortest Path
};

class Config {
private:
    ProblemType problemType;
    bool runPrim;
    bool runKruskal;
    bool runDijkstra;
    bool runBellmanFord;
    bool useMatrixRepresentation;
    bool useListRepresentation;
    std::string inputFile;
    int vertexCount;
    double density;
    bool showGraph;
    bool runPerformanceTests;
    int sourceVertex;
    int destinationVertex;

public:
    Config();
    bool loadConfigFromFile(const std::string& filename);

    // Getters
    ProblemType getProblemType() const { return problemType; }
    bool isRunPrim() const { return runPrim; }
    bool isRunKruskal() const { return runKruskal; }
    bool isRunDijkstra() const { return runDijkstra; }
    bool isRunBellmanFord() const { return runBellmanFord; }
    bool isUseMatrixRepresentation() const { return useMatrixRepresentation; }
    bool isUseListRepresentation() const { return useListRepresentation; }
    std::string getInputFile() const { return inputFile; }
    int getVertexCount() const { return vertexCount; }
    double getDensity() const { return density; }
    bool isShowGraph() const { return showGraph; }
    bool isRunPerformanceTests() const { return runPerformanceTests; }
    int getSourceVertex() const { return sourceVertex; }
    int getDestinationVertex() const { return destinationVertex; }
};

#endif // CONFIG_H
