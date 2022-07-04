#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <iostream>
#include <string>
#include <chrono>
#include "double.h"
#include "tree.h"
#include "queue.h"

class AFN{
private:
    DoubleList<char> alfabeto;
    DoubleList<DoubleList<char>> T;
    DoubleList<string> Tstr;
    Tree<char> structure;
    int nEstados;
    
public:
    AFN();
    AFN(string alfabeto, int n);
    AFN(string alfabeto);
    void set_alfa(string alfa);
    void set_t(string t);
    void set_tstr(string t);
    void display_alfabeto();
    void display_T();
    void insert_states();
    void display_structure();
    void set_adjList();
    void get_adjList();
    void test_str(string str);
    void test_str_afd(string str);
    
};

AFN::AFN(string alfabeto, int n){
    for(auto chr: alfabeto)
        this->alfabeto.push_back(chr);
    nEstados = n;
};

AFN::AFN(){
};


void AFN::set_alfa(string alfabeto){
    for(auto chr: alfabeto)
        this->alfabeto.push_back(chr);
};

void AFN::set_t(string t){
    DoubleList<char> aux;
    for(auto chr: t)
        aux.push_back(chr);
    this->T.push_back(aux);
}

void AFN::set_tstr(string t){
    this->Tstr.push_back(t);
}

void AFN::display_alfabeto(){
    for(int i = 0; i<this->alfabeto.size(); i++){
        cout<<alfabeto[i]<<" "; 
    } cout<<endl;
}

void AFN::display_T(){
    for(int i=0; i<this->T.size(); ++i){
        for(int j=0; j<this->T[i].size(); ++j){
            cout<<this->T[i][j]<<" ";
        } cout<<endl;
    }
}

void AFN::insert_states(){
    for(int i=0; i<Tstr.size(); ++i)
        structure.insert(Tstr[i]);
}

void AFN::display_structure(){
    structure.displayTree();
}

void AFN::get_adjList(){
    DoubleList<DoubleList<string>> adjList = structure.adjList();
    for(int i=0; i<adjList.size(); ++i){
        cout<<adjList[i][0]<<": ";
        for(int j=1; j<adjList[i].size(); ++j){
            cout<<adjList[i][j]<<" ";
        } cout<<endl;
    }
}

void AFN::test_str(string str){
    cout<<boolalpha<<this->structure.testString(str)<<endl;
}

void AFN::test_str_afd(string str){
    string concatenatedString="";
    for(int i=0; i<this->Tstr.size(); ++i)
        concatenatedString+=Tstr[i];
    cout<<boolalpha<<this->structure.evaluateStrInAfd(str, concatenatedString)<<endl;
};


#endif
