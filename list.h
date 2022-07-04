#ifndef LIST_H
#define LIST_H
#include "node.h"

template <typename T>
class List {
protected: 
    Node<T>* head;
    Node<T>* tail;
    int nodes;
public:
    List() : head(nullptr), tail(nullptr), nodes(0) {};
    virtual ~List(){};
    virtual T front() = 0;
    virtual T back() = 0;
    virtual void push_front(T) = 0;
    virtual void push_back(T) = 0;
    virtual T pop_front() = 0;
    virtual T pop_back() = 0;
    virtual void insert(int, T) = 0;
    virtual T& operator[](int) = 0;
    virtual bool is_empty() = 0;
    virtual int size() = 0;
};
#endif

