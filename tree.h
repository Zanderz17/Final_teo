#ifndef TREE_H
#define TREE_H

#include "string"
#include "nodeT.h"
#include "queue.h"
using namespace std;

template <class T>
class Tree {
    private:
        NodeT<T>* root; 
        int sizeTree;
        int sizeRoot;
        DoubleList<string> afn_finalStates;
        DoubleList<string> afd_finalStates;
    public:
        Tree(): root(nullptr), sizeTree(0), sizeRoot(0) {}
		void insert(string str);
        void displayTree();
        DoubleList<DoubleList<string>> adjList();
        bool testString(string str);
        DoubleList<DoubleList<string>> afnMatrix(string str);
        DoubleList<DoubleList<string>> afdMatrix(string str);
        NodeT<T>* go_state(string stateName);
        bool evaluateStrInAfd(string strToEvaluate, string stringsFromAFD);
        ~Tree(){};
    private:
        void insert(NodeT<T>* &nodo, string str);
        bool testStrByBranch(int nBranch, string subStr);
};

template <class T>
void Tree<T>::insert(string str){
    int id = sizeTree;
    char symbol = str[0];
    if(root == nullptr){
        root = new NodeT<T>(id, symbol);
        ++this->sizeTree;   
    }
    else{
        root->symbols.push_back(symbol);
    }
    insert(this->root, str.substr(1, str.size()));
    ++this->sizeRoot;
}

template <class T>
void Tree<T>::insert(NodeT<T>* &nodo, string str){
    if(str == "") {
        int id = sizeTree;
        char symbol = str[0];
        nodo->nodes.push_back(new NodeT<T>(id, symbol));
        ++this->sizeTree;
        afn_finalStates.push_back(nodo->nodes[0]->stateName);
    }
    else if(nodo == this->root){
        int id = sizeTree;
        char symbol = str[0];
        nodo->nodes.push_back(new NodeT<T>(id, symbol));
        ++this->sizeTree;
        insert(nodo->nodes[sizeRoot], str.substr(1, str.size()));
    }
    else{
        int id = sizeTree;
        char symbol = str[0];
        nodo->nodes.push_back(new NodeT<T>(id, symbol));
        ++this->sizeTree;
        insert(nodo->nodes[0], str.substr(1, str.size()));
    }
}

template <class T>
void Tree<T>::displayTree(){
    cout<<root->stateName<<" - ";
    cout<<"size: "<<sizeRoot<<endl;
    for(int i=0; i<this->sizeRoot; ++i){
        NodeT<T>* travNode = root->nodes[i]; 
        while(true){
            cout<<i<<" -> ";
            cout<<travNode->stateName<<" - ";
            cout<<"size: "<<travNode->nodes.size()<<endl;

            if(travNode->nodes.size() != 0)
                travNode = travNode->nodes[0];
            else
                break;
        }
    }
}

template <class T>
DoubleList<DoubleList<string>> Tree<T>::adjList(){
    DoubleList<DoubleList<string>> adjList;
    DoubleList<string> aux0;
    aux0.push_back(root->stateName);
    for(int i=0; i<this->sizeRoot; ++i)
        aux0.push_back(root->nodes[i]->stateName);
    adjList.push_back(aux0);
    
    for(int i=0; i<this->sizeRoot; ++i){
        NodeT<T>* travNode0 = root->nodes[i];
        while(true){
            DoubleList<string> aux1;
            aux1.push_back(travNode0->stateName);
            if(travNode0->nodes.size() != 0){
                NodeT<T>* travNode1 = travNode0->nodes[0];
                aux1.push_back(travNode1->stateName);
            }
            adjList.push_back(aux1);
            if(travNode0->nodes.size() != 0)
                travNode0 = travNode0->nodes[0];
            else
                break;
        }
    }
    return adjList;
}

