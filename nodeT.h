#ifndef NODET_H
#define NODET_H

#include "double.h"
using namespace std;

template <typename T>
struct NodeT {
    string stateName;
    DoubleList<T> symbols;
    DoubleList<NodeT*> nodes;
    NodeT(){}
    NodeT(int id, T symbol){
        stateName = 'q'+to_string(id);
        symbols.push_back(symbol);
    }
    NodeT(T symbol){
        symbols.push_back(symbol);
    }
    void KillSelf(){}
};

#endif