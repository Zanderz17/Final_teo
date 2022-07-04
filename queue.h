#ifndef QUEUE_H
#define QUEUE_H

#include "double.h"

template <typename T>
class QueueArray : public DoubleList<T> { 
    public:
    QueueArray() : DoubleList<T>() {};
    void enqueue(T data);
    T dequeue();
    bool is_empty();
    
};

template <class T>
void QueueArray<T>::enqueue(T data){
    this->push_back(data);
}

template <class T>
T QueueArray<T>::dequeue(){
    T result=this->pop_front();
    return result;
}

template <class T>
bool QueueArray<T>::is_empty(){
    return this->nodes == 0;
}

#endif