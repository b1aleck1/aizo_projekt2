#include "../include/Application.h"
#include "../include/Timer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> // Dodane do obsługi folderu results

// Deklaracje zewnętrznych funkcji (algorytmów i generatora):
extern double runPrimMST(Graph* graph);
extern double runKruskalMST(Graph* graph);
extern double runDijkstraSP(Graph* graph, int src, int dest);
extern double runBellmanFordSP(Graph* graph, int src, int dest);
extern void generateConnectedGraph(Graph* graph, int vertices, double density);

Application::Application()
    : matrixGraph(nullptr), listGraph(nullptr) {}

Application::~Application() {
    delete matrixGraph;
    delete listGraph;
}

void Application::run() {
    // 1. Wczytanie konfiguracji
    if (!config.loadConfigFromFile("./data/config.txt")) {
        std::cerr << "Error loading configuration file. Using default values.\n";
    }

    // --- Debug: wypisanie załadowanych opcji ---
    std::cout << "\n=== Configuration Loaded ===\n";
    std::cout << "[DEBUG] Problem Type: "
              << (config.getProblemType() == MST ? "MST" : "SP") << "\n";
    std::cout << "[DEBUG] Graph File: '" << config.getInputFile() << "'\n";
    std::cout << "[DEBUG] Vertices (if random): " << config.getVertexCount() << "\n";
    std::cout << "[DEBUG] Density (if random): " << config.getDensity() << "\n";
    std::cout << "[DEBUG] Use Matrix: "
              << (config.isUseMatrixRepresentation() ? "true" : "false") << "\n";
    std::cout << "[DEBUG] Use List: "
              << (config.isUseListRepresentation() ? "true" : "false") << "\n";
    std::cout << "[DEBUG] Display Graph: "
              << (config.isShowGraph() ? "true" : "false") << "\n";
    std::cout << "[DEBUG] Run Performance Tests: "
              << (config.isRunPerformanceTests() ? "true" : "false") << "\n";
    if (config.getProblemType() == SP) {
        std::cout << "[DEBUG] Source Vertex: " << config.getSourceVertex() << "\n";
        std::cout << "[DEBUG] Destination Vertex: " << config.getDestinationVertex() << "\n";
    }
    std::cout << "==========================\n\n";

    // 2. Wczytanie grafu z pliku lub generowanie losowego
    if (!config.getInputFile().empty()) {
        std::cout << "[INFO] Graph file specified. Attempting to load graph.\n";
        if (!loadGraphFromFile(config.getInputFile())) {
            std::cerr << "Failed to load graph from file. Please check the file path, existence, and format.\n";
            return;
        }
    } else {
        std::cout << "[INFO] No graph file specified in config. Generating a random graph.\n";
        generateGraph();
    }

    // 3. Wyświetlenie grafu, jeśli wymaga konfiguracja
    if (config.isShowGraph()) {
        displayGraphs();
    }

    // 4. Uruchomienie wybranych algorytmów
    runAlgorithms();

    // 5. Jeśli włączone, wykonujemy testy wydajnościowe
    if (config.isRunPerformanceTests()) {
        std::cout << "\n=== Performance Tests ===\n";
        runPerformanceTests();
    }
}

bool Application::loadGraphFromFile(const std::string& filename) {
    std::cout << "[DEBUG] Attempting to open graph file: '" << filename << "'\n";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open graph file: '" << filename
                  << "'. Verify file path, permissions, and existence.\n";
        return false;
    }
    std::cout << "[DEBUG] Graph file successfully opened.\n";

    int numEdges, numVertices;
    if (!(file >> numEdges >> numVertices)) {
        std::cerr << "[ERROR] Failed to read number of edges and vertices from '"
                  << filename << "'. File might be empty, corrupted, or in wrong format.\n";
        file.close();
        return false;
    }
    std::cout << "[DEBUG] Read " << numVertices << " vertices and " << numEdges
              << " edges from file.\n";

    // (Re)inicjalizacja obiektów grafów
    if (config.isUseMatrixRepresentation()) {
        delete matrixGraph;
        matrixGraph = new MatrixGraph(numVertices, config.getProblemType() == SP);
    }
    if (config.isUseListRepresentation()) {
        delete listGraph;
        listGraph = new ListGraph(numVertices, config.getProblemType() == SP);
    }

    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        if (!(file >> src >> dest >> weight)) {
            std::cerr << "[ERROR] Failed to read edge " << i + 1
                      << " from '" << filename << "'. File might be incomplete or corrupted.\n";
            file.close();
            return false;
        }
        if (matrixGraph) matrixGraph->addEdge(src, dest, weight);
        if (listGraph)   listGraph->addEdge(src, dest, weight);
    }
    std::cout << "[DEBUG] Successfully loaded all " << numEdges << " edges from file.\n";

    file.close();
    return true;
}

void Application::generateGraph() {
    int v = config.getVertexCount();
    double d = config.getDensity();
    std::cout << "[INFO] Generating random graph with " << v << " vertices and density "
              << d << ".\n";

    if (config.isUseMatrixRepresentation()) {
        delete matrixGraph;
        matrixGraph = new MatrixGraph(v, config.getProblemType() == SP);
        generateConnectedGraph(matrixGraph, v, d);
    }

    if (config.isUseListRepresentation()) {
        delete listGraph;
        listGraph = new ListGraph(v, config.getProblemType() == SP);
        generateConnectedGraph(listGraph, v, d);
    }
    std::cout << "[DEBUG] Random graph generation complete.\n";
}

