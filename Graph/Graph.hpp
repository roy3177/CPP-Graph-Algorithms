//roymeoded2512@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

const int MAX_VERTICES=100;

namespace graph{


//The struct of the edge:
struct Node{
    int dest;     //The number of the vertix that the edge comes
    int weight;  //The weight of the edge
    Node* next;  //Points to the next edge 

};

class Graph{
private:

    int numVertx;

    //Structure, that represents adjacency list:
    Node* adjList[MAX_VERTICES];

public:
    
    //Constructor-->create new graph with constant number of vertices:
    Graph(int numVertx);
    ~Graph(); //Destructor

    //Add edge to the graph:
    void addEdge(int source,int destination, int weight=1);

    //Remove edge from the graph:
    void removeEdge(int source,int destination);

    //Print the graph:
    void print_graph() const;

    //Return the number of the vertices in the graph:
    int getNumVertices()const;

    //Return the head of neighbors's list(important for the Algorithms):
    Node* getAdjList(int vertex)const;
};
}
#endif