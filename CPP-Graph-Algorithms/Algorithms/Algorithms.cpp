//@roymeoded2512@gmail.com

#include "Algorithms.hpp"
#include "../DataStructures/Queue.hpp" //BFS,DFS
#include "../Graph/Graph.hpp"
#include "../DataStructures/PriorityQueue.hpp" //Dijkstra
#include <limits> 
#include "../DataStructures/UnionFind.hpp" //Kruskal

#define MAX_EDGES 1000 // Maximum number of edges in the graph

//Struct of edge:
//Used in Kruskal's algorithm to store edges
struct Edge{
    int u; //The source vertex of the edge
    int v; //The destination vertex of the edge
    int weight;
};

namespace graph{

//**********BFS Algorithm**********
void Algorithms::bfs(const Graph& g,int source,int parent[]){
    int numVex=g.getNumVertices(); 

    if (source < 0 || source >= g.getNumVertices()) {
    throw std::invalid_argument("Invalid start vertex");
    }
    
    //Making a boolean array that if we visited for each node
    //Starts with false for everyone
    bool visited[MAX_VERTICES]={false};

    Queue q; //Our queue for breadth-first search
    
    //We starts the every node does not has parent:
    for(int i=0;i<numVex;i++){
        parent[i]=-1;
    }

    visited[source]=true; //This is the first node that we visited
    
    //Adding the initial node to the queue:
    q.enqueue(source);

    while(!q.isEmpty()){
        int current=q.dequeue(); //Pop out the first node of the queue
        Node* neighbor=g.getAdjList(current);
        while(neighbor!=nullptr){
            int v=neighbor->dest; //v<---->current
            //If we did not visit v--> mark that we visit it:
            if(!visited[v]){
                visited[v]=true;
                parent[v]=current;
                q.enqueue(v); //Put v on the queue, for works on his neighbors
            }
            neighbor=neighbor->next;
        }
    }
}

//**********DFS Algorithm**********
static void dfsHelper(const Graph& g,int current,bool visited[], int parent[]){

    //Mark the current node as visited:
    visited[current]=true ;

    //Get the neighbors of the current node:
    Node* neighbor=g.getAdjList(current);
    while(neighbor!=nullptr){
        int v=neighbor->dest;
        //If we dont visit v, so current is the father of v:
        if(!visited[v]){
            parent[v]=current;
            dfsHelper(g,v,visited,parent); //Recursive
        }
        neighbor=neighbor->next;
    }
}

void Algorithms::dfs(const Graph& g,int source,int parent[]){
    int numVerx=g.getNumVertices();
    bool visited[MAX_VERTICES]={false}; //Visited vertices

    //Check if the source vertex is valid:
    if (source < 0 || source >= g.getNumVertices()) {
        throw std::invalid_argument("Invalid start vertex");
    }
    //Like BFS, at the beginning-->no fathers:
    for(int i=0;i<numVerx;i++){
        parent[i]=-1;
    }
    
    dfsHelper(g,source,visited,parent); //Recursive helper function
    
}  

//**********Dijkstra Algorithm**********:
Graph Algorithms::dijkstra(const Graph& g,int source,int dist[],int parent[]){
    int numVex=g.getNumVertices();
    bool visited[MAX_VERTICES]={false};

    //Check if the source vertex is valid:
    if(source<0 || source>=g.getNumVertices()){
        throw std::invalid_argument("Invalid source vertex !");
    }

    for(int i=0; i<numVex;i++){
       
        dist[i]=std::numeric_limits<int>::max(); //Initialize the distance to all vertices as infinite
        parent[i]=-1 ; //Unknown parent 
    }

    dist[source]=0; //It's obvious

    //Create our priority queue :
    //We will use it to get the vertex with the minimum distance
    PriorityQueue pq;
    pq.insert(source,0); 

    while(!pq.isEmpty()){
        int u=pq.extractMin(); //Taking the vertex with shortest distance
        if(visited[u]){
            continue;
        }
        visited[u]=true;
        //Get the list of neighbors of vertex u:
        Node* neighbor=g.getAdjList(u);
        while(neighbor!=nullptr){
            //Saves the neighbor vertex of u(v),and the edge's size (u<----->v)
            int v=neighbor->dest;
            int weight=neighbor->weight;

            //On Dijkstra-->all the edges are positives
            if(weight<=0){
                throw std::invalid_argument("Edge weight must be positive");
            }
            if(!visited[v]&& dist[u]+weight<dist[v]){
                dist[v]=dist[u]+weight; //The shortest distance 
                parent[v]=u; //The parent
                pq.insert(v,dist[v]); //Instert the new vertex
            }
            neighbor=neighbor->next;

        }
    }
    //Builds the graph that we want to return:
    Graph mst(numVex);
    for (int v = 0; v < numVex; v++) {
        if (parent[v] != -1) {
            int u = parent[v];
            int weight = dist[v] - dist[u]; 
            mst.addEdge(u, v, weight);
        }
    }

    return mst;

    }

