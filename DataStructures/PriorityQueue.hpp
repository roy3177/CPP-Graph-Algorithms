//roymeoded2512@gmail.com

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#define MAX_VERTICES 1000

//Node in our priority queue:
struct PQNode{
    int vertex; //Number of the vertex
    int distance; //The distance of the vertex from the initial vertex
};

class PriorityQueue{
private:
    PQNode data[MAX_VERTICES];
    int size; 

public:
    PriorityQueue(); //Constructor
    void insert(int vertex,int distance); //Add new element to the queue
    int extractMin(); //Return the vertex with the minimum distance
    bool isEmpty() const; //Check if the queue is empty

    //If we find shorter path-we decrease the vertex that on the queue:
    void decreaseKey(int vertex,int newDis);
};

#endif