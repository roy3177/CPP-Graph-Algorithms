//roymeoded2512@gmail.com

#include "Graph.hpp"

namespace graph{

//Implements our constructor:
Graph::Graph(int vertices){
    numVertx=vertices;

    //Initializing all the vertices with empty adjacency list:
    //Every node start without neighbors
    for(size_t i=0; i<MAX_VERTICES;i++){
        adjList[i]=nullptr;
    }
}

//Free from the memory all the edges,that allocate dynamic for every node:
Graph::~Graph(){
    for(int i=0;i<numVertx;i++){
        Node* current=adjList[i];
        while(current!=nullptr){
            Node* next=current->next;
            delete current;
            current=next;
        }
    }
}

//Add edge to the graph:
void Graph::addEdge(int source, int destination, int weight) {
    // Valid vertices:
    if (source < 0 || destination < 0 || source >= numVertx || destination >= numVertx) {
        throw std::invalid_argument("Invalid vertex index in addEdge");
    }

    // Adding the edge to the graph:
    Node* newNode = new Node{destination, weight, adjList[source]};
    adjList[source] = newNode;

    // Adding the reverse edge (undirected graph):
    Node* newNodeBack = new Node{source, weight, adjList[destination]};
    adjList[destination] = newNodeBack;
}

//Print the graph:
void Graph:: print_graph() const{
    std:: cout << "Graph adjacency list:\n";
    for(int i=0;i<numVertx;i++){
        std:: cout <<"Vertex"<<i<<":";
        Node* current=adjList[i];
        while(current!=nullptr){
            std::cout <<"(neighbor: "<<current->dest<<",weight:"<<current->weight<<")";
            current=current->next;
        }
        std::cout <<std::endl;
    }
}

//Remove edge from the graph:
void Graph:: removeEdge(int source,int destination){
    //Valid vertices:
     if (source < 0 || destination < 0 || source >= numVertx || destination >= numVertx) {
        throw std::invalid_argument("Invalid vertex index in addEdge");
    }

    //Goes on the list of source,  and removes the edge that comes to destination:
    Node** current=&adjList[source];
    while(current!=nullptr){
        if((*current)->dest==destination){
            Node* temp=*current;
            *current=(*current)->next;
            delete temp;
            break;
        }
        current=&((*current)->next);
    }
    //Doing the same on the reverse way->because our graph is undirected:
     Node** current2=&adjList[destination];
    while(current2!=nullptr){
        if((*current2)->dest==source){
            Node* temp=*current2;
            *current2=(*current2)->next;
            delete temp;
            break;
        }
        current2=&((*current2)->next);
    }
    
}

//Returns the number of the vertices(that defined in the constructor):
int Graph::getNumVertices()const{
    return numVertx;
}

//Return the head of the neighbors's list:
Node* Graph::getAdjList(int vertex)const{
    if(vertex<0 || vertex>=numVertx){
        return nullptr;
    }
    return adjList[vertex];
}

    
} // namespace graph