template <class T>
bool Tree<T>::testString(string str){
    QueueArray<NodeT<T>*> sReached;
    sReached.enqueue(root);
    QueueArray<NodeT<T>*> newSReached;
    for(auto& chr: str){
        int sz = sReached.size();
        for(int i=0; i<sz; ++i){
            NodeT<T>* stateDq = sReached.dequeue();
            if(stateDq == root){
                newSReached.enqueue(root);
                int stateDq_size = stateDq->symbols.size();
                for(int j=0; j<stateDq_size; ++j){
                    if(stateDq->symbols[j] == chr){
                        newSReached.enqueue(stateDq->nodes[j]);
                        if(stateDq->nodes[j]->symbols[0] == 0)
                            return true;
                    }   
                }
            }
            else{
                if(stateDq->symbols[0] == chr){
                    newSReached.enqueue(stateDq->nodes[0]);
                    if(stateDq->nodes[0]->symbols[0] == 0)
                        return true;
                }           
            }
        }
        
        while(!newSReached.is_empty()){
            sReached.enqueue(newSReached.dequeue());
        }
    }
    return false;
}

template <typename T>
NodeT<T>* Tree<T>::go_state(string stateName){
    int nState = stoi(stateName.substr(1, stateName.size()));
    if(nState == 0)
        return root;
    else{
        int counter = 1;
        for(int i=0; i<sizeRoot; ++i){
            NodeT<T>* travNode = root->nodes[i];
            while(travNode->symbols[0] != 0){
                if(counter == nState){
                    return travNode;   
                }
                else{
                    travNode = travNode->nodes[0];
                    ++counter;
                }
            }
            if(counter == nState)
                return travNode;
            ++counter;
        }
    }
}

template <class T>
DoubleList<DoubleList<string>> Tree<T>::afnMatrix(string str){
    DoubleList<char> colsSymbols;
    for(auto chr: str){
        if(!colsSymbols.is_in(chr))
            colsSymbols.push_back(chr);
    }
    DoubleList<DoubleList<string>> matrix;
    
    for(int i=0; i<sizeTree; ++i){
        string stateName = 'q'+to_string(i);
        NodeT<T>* node = this->go_state(stateName);
        DoubleList<string> matrixRows;
        for(int j=0; j<colsSymbols.size(); ++j){
            if(i==0){
                string temp="";
                temp+=(root->stateName);
                for(int k=0; k<sizeRoot; ++k)
                    if(root->symbols[k] == colsSymbols[j])
                        temp+=(root->nodes[k]->stateName);
                matrixRows.push_back(temp);
            }
            else{
                if(node->symbols[0] == colsSymbols[j]){
                    matrixRows.push_back(node->nodes[0]->stateName);
                }
                else{
                    matrixRows.push_back(" ");
                }
            }
        }
        matrix.push_back(matrixRows);
    }
    return matrix;
}

DoubleList<int> mySplit(string str){
    DoubleList<int> splittedStr;
    string temp="";
    for(int i=1; i<str.size(); ++i){
        if(str[i] == 'q'){
            splittedStr.push_back(stoi(temp));
            temp="";
        }
        else{
            temp+=str[i];
        }
    }
    splittedStr.push_back(stoi(temp));
    return splittedStr;
}

DoubleList<string> convStrStatesToList(string states){
    DoubleList<string> statesList;
    string temp="q";
    for(int i=0; i<states.size(); ++i){
        if(states[i] == 'q'){
            statesList.push_back(temp);
            temp="q";
        }
        else{
            temp+=states[i];
        }
    }
    statesList.push_back(temp);
    return statesList;
}

