//roymeoded2512@gmail.com

#include "PriorityQueue.hpp"

//Constructor-->empty queue:
PriorityQueue::PriorityQueue(){
    size=0;
}

//Insert new element to the end of the queue:
void PriorityQueue::insert(int vertex,int distance){
    data[size++]={vertex,distance};
}

//
int PriorityQueue::extractMin(){
    int minIndex=-1; 
    int minValue=1e9;//Save the minimum value that we found

    //Check which vertex taking the smallest distance+ save it's index:
    for(int i=0;i<size;i++){
        if(data[i].distance<minValue){
            minValue=data[i].distance;
            minIndex=i;
        }
    }
    //Save the number of the vertex that we return from the queue:
    int result=data[minIndex].vertex;


    //Taking the last vertex in the queue-->put him on the place of the vertex that got removed-->reduce the size:
    data[minIndex]=data[--size];

    return result;
}

//Check if the queue is empty:
bool PriorityQueue::isEmpty()const{
    return size==0;
}


//If we find shorter path-we decrease the vertex that on the queue:
void PriorityQueue::decreaseKey(int vertex,int newDis){
    for(int i=0;i<size;i++){
        //If the vertex already on the queue + has smallest distance from before:
        if(data[i].vertex==vertex && newDis<data[i].distance){
            data[i].distance=newDis;
            break;
        }
    }
}
