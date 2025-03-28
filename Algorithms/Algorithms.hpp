//roymeoded2512@gmail.com

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "../Graph/Graph.hpp"

namespace graph{

class Algorithms{
public:
    static void bfs(const Graph& g,int source,int parent[]);
    static Graph dfs(const Graph& g,int source,int parent[]);
    static Graph dijkstra(const Graph& g,int source,int dist[],int parent[]);
    static Graph prim(const Graph& g,int source,int parent[]);
    static Graph kruskal(const Graph& g,int parent[]);
    

private:

};

}

#endif