bool is_in_OrdNotMatt(DoubleList<string> statesList, string state){
    DoubleList<DoubleList<string>> statesListSegmented;
    for(int i=0; i<statesList.size(); ++i)
        statesListSegmented.push_back(convStrStatesToList(statesList[i]));
    DoubleList<string> strStateSegmented = convStrStatesToList(state);
    for(int i=0; i<statesList.size(); ++i){
        bool verifyer = false;
        for(int j=0; j<strStateSegmented.size(); ++j){
            if(statesListSegmented[i].size() == strStateSegmented.size()){
                if(statesListSegmented[i].is_in(strStateSegmented[j]))
                    verifyer = true;
                else{
                    verifyer = false;
                    break;
                }
            }
        }
        if(verifyer)
            return true;
    }
    return false;
}

template <class T>
DoubleList<DoubleList<string>> Tree<T>::afdMatrix(string str){
    DoubleList<char> colsSymbols;
    for(auto chr: str){
        if(!colsSymbols.is_in(chr))
            colsSymbols.push_back(chr);
    }
    DoubleList<DoubleList<string>> afn = this->afnMatrix(str);
    DoubleList<string> matrixRows;
    DoubleList<DoubleList<string>> matrix;
    
    matrixRows.push_back("q0");
    int prevQStates = 1;
    
    for(int i=0; i<afn[0].size(); ++i){
        if(!is_in_OrdNotMatt(matrixRows, afn[0][i])){
            matrixRows.push_back(afn[0][i]);   
        }
    }
    matrix.push_back(afn[0]);
    
    int rowTraveler=0;
    while(true){
        int QStates = matrixRows.size();
        for(int i=prevQStates; i<QStates; ++i){
            DoubleList<string> row;
            for(int j=0; j<colsSymbols.size(); ++j){
                DoubleList<int> states = mySplit(matrixRows[i]);
                DoubleList<string> temp_str_list;
                string temp_str="";
                for(int k=0; k<states.size(); ++k){
                    if(afn[states[k]][j] != " " && !is_in_OrdNotMatt(temp_str_list, afn[states[k]][j])){
                        temp_str_list.push_back(afn[states[k]][j]);
                        temp_str+=afn[states[k]][j];
                    }
                }
                row.push_back(temp_str);
            }
            matrix.push_back(row);
        }
        for(int j=0 ; j<QStates-prevQStates; ++j){
            rowTraveler+=1;
            for(int i=0; i<colsSymbols.size(); ++i){
                if(!is_in_OrdNotMatt(matrixRows, matrix[rowTraveler][i])){
                    DoubleList<string> ListOfSomeStates = convStrStatesToList(matrix[rowTraveler][i]);
                    for(int k=0; k<ListOfSomeStates.size(); ++k){
                        if(this->afn_finalStates.is_in(ListOfSomeStates[k]))
                            afd_finalStates.push_back(matrix[rowTraveler][i]);
                    }
                    matrixRows.push_back(matrix[rowTraveler][i]);
                }   
            }
        }
        prevQStates = QStates;
        if(prevQStates == matrixRows.size()){
            break;
        }
    }
    matrix.push_back(matrixRows);
    return matrix;
}

template <class T> 
bool Tree<T>::evaluateStrInAfd(string strToEvaluate, string stringsFromAFD){
    DoubleList<DoubleList<string>> afd = this->afdMatrix(stringsFromAFD);
    DoubleList<string> afd_rows = afd[afd.size()-1];
    DoubleList<char> cols_symbols;
    for(auto chr: stringsFromAFD){
        if(!cols_symbols.is_in(chr))
            cols_symbols.push_back(chr);
    }
    QueueArray<string> sReached;
    sReached.enqueue(afd[0][0]);
    for(auto chr: strToEvaluate){
        string state = sReached.dequeue();
        int indxRow_state = afd_rows.is_in_index(state);
        int indxCol_symbol = cols_symbols.is_in_index(chr);
        if(indxCol_symbol == -1){
            sReached.enqueue(afd[0][0]);
        }
        else{
            if(this->afd_finalStates.is_in(afd[indxRow_state][indxCol_symbol]))
                return true;
            sReached.enqueue(afd[indxRow_state][indxCol_symbol]);
        }
    } 
    return false;    
}

#endif
