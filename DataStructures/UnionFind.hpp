//roymeoded2512@gmail.com

#pragma once

#define MAX_VERTICES  1000

namespace graph{

class UnionFind{
private:
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES]; 

public:
    UnionFind(int size); //Constructor
    int find(int v); //Return the root that v belongs
    void unit(int v,int u); //Unit the groups of u and v

};
}