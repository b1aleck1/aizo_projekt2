#include "../include/Config.h"
#include <fstream>
#include <string>
#include <iostream>

Config::Config()
    : problemType(MST),
      runPrim(true),
      runKruskal(true),
      runDijkstra(false),
      runBellmanFord(false),
      useMatrixRepresentation(true),
      useListRepresentation(true),
      inputFile(""),
      vertexCount(10),
      density(0.5),
      showGraph(true),
      runPerformanceTests(false),
      sourceVertex(0),
      destinationVertex(5) {
}

bool Config::loadConfigFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening config file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;

        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);

        // Trim whitespace
        auto trim = [](std::string& s) {
            s.erase(0, s.find_first_not_of(" \t"));
            s.erase(s.find_last_not_of(" \t") + 1);
        };

        trim(key);
        trim(value);

        // Configuration options
        if (key == "Problem") {
            if (value == "MST") problemType = MST;
            else if (value == "SP") problemType = SP;
        } else if (key == "LoadFromFile") {
            // Remove quotes if present
            if (value.length() > 2 && value[0] == '\"' && value[value.length() - 1] == '\"') {
                inputFile = value.substr(1, value.length() - 2);
            } else {
                inputFile = value;
            }
        } else if (key == "Vertices") {
            vertexCount = std::stoi(value);
        } else if (key == "Density") {
            density = std::stod(value);
        } else if (key == "RunPrim") {
            runPrim = (value == "true");
        } else if (key == "RunKruskal") {
            runKruskal = (value == "true");
        } else if (key == "RunDijkstra") {
            runDijkstra = (value == "true");
        } else if (key == "RunBellmanFord") {
            runBellmanFord = (value == "true");
        } else if (key == "UseMatrix") {
            useMatrixRepresentation = (value == "true");
        } else if (key == "UseList") {
            useListRepresentation = (value == "true");
        } else if (key == "DisplayGraph") {
            showGraph = (value == "true");
        } else if (key == "RunPerformanceTests") {
            runPerformanceTests = (value == "true");
        } else if (key == "Source") {
            sourceVertex = std::stoi(value);
        } else if (key == "Destination") {
            destinationVertex = std::stoi(value);
        }
    }

    file.close();
    return true;
}
