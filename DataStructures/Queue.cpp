//roymeoded2512@gmail.com

#include "Queue.hpp"
#include <iostream>

//The constructor initializing the two of the indexes to the beginning:
//The queue is empty
Queue:: Queue(): front(0) ,rear(0){}


//If rear==front-->no elements in the queue:
bool Queue:: isEmpty() const{
    return front==rear;
}

//If we came to the end of the array-->no way to add more elements:
bool Queue:: isFull()const{
    return rear==MAX_SIZE;
}

//Adding element to the end of the queue:
void Queue:: enqueue(int value){
    if(isFull()){
        std::cout <<"Queue is full!"<< std::endl;
        return;
    }
    data[rear++]=value; //Put the value in the end of the queue
}

//Remove the first element of the queue:
int Queue::dequeue(){
    if(isEmpty()){
        std::cout<<"There is no element to put out!"<<std::endl;
        return -1;
    }
    return data[front++]; //Return the first element and increase the front index
}

//Show the first element of the queue:
int Queue:: peek()const{
    if(isEmpty()){
        std::cout<<"The queue is empty!"<<std::endl;
        return -1;
    }
    return data[front]; // Return the first element without removing it
}



