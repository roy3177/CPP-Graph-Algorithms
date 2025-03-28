
# CPP Graph Algorithms

## Project Overview

This project implements a **Graph** in C++, along with classical graph algorithms:

**-Breadth-First Search(BFS):** Traveres the graph level-by-level, useful for finding shortest-paths in unweighted graphs.
Generates a tree, using a parent array.

**-Depth-First Search(DFS):** Explores the graph as deeply as possible before backtracking, useful for topological sorting, and cycle detection.
Generates a tree, using a parent array.


**-Dijkstra's Algorithm:** Finds the shortest paths from the source vertex to all other vertices in a weighted graph, and also showing distance clearly.


**-Prim's Algorithm:** Builds a Minimum Spanning Tree(MST) by gradually expanding from source vertex.

**-Kruskal's Algorithm:** Builds a Minimum Spanning Tree(MST) by selecting edges from smallest to largest, with avoiding creating cycles.



The project includes implementations of fundamental data structures:

**-Queue:** Standart FIFO queue, implemented using arrays.

**-Priority Queue:** Allows retrieving elements based on priority, implemented using a basic array.

**-Union-Find:** Data structure for disjoint sets, efficient for cennectivity checks, implemented without STL.

## Graph Class Overviwe

The graph class is responsible for representing the graph,using adjacency lists,and includes basic methods:

**-addEdge:** Create connection between two vertices with weight.

**-removeEdge:** Remove connection between two vertices.

**-print_graph:** Presenting our graph.

**-getAdjList:** Getting the vertices adjacent to a given vertex.

**-getNumVertices:** Getting the number of vertices of a given graph.

## Installation and Usage

**Compilation:** To compile-using the provided MakeFile :
```bash 
make
```
**Running the Main Program:** To execute demos and examples:
``` bash
make Main
```
**Running Tets:** To run tests, using **doctest**:
```bash
make test
```
**Memory Check(Valgrind):** To check for memory leaks:
```bash
make valgrind
```
**Cleaning Files:** To remove compile files:
```bash
make clean
```


## Project Structure

```plaintext
CPP_GRAPH
├── Algorithms
│   ├── Algorithms.cpp
│   ├── Algorithms.hpp
├── DataStructures
│   ├── PriorityQueue.cpp
│   ├── PriorityQueue.hpp
│   ├── Queue.cpp
│   ├── Queue.hpp
│   ├── UnionFind.cpp
│   ├── UnionFind.hpp
│   
├── Graph
│   ├── Graph.cpp
│   ├── Graph.hpp
│   
├── Tests
│   ├── test.cpp
│   
├── doctest.h
├── main.cpp
├── makefile
└── README.md
```

## Usage Examples

In the file **main.cpp** -includes examples, that demonstrating the usage of the algorithms,clearly showing outputs before and after execution,as well as MST and shortest paths.

## Testing 

Comprehensive unit tests, using **doctest.h**, ensure full coverage and corretness.

## Author

**Roy Meoded** (roymeoded2512@gmail.com)










