#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

template <typename T>
class DoubleList : public List<T> {
    public:
        DoubleList() : List<T>() {};
        T front();
        T back();
        void push_front(T data);
        void push_back(T data);
        T pop_front();
        T pop_back();
        void insert(int pos, T data);
        T& operator[](int pos);
        bool is_empty();
        int size();
        bool is_in(T data);
        int is_in_index(T data);
};


template <typename T>
T DoubleList<T>::front(){
    return this->head->data;
}

template <typename T>
T DoubleList<T>::back(){
    return this->tail->data;
}

template <typename T>
void DoubleList<T>::push_front(T value){
    Node<T>* new_node = new Node<T>(value);
    if(this->head==nullptr && this->tail==nullptr){
        this->head = new_node;
        this->tail = new_node;
    }
    else{
        new_node->next = this->head;
        new_node->prev = this->head->prev;
        this->head->prev = new_node;
        this->head = new_node;
    }
    ++this->nodes;
}

template <typename T>
void DoubleList<T>::push_back(T value){
    Node<T>* new_node = new Node<T>(value);
    
    if(this->head==nullptr){
        this->head = new_node;
        this->tail = new_node;
    }
    else{
        new_node->prev = this->tail;
        new_node->next = this->tail->next;
        this->tail->next = new_node;
        this->tail = new_node;
    }
    
    ++this->nodes;
}

template <typename T>
T DoubleList<T>::pop_front(){
    if(this->head == nullptr) throw("Empty list");
    T temp = this->head->data;
    this->head = this->head->next;
    --this->nodes;
    return temp;
    
}

template <typename T>
T DoubleList<T>::pop_back(){
    if(this->head == nullptr) throw("Empty list");
    T temp = this->tail->data;
    this->tail = this->tail->prev;
    --this->nodes;
    return temp;
}

template <typename T>
void DoubleList<T>::insert(int pos, T data){
    if(pos == 0)
        push_front(data);
    else if(pos == this->nodes)
        push_back(data);
    else{
        Node<T>* new_node = new Node<T>;
        new_node->data = data;
        Node<T>* temp = this->head;
        int i = 0;
        while(i++ < pos-1){temp = temp->next;}
        new_node->next = temp->next;
        new_node->prev = temp;
        temp->next->prev = new_node;
        temp->next = new_node;
    }
    ++this->nodes;
}

template <typename T>
T& DoubleList<T>::operator[](int pos){
    if(pos < 0 || pos >= this->nodes)
        throw("Index out of bounds");
    else{
        Node<T>* temp = this->head;
        int i=0;
        while(i++ < pos){temp = temp->next;}
        return temp->data;
    }
}

template <typename T>
bool DoubleList<T>::is_empty(){
    return this->nodes == 0;
}

template <typename T>
int DoubleList<T>::size(){
    return this->nodes;
}

template <typename T>
bool DoubleList<T>::is_in(T data){
    Node<T>* temp = this->head;
    int i=0;
    while(i++ < this->nodes){
        if(temp->data == data)
            return true;
        temp = temp->next;
    }
    return false;
}

template <typename T>
int DoubleList<T>::is_in_index(T data){
    Node<T>* temp = this->head;
    int i=0;
    while(i < this->nodes){
        if(temp->data == data)
            return i;
        temp = temp->next;
        ++i;
    }
    return -1;
}

#endif
