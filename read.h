#ifndef READ_H
#define READ_H
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include "double.h"
#include "tree.h"
#include "queue.h"
#include "automaton.h"
using namespace std;


void test_files_afn(string textname){
  ifstream someStream(textname);
  string line;

  getline( someStream, line );
  AFN afn;
  afn.set_alfa(line);
  int end_count;
  int end_count2;
  int counter = 2;

  while( !someStream.eof() ) {
    getline( someStream, line );
    if(counter==2){
      end_count= stoi(line);
    }
      
    else if(counter>2 &&  counter<=2+end_count){
      afn.set_tstr(line.substr(0, line.size() - 1)); 
    }
    else if(counter==3+end_count){
      afn.insert_states();
    }
      
    else if(counter>3+end_count){
      afn.test_str(line);
    }
    ++counter;    
  }
}


void test_files_afd(string textname){
  ifstream someStream(textname);
  string line;

  getline( someStream, line );
  AFN afn;
  afn.set_alfa(line);
  int end_count;
  int end_count2;
  int counter = 2;

  while( !someStream.eof() ) {
    getline( someStream, line );
    if(counter==2){
      end_count= stoi(line);
    }
      
    else if(counter>2 &&  counter<=2+end_count){
      afn.set_tstr(line.substr(0, line.size() - 1)); 
    }
    else if(counter==3+end_count){
      afn.insert_states();
    }
      
    else if(counter>3+end_count){
      afn.test_str_afd(line);
    }
    ++counter;    
  }
}

string test_p4_syms(string textname){
  ifstream someStream(textname);
  string line;

  string syms;
  string vars;
  int n=0;
  DoubleList<string> rules;


  int counter = 0;
  while( !someStream.eof()) {
    getline( someStream, line );
    if(counter==0){
        syms=line;
    }
    
    else if(counter==1){
      vars = line;
    }
    else if(counter==2){
      n = stoi(line);
    }
    else if(counter>2){
      rules.push_back(line);
    }
    counter=counter+1;   
  }
  return syms;
}



string test_p4_vars(string textname){
  ifstream someStream(textname);
  string line;

  string syms;
  string vars;
  int n=0;
  DoubleList<string> rules;


  int counter = 0;
  while( !someStream.eof()) {
    getline( someStream, line );
    if(counter==0){
        syms=line;
    }
    
    else if(counter==1){
      vars = line;
    }
    else if(counter==2){
      n = stoi(line);
    }
    else if(counter>2){
      rules.push_back(line);
    }
    counter=counter+1;   
  }
  return vars;
}


int test_p4_n(string textname){
  ifstream someStream(textname);
  string line;

  string syms;
  string vars;
  int n=0;
  DoubleList<string> rules;


  int counter = 0;
  while( !someStream.eof()) {
    getline( someStream, line );
    if(counter==0){
        syms=line;
    }
    
    else if(counter==1){
      vars = line;
    }
    else if(counter==2){
      n = stoi(line);
    }
    else if(counter>2){
      rules.push_back(line);
    }
    counter=counter+1;   
  }
  return n;
}


DoubleList<string> test_p4_rules(string textname){
  ifstream someStream(textname);
  string line;
  string syms;
  string vars;
  int n=0;
  DoubleList<string> rules;


  int counter = 0;
  while( !someStream.eof()) {
    getline( someStream, line );
    if(counter==0){
        syms=line;
    }
    
    else if(counter==1){
      vars = line;
    }
    else if(counter==2){
      n = stoi(line);
    }
    else if(counter>2){
        
        string word = "";
        for (auto x : line)
        {
            if (x == ' ')
            {
                rules.push_back(word);
                word = "";
            }
            else {
                word = word + x;
            }
    }
    rules.push_back(word);
    }
    
    counter=counter+1;   
  }

  return rules;
}

#endif