cmake_minimum_required(VERSION 3.31)
project(projekt2)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekt2
        src/main.cpp
        src/Application.cpp
        src/BellmanFord.cpp
        src/Config.cpp
        src/Dijkstra.cpp
        src/Graph.cpp
        src/GraphGenerator.cpp
        src/Kruskal.cpp
        src/ListGraph.cpp
        src/MatrixGraph.cpp
        src/Prim.cpp
        src/Timer.cpp
        src/MinHeap.cpp
        src/AlgorithmsRunner.cpp
)

target_include_directories(projekt2 PRIVATE include)
