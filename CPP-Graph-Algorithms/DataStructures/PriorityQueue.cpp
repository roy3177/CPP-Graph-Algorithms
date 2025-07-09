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

//Extract the vertex with the minimum distance from the queue:
int PriorityQueue::extractMin(){
    int minIndex=-1; 
    int minValue=1e9;//We start with the maximum value, so we can find the minimum

    //Check which vertex taking the smallest distance + save it's index:
    for(int i=0;i<size;i++){
        if(data[i].distance<minValue){
            minValue=data[i].distance;
            minIndex=i;
        }
    }
    //Save the number of the vertex that we return from the queue:
    int result=data[minIndex].vertex;

    //If we found the vertex with the minimum distance, we remove it from the queue:
    data[minIndex]=data[--size];

    return result; //Return the vertex with the minimum distance
}

//Check if the queue is empty:
bool PriorityQueue::isEmpty()const{
    return size==0;
}


////If we find shorter path-we decrease the vertex that on the queue:
void PriorityQueue::decreaseKey(int vertex,int newDis){
    for(int i=0;i<size;i++){
        //If the vertex already on the queue + has smallest distance from before:
        if(data[i].vertex==vertex && newDis<data[i].distance){
            data[i].distance=newDis;
            break;
        }
    }
}
