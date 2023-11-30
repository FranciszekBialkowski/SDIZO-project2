cmake_minimum_required(VERSION 3.25)
project(projekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(projekt main/main.cpp main/Menu.cpp algorithms/Prim.cpp headers/Prim.h headers/Algorithm.h algorithms/Dijkstra.cpp headers/Dijkstra.h algorithms/Kruskal.cpp algorithms/BellmanFord.cpp headers/BellmanFord.h headers/BellmanFord.h headers/BellmanFord.h headers/BellmanFord.h headers/BellmanFord.h main/GraphGenerator.cpp headers/GraphGenerator.h)
