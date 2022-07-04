#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(){ 
        this->next = nullptr;
        this->prev = nullptr;
    }
    Node(T value){
        this->data = value;
        this->next = nullptr;
        this->prev = nullptr;
    }
    void killSelf(){;}
};

#endif