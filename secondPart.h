#include <iostream>
#include <string>
#include "automaton.h"
#include "random.h"
#include "read.h"
#include "queue.h"
#include "read.h"
using namespace std;

void insert_rules(DoubleList<string> leftRules, DoubleList<string> rightRules, DoubleList<string> rules){
  string left;
  string right;
  //for(int i = 0 ; i < rules.size() ; i++){
  //  left.push_back(rules[i][0]);
  //}
  //for(char x: rules){
    //while(x != ' '){
    //  left.push_back(x);
    //}
  //}
}

string algorythmP5(string syms, string vars, int n, DoubleList<string> rules){
    DoubleList<char> vSyms;
    DoubleList<char> vVars;
    DoubleList<string> leftRules;
    DoubleList<string> rightRules;
    for(int i=0; i<syms.size(); ++i){
        vSyms.push_back(syms[i]);
    }
    for(int i=0; i<vars.size(); ++i){
        vVars.push_back(vars[i]);
    }
  //
    for(int i=1; i<rules.size(); i+=2){
        rightRules.push_back(rules[i]);
    }
    for(int i=0; i<rules.size(); i+=2){
        leftRules.push_back(rules[i]);
    } 
  //
    DoubleList<char> generator;
    int changes = 0;
    do {
        changes = 0;
        for(int i=0; i<rightRules.size(); ++i){
            int symbolsOrGenCounter = 0;
            for(int j=0; j<rightRules.size(); ++j){
                if(vSyms.is_in(rightRules[i][j])){
                    ++symbolsOrGenCounter;
                    if(!generator.is_in(rightRules[i][j])){
                        generator.push_back(rightRules[i][j]);
                        ++changes;
                    }
                }
                else if(generator.is_in(rightRules[i][j])){
                    ++symbolsOrGenCounter;
                }
            }
            if(symbolsOrGenCounter==rightRules[i].size()){
                if(!generator.is_in(leftRules[i][0])){
                    generator.push_back(leftRules[i][0]);
                    ++changes;
                }
            }
        }
    } while(changes != 0);

    // En caso el S esté dentro de generator, entonces el lenguaje NO es vacio y retornamos NO    
    if(generator.is_in(leftRules[0][0])){
        return "NO";
    }
    // En caso el S NO esté dentro de generator, entonces el lenguaje SI es vacio y retornamos SI
    else{
        return "SI";
    }
}

void testP5(){
    string syms = test_p4_syms("text.txt");
    string vars = test_p4_vars("text.txt");
    int n = test_p4_n("text.txt");
    DoubleList<string> rules = test_p4_rules("text.txt");
    cout<<algorythmP5(syms, vars, n, rules)<<endl;
}


string algorythmP6(string syms, string vars, int n, DoubleList<string> rules){
    DoubleList<char> vSyms;
    DoubleList<char> vVars;
    DoubleList<string> leftRules;
    DoubleList<string> rightRules;
    DoubleList<int> count;
    
    for(int i=0; i<syms.size(); ++i){
        vSyms.push_back(syms[i]);
    }
    for(int i=0; i<vars.size(); ++i){
        vVars.push_back(vars[i]);
    }
    for(int i=1; i<rules.size(); i+=2){
        rightRules.push_back(rules[i]);
    }
    for(int i=0; i<rules.size(); i+=2){
        leftRules.push_back(rules[i]);
    } 
    for(int i=1; i<rules.size(); i+=2){
        if(rules[i].size() > 1){
            count.push_back(rules[i].size());
        }
        else{
            if(vSyms.is_in(rules[i][0]))
                count.push_back(0);
            else{
                count.push_back(1);
            }
        }
    }

    //Variables[Sin repetir]
    DoubleList<char> vVarsNoRep;
    for(int i=0; i<leftRules.size(); ++i){
        if(!vVarsNoRep.is_in(leftRules[i][0])){
            vVarsNoRep.push_back(leftRules[i][0]);
        }
    }

    //Generate?
    DoubleList<DoubleList<string>> validation;
    for(int i=0; i<vVarsNoRep.size(); ++i){
        DoubleList<string> temp;
        string var(1, vVarsNoRep[i]);
        temp.push_back(var);
        temp.push_back("NO");
        validation.push_back(temp);
    }

    
    //Listas de adyacencia con las posiciones de los iguales a las variables a la cual corresponden
    DoubleList<DoubleList<int>> adjListPosGen;
    for(int i=0; i<vVarsNoRep.size(); ++i){
        //Lista con las posiciones de sus iguales
        /* Nota: Las posiciones son en función del cómo es que las reglas han ido entrando 
            siendo la posición 0 la de la fila 0 y así sucesivamente */
        DoubleList<int> adjListPosInd;
        for(int j=0; j<rightRules.size(); ++j){
            for(int k=0; k<rightRules[j].size(); ++k){
                if(vVarsNoRep[i] == rightRules[j][k]){
                    adjListPosInd.push_back(j);
                }
            }
        }
        adjListPosGen.push_back(adjListPosInd);
    }
    
    QueueArray<char> cStack; //Container stack: Un simple contenedor
    DoubleList<char> mStack; //Memory stack: Un stack que recuerda (aquel que no ejerce pop)
    for(int i=0; i<rightRules.size(); ++i){
        if(rightRules[i].size() == 1){
            if(vSyms.is_in(rightRules[i][0])){
                cStack.enqueue(leftRules[i][0]);
                mStack.push_back(leftRules[i][0]);
            }
        }
    }
    
    while(!(cStack.is_empty())){
        char var = cStack.dequeue();
        for(int i=0; i<vVarsNoRep.size(); ++i){
            if(vVarsNoRep[i] == var){
                for(int j=0; j<adjListPosGen[i].size(); ++j){
                    count[adjListPosGen[i][j]] -= 1;
                }
            }
        }
        //verificamos para este punto algún contador llegó a 0
        for(int i=0; i<count.size(); ++i){
            if(count[i] == 0){
                if(!mStack.is_in(leftRules[i][0])){
                    cStack.enqueue(leftRules[i][0]);
                    mStack.push_back(leftRules[i][0]);
                }
            }
        }
        
    }
    
    for(int i=0; i<validation.size(); ++i){
        if(mStack.is_in(validation[i][0][0])){
            validation[i][1] = "SI";
        }
    }

    if(validation[0][1] == "SI")
        return "NO";
    else{
        return "SI";
    }
}

void testP6(){
    string syms = test_p4_syms("text.txt");
    string vars = test_p4_vars("text.txt");
    int n = test_p4_n("text.txt");
    DoubleList<string> rules = test_p4_rules("text.txt");
    cout<<algorythmP6(syms, vars, n, rules)<<endl;
}
