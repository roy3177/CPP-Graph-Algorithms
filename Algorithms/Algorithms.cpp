//@roymeoded2512@gmail.com

#include "Algorithms.hpp"
#include "../DataStructures/Queue.hpp" //BFS,DFS
#include "../Graph/Graph.hpp"
#include "../DataStructures/PriorityQueue.hpp" //Dijkstra
#include <limits> 
#include "../DataStructures/UnionFind.hpp" //Kruskal

#define MAX_EDGES 1000

//Struct of edge:
struct Edge{
    int u;
    int v;
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
    visited[current]=true ;//We dont come to this node again
    //Get the head of the neighbor's list of current:
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

Graph Algorithms::dfs(const Graph& g,int source,int parent[]){
    int numVerx=g.getNumVertices();
    bool visited[MAX_VERTICES]={false};

    if (source < 0 || source >= g.getNumVertices()) {
        throw std::invalid_argument("Invalid start vertex");
    }
    //Like BFS, at the beginning-->no fathers:
    for(int i=0;i<numVerx;i++){
        parent[i]=-1;
    }
    Graph tree(numVerx); //The graph we will return
    //Calling the our helper function-start our deep search:
    dfsHelper(g,source,visited,parent);
    
    return tree;
}  

//**********Dijkstra Algorithm**********:
Graph Algorithms::dijkstra(const Graph& g,int source,int dist[],int parent[]){
    int numVex=g.getNumVertices();
    bool visited[MAX_VERTICES]={false};

    if(source<0 || source>=g.getNumVertices()){
        throw std::invalid_argument("Invalid source vertex !");
    }

    for(int i=0; i<numVex;i++){

        //At the beginning-->the shortest distance from source to each vertex is infinite
        dist[i]=std::numeric_limits<int>::max();
        parent[i]=-1 ; //Unknown parent 
    }
        dist[source]=0; //It's obvious

        //Create our priority queue :
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
        bool visited[MAX_VERTICES]={false};
        int key[MAX_VERTICES]; //The minimal price of edge to this vertex

        if(source<0 || source>=g.getNumVertices()){
        throw std::invalid_argument("Invalid source vertex !");
    }


        //At the beginning: all the keys are infinetes + dont have parent:
        for(int i=0;i<numVex;i++){
            parent[i]=-1;
            key[i]=1e9 ;; //Infinite
        }
        key[source]=0; //Our start vertex 
        
        //Adding new vertex to the MST every round:
        for(int i=0;i<numVex;i++){
            //We find the vertex with the minimal key, that we dont visit yet:
            int u=-1;
            int minKey=1e9;
            for(int j=0;j<numVex;j++){
                if(!visited[j]&& key[j]<minKey){
                    minKey=key[j];
                    u=j;
                }
            }
            //We already visit all the vetices:
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
                    key[v]=weight;
                  
                    parent[v]=u;
                }
                neighbor=neighbor->next;
            }
        }
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

    UnionFind uf(numVex);

    for(int i = 0; i < numVex; i++){
        parent[i] = -1;
    }
    Graph mst(numVex); //The graph we will return


    int edgesUsed = 0;
    

    for(int i = 0; i < edgesCount && edgesUsed < numVex - 1; i++){
        int u = edges[i].u;
        int v = edges[i].v;

        if(uf.find(u) != uf.find(v)){
            uf.unit(u, v);

            // Set parent[v] = u OR parent[u] = v depending on who was child
            if (parent[u] == -1) {
                parent[u] = v;
            } else {
                parent[v] = u;
            }

            mst.addEdge(u,v,edges[i].weight);
            edgesUsed++;
        }
    
    }
     if(edgesUsed!=numVex-1){
        throw  std::invalid_argument("MST cannot be build!");
     }
    return mst;

    }
}


    