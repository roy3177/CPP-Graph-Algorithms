//roymeoded2512@gmail.com

#include "Graph.hpp"

namespace graph{

//Constructor-->create new graph with constant number of vertices:
Graph::Graph(int vertices){
    numVertx=vertices;

    //Initializing all the vertices with empty adjacency list:
    //Every node start without neighbors
    for(size_t i=0; i<vertices;i++){
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

    //Checking if we added the same edge before:
    Node* current = adjList[source];
    while (current != nullptr) {
        if (current->dest == destination) {
            // Edge already exists, no need to add it again:
            std::cerr << "Edge from " << source << " to " << destination << " already exists.\n";
            return;
        }   
        current = current->next;
    }

    //Our graph is undirected, so we add the edge in both directions:

    // Adding the edge to the graph:
    // x------->y
    Node* newNode = new Node{destination, weight, adjList[source]};
    adjList[source] = newNode;

    // Adding the reverse edge (undirected graph):
    // y------->x
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
    //Check if the edge exists before removing it:
    Node* current2 = adjList[source];
    bool edgeExists = false;
    while (current2 != nullptr) {
        if (current2->dest == destination) {
            edgeExists = true;
            break;
        }
        current2 = current2->next;
    }
    
    //If the edge does not exist, we do not remove it:
    if (!edgeExists) {
        std::cerr << "Edge does not exist.\n";
        return;
    }


    //Removing the edge from the adjacency list of the source vertex:
    //We use double pointer to be able to change the head of the list:
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
     Node** current3=&adjList[destination];
    while(current3!=nullptr){
        if((*current3)->dest==source){
            Node* temp=*current3;
            *current3=(*current3)->next;
            delete temp;
            break;
        }
        current3=&((*current3)->next);
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