void Application::displayGraphs() {
    std::cout << "\n=== Graph Display ===\n";
    if (matrixGraph) {
        std::cout << "\n--- Matrix Representation ---\n";
        matrixGraph->display();
    }
    if (listGraph) {
        std::cout << "\n--- List Representation ---\n";
        listGraph->display();
    }
    std::cout << "=======================\n";
}

void Application::runAlgorithms() {
    if (config.getProblemType() == MST) {
        std::cout << "\n=== Running MST Algorithms ===\n";
        if (config.isRunPrim()) {
            std::cout << "\n--- Prim's Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runPrimMST(matrixGraph) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runPrimMST(listGraph) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Prim's Algorithm not enabled in config.\n";
        }

        if (config.isRunKruskal()) {
            std::cout << "\n--- Kruskal's Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runKruskalMST(matrixGraph) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runKruskalMST(listGraph) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Kruskal's Algorithm not enabled in config.\n";
        }
    }
    else if (config.getProblemType() == SP) {
        int src = config.getSourceVertex();
        int dest = config.getDestinationVertex();
        std::cout << "\n=== Running Shortest Path Algorithms (Source: "
                  << src << ", Destination: " << dest << ") ===\n";

        if (config.isRunDijkstra()) {
            std::cout << "\n--- Dijkstra's Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runDijkstraSP(matrixGraph, src, dest) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runDijkstraSP(listGraph, src, dest) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Dijkstra's Algorithm not enabled in config.\n";
        }
        if (config.isRunBellmanFord()) {
            std::cout << "\n--- Bellman-Ford Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runBellmanFordSP(matrixGraph, src, dest) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runBellmanFordSP(listGraph, src, dest) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Bellman-Ford Algorithm not enabled in config.\n";
        }
    }
}

// ===========================================================
// === Zmieniona implementacja testów wydajnościowych ===
// ===========================================================
void Application::runPerformanceTests() {
    // Tworzenie folderu results, jeśli nie istnieje
    std::filesystem::create_directories("./results");

    std::ofstream outFile("./results/performance_results.csv");
    outFile << "TypGrafu,Reprezentacja,Wierzchołki,Gęstość,Algorytm,ŚredniCzas\n";

    int vertexCounts[] = {10, 50, 100, 200, 300, 400, 500};
    double densities[] = {0.25, 0.50, 0.99};
    int trials = 3;

    int totalSteps = 2 * 7 * 3 * 2 * trials; // problemType x vertexCounts x densities x repr x trials
    int currentStep = 0;
    int lastPercent = -1;

    std::cout << "[INFO] Rozpoczęto testy wydajnościowe...";
    std::cout.flush();

    for (int problemType = 0; problemType <= 1; ++problemType) {
        for (int i = 0; i < (int)(sizeof(vertexCounts) / sizeof(vertexCounts[0])); ++i) {
            int V = vertexCounts[i];
            for (int j = 0; j < (int)(sizeof(densities) / sizeof(densities[0])); ++j) {
                double D = densities[j];
                for (int rep = 0; rep <= 1; ++rep) {
                    double sumPrim = 0, sumKruskal = 0;
                    double sumDijkstra = 0, sumBellman = 0;

                    for (int t = 0; t < trials; ++t) {
                        if (rep == 0) {
                            delete matrixGraph;
                            matrixGraph = new MatrixGraph(V, (problemType == 1));
                            generateConnectedGraph(matrixGraph, V, D);

                            if (problemType == 0) {
                                sumPrim     += runPrimMST(matrixGraph);
                                sumKruskal  += runKruskalMST(matrixGraph);
                            } else {
                                int src = 0, dst = V - 1;
                                sumDijkstra += runDijkstraSP(matrixGraph, src, dst);
                                sumBellman  += runBellmanFordSP(matrixGraph, src, dst);
                            }
                        } else {
                            delete listGraph;
                            listGraph = new ListGraph(V, (problemType == 1));
                            generateConnectedGraph(listGraph, V, D);

                            if (problemType == 0) {
                                sumPrim     += runPrimMST(listGraph);
                                sumKruskal  += runKruskalMST(listGraph);
                            } else {
                                int src = 0, dst = V - 1;
                                sumDijkstra += runDijkstraSP(listGraph, src, dst);
                                sumBellman  += runBellmanFordSP(listGraph, src, dst);
                            }
                        }

                        currentStep++;
                        int percent = (currentStep * 100) / totalSteps;
                        if (percent != lastPercent && percent % 5 == 0) {
                            std::cout << "\r[INFO] Postęp: " << percent << "%  ";
                            std::cout.flush();
                            lastPercent = percent;
                        }
                    }

                    std::string typ     = (problemType == 0) ? "MST" : "SP";
                    std::string repr    = (rep == 0) ? "Matrix" : "List";

                    if (problemType == 0) {
                        outFile << typ << "," << repr << "," << V << "," << D
                                << ",Prim,"     << (sumPrim    / trials) << "\n";
                        outFile << typ << "," << repr << "," << V << "," << D
                                << ",Kruskal,"  << (sumKruskal / trials) << "\n";
                    } else {
                        outFile << typ << "," << repr << "," << V << "," << D
                                << ",Dijkstra,"     << (sumDijkstra / trials) << "\n";
                        outFile << typ << "," << repr << "," << V << "," << D
                                << ",BellmanFord,"  << (sumBellman  / trials) << "\n";
                    }
                }
            }
        }
    }

    std::cout << "\r[INFO] Testy zakończone (100%)      \n";
    std::cout << "[INFO] Wyniki zapisano do: ./results/performance_results.csv\n";
    outFile.close();
}
