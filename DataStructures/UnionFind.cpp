//roymeoded2512@gmail.com

#include "UnionFind.hpp"

//Implement the constructor:
graph::UnionFind::UnionFind(int size){
    for(int i=0;i<size;i++){
        parent[i]=i;//Every group its group by itself
        rank[i]=0; //Every group start with rank 0
    }
}

//Check who is the root of v:
int graph::UnionFind::find(int v){
    //If v is not the root--> we go recursive to his father:
    if(parent[v]!=v){ 
        parent[v]=find(parent[v]); //We bring closer the path
    }
    return parent[v];
}

//
void graph::UnionFind::unit(int v,int u){
    //We find the roots of u and v:
    int rootU=find(u);
    int rootV=find(v);

    if(rootU==rootV){
        return; // We on the same group
    }
    //We connect the group with the small rank to the group with the big rank:
    if(rank[rootU]<rank[rootV]){
        parent[rootU]=rootV;
    }
    else if(rank[rootU]>rank[rootV]){
        parent[rootV]=rootU;
    }
    //If there is equality--> we choose randomally rank and +1:
    else{
        parent[rootU]=rootV;
        rank[rootV]++;
    }
}