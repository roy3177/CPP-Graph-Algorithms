//roymeoded2512@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../Algorithms/Algorithms.hpp"
#include "../Graph/Graph.hpp"

using namespace graph;

//Check add/remove edge:
TEST_CASE("Adding and removing edges"){
    Graph g(3);
    g.addEdge(0,1,5);
    g.addEdge(1,2,10);

    //Make sure that adding edge that exsist-->not throw exception:
    CHECK_NOTHROW(g.addEdge(1,2,10));
}

TEST_CASE("Adding edges with invalid vertices-->throw exception"){
    Graph g(3);
    CHECK_THROWS_AS(g.addEdge(-1,-3,10),std::invalid_argument);
    CHECK_THROWS_AS(g.addEdge(3,1,5),std::invalid_argument);

}

TEST_CASE("Removing edges with valid and invalid vertices"){
    Graph g(4);
    g.addEdge(0,1,3);
    g.addEdge(2,3,4);

    CHECK_NOTHROW(g.removeEdge(0,1));
    CHECK_NOTHROW(g.removeEdge(2,3));

    //Invalid vertex-->negative vertex:
    CHECK_THROWS_AS(g.removeEdge(-1,2),std::invalid_argument);

    //Invalid vertex-->bigger vertex:
    CHECK_THROWS_AS(g.removeEdge(2,10),std::invalid_argument);
}

//The number of vertices:
TEST_CASE("Return the current number of vertices"){
    Graph g(5);
    CHECK(g.getNumVertices()==5);
}

TEST_CASE("Return the current connections"){
    Graph g(3);
    g.addEdge(0,1,10);
    g.addEdge(0,2,5);

     //Make sure that there are connections from vertex 0:
     int count=0;
     for(Node* curr=g.getAdjList(0);curr!=nullptr;curr=curr->next){
        count++;
     }
     CHECK(count==2);

     //Check invalid 1<---->1:
     for(Node* current=g.getAdjList(1);current!=nullptr;current=current->next){
        CHECK(current->dest!=1);
     }
}

//Check the print graph:
TEST_CASE("Print the graph-without throwing"){
    Graph g(3);
    g.addEdge(0,1,10);
    g.addEdge(2,1,13);

    CHECK_NOTHROW(g.print_graph());
}


//BFS:
TEST_CASE("Checking the BFS-->return correct tree"){
    Graph g(4);
    g.addEdge(0,1,1);
    g.addEdge(0,2,1);
    g.addEdge(1,3,1);

    int parent[4];
    Algorithms::bfs(g,0,parent);

    CHECK(parent[0]==-1);
    CHECK((parent[1]==0||parent[2]==0));
    CHECK(parent[3]==1);

    //Throw  exception for invalid s vertex:
    CHECK_THROWS_AS(Algorithms::bfs(g,10,parent),std::invalid_argument);


}

//DFS:
TEST_CASE("Checking the DFS-->return correct tree"){
    Graph g(6);
    g.addEdge(0,3,1);
    g.addEdge(3,2,1);
    g.addEdge(1,2,1);
    g.addEdge(1,5,1);
    g.addEdge(1,4,1);


    int parent[6];
    Graph tree=Algorithms::dfs(g,0,parent);

    CHECK(parent[0]==-1);
    CHECK((parent[1]==2||parent[2]==3));
    CHECK(parent[3]==0);

    //Check if there is only one root:
    int rootCount = 0;
    for (int i = 0; i < 6; i++) {
        if (parent[i] == -1) rootCount++;
    }
    CHECK(rootCount == 1);

    //Throw  exception for invalid s vertex:
    CHECK_THROWS_AS(Algorithms::dfs(g,10,parent),std::invalid_argument);
}

//Dijkstra:
TEST_CASE("Return the shortest path from source to the rest of the vertices"){
    Graph g(5);
    g.addEdge(0,1,2);
    g.addEdge(0,2,4);
    g.addEdge(1,3,7);
    g.addEdge(4,3,2);
    g.addEdge(4,2,3);
    g.addEdge(2,1,1);

    int dist[5];
    int parent[5];
    Graph mst=Algorithms::dijkstra(g,0,dist,parent);

    CHECK(dist[0]==0);
    CHECK(dist[1]==2);
    CHECK(dist[2]==3);
    CHECK(dist[4]==6);
    CHECK(dist[3]==8);

}
TEST_CASE("Invalid source vertex"){
    Graph g(3);
    g.addEdge(0,1,1);
    g.addEdge(1,2,2);

    int dist[3];
    int parent[3];

    CHECK_THROWS_AS(Algorithms::dijkstra(g,5,dist,parent),std::invalid_argument);
}

TEST_CASE("Invalid source vertex"){
    Graph g(3);
    g.addEdge(0,1,1);
    g.addEdge(1,2,-2);

    int dist[3];
    int parent[3];

    CHECK_THROWS_AS(Algorithms::dijkstra(g,5,dist,parent),std::invalid_argument);
}
//Prim:
TEST_CASE("Get a valid MST"){
     Graph g(9);

    g.addEdge(0, 1, 9);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 4, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 5, 3);
    g.addEdge(2, 3, 5);
    g.addEdge(2,5,12);
    g.addEdge(2,4,1);
    g.addEdge(3,6,8);
    g.addEdge(4,8,6);
    g.addEdge(5,6,5);
    g.addEdge(5,7,2);
    g.addEdge(6,7,2);
    g.addEdge(7,8,1);

    int parent[9];
    
    Algorithms::prim(g,0,parent);
    int count=0;
    for(int i=0;i<9;i++){
        if(parent[i]!=-1){
            count++;
        }
    }
    CHECK(count==8);
}
TEST_CASE("Invalid source vertex-->throw exception"){
    Graph g(3);
    g.addEdge(0,1,10);
    g.addEdge(1,2,5);

    int parent[3];

    CHECK_THROWS_AS(Algorithms::prim(g,-1,parent),std::invalid_argument);
    CHECK_THROWS_AS(Algorithms::prim(g,3,parent),std::invalid_argument);
                                                                                                                                                                                                                                                           
}
//Kruskal:
TEST_CASE("Get a valid MST"){
     Graph g(4);

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2,3,3);
    g.addEdge(3,0,4);
   

    int parent[4];
    Graph mst=Algorithms::kruskal(g,parent);

    int edgeCount=0;
    for(int i=0;i<mst.getNumVertices();i++){
        Node*current=mst.getAdjList(i);
        while(current!=nullptr){
            edgeCount++;
            current=current->next;
        }
    }
    //On undirected graph-->every edge showed twice:
    CHECK(edgeCount/2==3);
}

TEST_CASE("Kruskal failed on undirected graph"){
    Graph g(4);
    g.addEdge(0,1,1);
    g.addEdge(2,3,1);

    int parent[4];
    CHECK_THROWS_AS(Algorithms::kruskal(g,parent),std::invalid_argument);
}


    
