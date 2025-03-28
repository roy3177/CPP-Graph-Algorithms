//roymeoded2512@gmail.com

#include "Algorithms.hpp"
#include "../DataStructures/Queue.hpp"
using namespace graph;

int main(){

    //Graph with 4 vertices:
    Graph g2(4);
    g2.addEdge(0,1,10);
    g2.addEdge(0,3,5);
    g2.addEdge(1,2,6);
    g2.addEdge(2,3,8); 
       
    std:: cout<<"\n********************************************\n";
    std:: cout<<"\n*************Graph 1**************\n";

    //Prints the initial graph:
    std::cout<<"\nInitial graph:\n";
    g2.print_graph();

    //Remove the edge of 0<--->1:
    g2.removeEdge(0,1);
    std:: cout<<"\nThe graph after removing the edge (0,1):\n";
    g2.print_graph();


    std:: cout<<"\n********************************************\n";

    std:: cout<<"*************Graph 2**************\n";

    //Run BFS from the vertex 0:
    int parent[MAX_VERTICES];
    Graph g3(4);
    g3.addEdge(0,3,0);
    g3.addEdge(0,1,0);
    g3.addEdge(2,1,0);
    g3.addEdge(2,3,0);

    //Prints the initial graph:
    std::cout<<"\nInitial graph:\n";
    g3.print_graph();
    std::cout <<"\nRunning BFS from the vertex 0:\n";
    Algorithms::bfs(g3,0,parent);

    std::cout <<"BFS tree (child->parent):\n";
    for(int i=0;i<g3.getNumVertices();i++){
        std::cout<<"child:"<<i <<", parent: "<<parent[i]<<'\n';
    }

    std:: cout<<"\n********************************************\n";

    std:: cout<<"*************Graph 3**************\n";

    //Run DFS from the vertex 0:
    int dist[MAX_VERTICES];
    Graph g4(6);
    g4.addEdge(0,3,0);
    g4.addEdge(5,1,0);
    g4.addEdge(4,1,0);
    g4.addEdge(2,1,0);
    g4.addEdge(2,3,0);

    //Prints the initial graph:
    std::cout<<"\nInitial graph:\n";
    g4.print_graph();

    std::cout <<"\nRunning DFS from the vertex 0:\n";
    Algorithms::dfs(g4,0,parent);

    std::cout <<"DFS tree (child->parent):\n";
    for(int i=0;i<g4.getNumVertices();i++){
        std::cout<<"child:"<<i <<", parent: "<<parent[i]<<'\n';
    } 
    std:: cout<<"\n********************************************\n";

    std:: cout<<"*************Graph 4**************\n";
    Graph g5(5);
    g5.addEdge(0,1,2);
    g5.addEdge(0,2,4);
    g5.addEdge(2,1,1);
    g5.addEdge(3,4,2);
    g5.addEdge(1,3,7);
    g5.addEdge(2,4,3);

    //Prints the initial graph:
    std::cout<<"\nInitial graph:\n";
    g5.print_graph();

    std::cout <<"Running Dijkstra from vertex 0:\n";
    Algorithms::dijkstra(g5,0,dist,parent);

    std::cout <<"Dijkstra results:\n";
    for(int i=0;i<g5.getNumVertices();i++){
        std::cout <<"Vertex"<<i
                    <<"-> distance : " <<dist[i]
                    <<" parent: " <<parent[i]<< "\n";


    }
    std:: cout<<"\n********************************************\n";

    std:: cout<<"*************Graph 5**************\n";
    //Graph with 8 vertices:
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

    //Prints the initial graph:
    std::cout<<"Initial graph:\n";
    g.print_graph();

    int parent2[9];

    std::cout <<"\nRunning Prim from vertex 0:\n";
    Algorithms::prim(g,0,parent2);

    std::cout <<"Prim MST results:\n";
    for(int i=0;i<9;i++){
      std::cout <<"Vertex"<< i <<" ---> "<<parent2[i] << std::endl;
    }

    std::cout << "\nRunning kruskal from vertex 0:\n";
    Algorithms::kruskal(g, parent2);

    std::cout << "\nKruskal MST results (child -> parent):\n";
    for(int i = 0; i < 9; i++){
        std::cout << "Vertex " << i << " ---> " << parent2[i] << std::endl;
    }


    return 0;


}



