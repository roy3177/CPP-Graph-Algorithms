//roymeoded2512@gmail.com


#ifndef QUEUE_HPP
#define QUEUE_HPP

const int MAX_SIZE=100;

class Queue{
private:
    int data[MAX_SIZE];
    int front; //Index of the first element in the queue
    int rear; //Index of the next element to put in

public:
    Queue();
    bool isEmpty() const;
    bool isFull() const;
    void enqueue(int value);
    int dequeue();
    int peek()const; //Return the first element->without to get it out
};

#endif