    //**********Prim Algorithm**********:
    Graph Algorithms::prim(const Graph& g,int source,int parent[]){

        int numVex=g.getNumVertices();
        bool visited[MAX_VERTICES]={false}; //Visited vertices
        int key[MAX_VERTICES]; //The minimum weight of the edge that connects the vertex to the MST

        //Check if the source vertex is valid:
        if(source<0 || source>=g.getNumVertices()){
            throw std::invalid_argument("Invalid source vertex !");
        }

        //Initialize the key and parent arrays:
        for(int i=0;i<numVex;i++){
            parent[i]=-1;
            key[i]=1e9 ;; //infinite distance
        }
        key[source]=0; //Our start vertex 
        
        //Adding new vertex to the MST every round:
        for(int i=0;i<numVex;i++){
            //Find the vertex with the minimum key that has not been visited yet:
            //We use minKey to find the minimum key:
            int u=-1;
            int minKey=1e9;
            for(int j=0;j<numVex;j++){
                if(!visited[j]&& key[j]<minKey){
                    minKey=key[j];
                    u=j;
                }
            }
            //If u is -1, it means that we visited all the vertices:
            if(u==-1){
                break;
            }
            visited[u]=true; //We  add u to our MST
            
            //Now we visit all the neighbors of the current vertex(u):
            Node* neighbor=g.getAdjList(u);

            while(neighbor!=nullptr){
                int v=neighbor->dest;
                int weight=neighbor->weight;

                //Checks the same to the neighbor of u (v):
                if(!visited[v] && weight<key[v]){
                    key[v]=weight; //The minimum weight of the edge that connects v to the MST
                  
                    parent[v]=u; //The parent of v in the MST
                }
                neighbor=neighbor->next; // Move to the next neighbor
            }
        }

        //Build the minimum spanning tree (MST) graph:
        Graph mst(numVex);
        for(int i=0;i<numVex;i++){
            if(parent[i]!=-1){
                mst.addEdge(i,parent[i],key[i]);
            }
        }
        return mst;
    }

    //**********Kruskal Algorithm**********:
    Graph Algorithms::kruskal(const Graph& g,int parent[]){
    int numVex = g.getNumVertices();


    //Define array that take all the edges in the graph:
    Edge edges[MAX_EDGES];
    int edgesCount = 0; //We count how many edges we put in

    //Build list of all the edges:
    for(int u = 0; u < numVex; u++){
        Node* neighbor = g.getAdjList(u);
        while(neighbor != nullptr){
            int v = neighbor->dest;
            int weight = neighbor->weight;
            
            //On undirected graph, we add the edge only once:
            if(u < v){
                edges[edgesCount++] = {u, v, weight};
            }
            neighbor = neighbor->next;
        }
    }

    //Sort the edges by weight (Bubble sort):
    for(int i = 0; i < edgesCount - 1; i++){
        for(int j = 0; j < edgesCount - i - 1; j++){
            if(edges[j].weight > edges[j + 1].weight){
                Edge tmp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = tmp;
            }
        }
    }
    //Now we have all the edges sorted by weight, we can start building the MST:
    //We will use Union-Find data structure to check if we can add the edge without creating a cycle:
    UnionFind uf(numVex);

    for(int i = 0; i < numVex; i++){
        parent[i] = -1;
    }
    Graph mst(numVex); //The graph we will return


    int edgesUsed = 0; //Count how many edges we used in the MST
    
    //Iterate over the sorted edges and add them to the MST if they do not create a cycle:
    for(int i = 0; i < edgesCount && edgesUsed < numVex - 1; i++){
        int u = edges[i].u; // The source vertex of the edge
        int v = edges[i].v; // The destination vertex of the edge

        //If u and v are not in the same set, we can add the edge to the MST:
        if(uf.find(u) != uf.find(v)){
            uf.unit(u, v);

            // Set parent[v] = u OR parent[u] = v depending on who was child:
            if (parent[u] == -1) {
                parent[u] = v;
            } 
            else {
                parent[v] = u;
            }

            //Add the edge to the MST:
            mst.addEdge(u,v,edges[i].weight);
            edgesUsed++;
        }
    
    }
    //If we used less than numVex - 1 edges, it means that the graph is not connected:
     if(edgesUsed!=numVex-1){
        throw  std::invalid_argument("MST cannot be build!");
     }
     
    return mst;

    }
}


    