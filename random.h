#ifndef RANDOM_H
#define RANDOM_H

#include <chrono>
#include "automaton.h"
using namespace std;

class Timer {

chrono::system_clock::time_point m_start;

public:
Timer(){
  m_start = chrono::system_clock::now();
}
float get_duration(){
  auto end = chrono::system_clock::now();
  chrono::duration<float, milli> duration = end - m_start;
  float duration_ = duration.count();
  cout << duration.count() << " ms" << endl;
  return duration_;
}
};

string ASCII(){
  string ASCII_;
  
  /* for(char i = '!' ; i <= '~' ; ++i){
    ASCII_.push_back(i);
  } */
  
  for(char i = 'A' ; i <= 'Z' ; ++i){ // solo el alfabeto
    ASCII_.push_back(i);
  }
  return ASCII_;
}


string alfabeto(string ASCII_){
    
  srand(time(NULL));
    
  int size_A = (std::rand() % ASCII_.length());
  string A; 
  
  for(int i = 0 ; i < size_A ; ++i){
    char C = ASCII_[(std::rand() % ASCII_.length()-1)];
    A.push_back(C);
  }

  cout << "Alfabeto: " << endl;
  for(int i = 0 ; i < size_A ; i++){
    cout << A[i] << ((i % 16 == 15) ? '\n' : ' ');
  }
    cout<<endl<<endl;

    return A;
  }
DoubleList<string> cadenas(string alfab, int cnt_max_long_cdns, int cant_cadenas){
  
  cout << "Cantidad de cadenas = " << cant_cadenas <<  endl << endl;

  DoubleList<string> T; 
  for(int i = 0 ; i < cant_cadenas ; ++i){
    
    int size_of_each_string = ((std::rand() % cnt_max_long_cdns)+1);
    string temp;
    
    for(int j = 0 ; j < size_of_each_string ; j++){
      temp.push_back(alfab[(std::rand() % alfab.size())]);
    }
    
    T.push_back(temp);
    temp = "";
    
    
    cout << "cadena T" << i << " con tamanio " << size_of_each_string << ':' << endl;
    for(int x = 0 ; x < size_of_each_string ; x++){
      cout << T[i][x];
    }
    
    cout << endl << endl;
    
    
  }
  return T;
}
void p1_test_random(string alfab, int cant_cadenas, DoubleList<string> cadenas_){
    AFN afn = AFN(alfab, cant_cadenas);
    for(int g = 0 ; g < cant_cadenas ; g++){
      afn.set_tstr(cadenas_[g]);
    }
    afn.insert_states();
    afn.get_adjList();
}
float generador_random_1(int cant_cadenas){
  Timer Tr1;
  const int cnt_max_long_cdns = cant_cadenas;
  string ASCII_ = ASCII();
  string alfab = alfabeto(ASCII_); 
  // un subconjunto aleatorio de los valores ASCII
  DoubleList<string> cadenas_ = cadenas(alfab, cnt_max_long_cdns, cant_cadenas);

  p1_test_random(alfab, cant_cadenas, cadenas_);  
  return Tr1.get_duration();
}

DoubleList<string> S(DoubleList<string> cadenas_, string alfab, int cant_cadenas){
  DoubleList<string> S;
  string temp;
  for(int i = 0 ; i < cant_cadenas ; i++){
    int length_cadena = ((std::rand() % cant_cadenas)+1); 
    
    for(int j = 0 ; j < length_cadena ; j++){
      temp.push_back(alfab[(std::rand() % alfab.size())]);
      }
    S.push_back(temp);
    temp="";
    
   cout << "cadena S" << i << " con tamanio " << S[i].size() << ':' << endl;
    for(int x = 0 ; x < S[i].size() ; x++){
      cout << S[i][x];
    }
    
    cout << endl << endl;
    
  }
  return S;
}

void p2_test_random(string alfab, int cant_cadenas, DoubleList<string> cadenas_, DoubleList<string> S_){
    AFN afn = AFN(alfab, cant_cadenas);
    for(int g = 0 ; g < cant_cadenas ; g++){
      afn.set_tstr(cadenas_[g]);
    }
    afn.insert_states();
    //afn.get_adjList();
  
    for(int i = 0 ; i < S_.size() ; i++){
      afn.test_str(S_[i]);
    }
}

float generador_random_2(int cant_cadenas){
  Timer Tr2;
  const int cnt_max_long_cdns = cant_cadenas; 
  // tamanio maximo de las cadenas
  string ASCII_ = ASCII();
  string alfab = alfabeto(ASCII_);
  // un subconjunto aleatorio de los valores ASCII
  DoubleList<string> cadenas_ = cadenas(alfab, cnt_max_long_cdns, cant_cadenas);
  DoubleList<string> S_ = S(cadenas_, alfab, cant_cadenas);

  p2_test_random(alfab, cant_cadenas, cadenas_, S_);  
  return Tr2.get_duration();
}

void p3_test_random(string alfab, int cant_cadenas, DoubleList<string> cadenas_, DoubleList<string> S_){
    AFN afn = AFN(alfab, cant_cadenas);
    for(int g = 0 ; g < cant_cadenas ; g++){
      afn.set_tstr(cadenas_[g]);
    }
    afn.insert_states();
    //afn.get_adjList();
  
    for(int i = 0 ; i < S_.size() ; i++){
      afn.test_str_afd(S_[i]);
    }
}

float generador_random_3(int cant_cadenas){
  Timer Tr3;
  const int cnt_max_long_cdns = cant_cadenas; 
  // tamanio maximo de las cadenas
  string ASCII_ = ASCII();
  string alfab = alfabeto(ASCII_);
  // un subconjunto aleatorio de los valores ASCII
  DoubleList<string> cadenas_ = cadenas(alfab, cnt_max_long_cdns, cant_cadenas);
  DoubleList<string> S_ = S(cadenas_, alfab, cant_cadenas);

  p3_test_random(alfab, cant_cadenas, cadenas_, S_);  
  return Tr3.get_duration();
}

//--------------------time-------------------------------

string alfabeto_t(string ASCII_){
    
  srand(time(NULL));
    
  int size_A = (std::rand() % ASCII_.length());
  string A; 
  
  for(int i = 0 ; i < size_A ; ++i){
    char C = ASCII_[(std::rand() % ASCII_.length()-1)];
    A.push_back(C);
  }
/*
  cout << "Alfabeto: " << endl;
  for(int i = 0 ; i < size_A ; i++){
    cout << A[i] << ((i % 16 == 15) ? '\n' : ' ');
  }
    cout<<endl<<endl;
*/
    return A;
  }
DoubleList<string> cadenas_t(string alfab, int cnt_max_long_cdns, int cant_cadenas){
  
  //cout << "Cantidad de cadenas = " << cant_cadenas <<  endl << endl;

  DoubleList<string> T; 
  for(int i = 0 ; i < cant_cadenas ; ++i){
    
    int size_of_each_string = ((std::rand() % cnt_max_long_cdns)+1);
    string temp;
    
    for(int j = 0 ; j < size_of_each_string ; j++){
      temp.push_back(alfab[(std::rand() % alfab.size())]);
    }
    
    T.push_back(temp);
    temp = "";
    
    /*
    cout << "cadena " << i << " con tamanio " << size_of_each_string << ':' << endl;
    for(int x = 0 ; x < size_of_each_string ; x++){
      cout << T[i][x];
    }
    
    cout << endl << endl;
    */
    
  }
  return T;
}
void p1_test_random_t(string alfab, int cant_cadenas, DoubleList<string> cadenas_){
    AFN afn = AFN(alfab, cant_cadenas);
    for(int g = 0 ; g < cant_cadenas ; g++){
      afn.set_tstr(cadenas_[g]);
    }
    afn.insert_states();
    //afn.get_adjList();
}
float generador_random_1_t(int cant_cadenas){
  Timer Tr1;
  const int cnt_max_long_cdns = cant_cadenas;
  string ASCII_ = ASCII();
  string alfab = alfabeto_t(ASCII_); 
  // un subconjunto aleatorio de los valores ASCII
  DoubleList<string> cadenas_ = cadenas_t(alfab, cnt_max_long_cdns, cant_cadenas);

  p1_test_random_t(alfab, cant_cadenas, cadenas_);  
  return Tr1.get_duration();
}

DoubleList<string> S_t(DoubleList<string> cadenas_, string alfab, int cant_cadenas){
  DoubleList<string> S;
  string temp;
  for(int i = 0 ; i < cant_cadenas ; i++){
    int length_cadena = (std::rand() % cant_cadenas); 
    
    for(int j = 0 ; j < length_cadena ; j++){
      temp.push_back(alfab[(std::rand() % alfab.size())]);
      }
    S.push_back(temp);
    temp="";
    
    //cout << "cadena S" << i << " con tamanio " << S[i].size() << ':' << endl;
    //for(int x = 0 ; x < S[i].size() ; x++){
    //  cout << S[i][x];
    //}
    
    //cout << endl << endl;
    
  }
  return S;
}

void p2_test_random_t(string alfab, int cant_cadenas, DoubleList<string> cadenas_, DoubleList<string> S_){
    AFN afn = AFN(alfab, cant_cadenas);
    for(int g = 0 ; g < cant_cadenas ; g++){
      afn.set_tstr(cadenas_[g]);
    }
    afn.insert_states();
    //afn.get_adjList();
  
    for(int i = 0 ; i < S_.size() ; i++){
      afn.test_str(S_[i]);
    }
}

float generador_random_2_t(int cant_cadenas){
  Timer Tr2;
  const int cnt_max_long_cdns = cant_cadenas; 
  // tamanio maximo de las cadenas
  string ASCII_ = ASCII();
  string alfab = alfabeto_t(ASCII_);
  // un subconjunto aleatorio de los valores ASCII
  DoubleList<string> cadenas_ = cadenas_t(alfab, cnt_max_long_cdns, cant_cadenas);
  DoubleList<string> S_ = S_t(cadenas_, alfab, cant_cadenas);

  p2_test_random_t(alfab, cant_cadenas, cadenas_, S_);  
  return Tr2.get_duration();
}

void p3_test_random_t(string alfab, int cant_cadenas, DoubleList<string> cadenas_, DoubleList<string> S_){
    AFN afn = AFN(alfab, cant_cadenas);
    for(int g = 0 ; g < cant_cadenas ; g++){
      afn.set_tstr(cadenas_[g]);
    }
    afn.insert_states();
    //afn.get_adjList();
  
    for(int i = 0 ; i < S_.size() ; i++){
      afn.test_str_afd(S_[i]);
    }
}

double generador_random_3_t(int cant_cadenas){
  Timer Tr3;
  const int cnt_max_long_cdns = cant_cadenas; 
  // tamanio maximo de las cadenas
  string ASCII_ = ASCII();
  string alfab = alfabeto_t(ASCII_);
  // un subconjunto aleatorio de los valores ASCII
  DoubleList<string> cadenas_ = cadenas_t(alfab, cnt_max_long_cdns, cant_cadenas);
  DoubleList<string> S_ = S_t(cadenas_, alfab, cant_cadenas);

  p3_test_random_t(alfab, cant_cadenas, cadenas_, S_);  
  return Tr3.get_duration();
}

void mean_(DoubleList<double> mean, int rep){
  float sum = 0;
  for(int j = 0 ; j < mean.size() ; j++){  
    sum = sum + mean[j];
  }
  //return sum/rep;
  cout << endl << "promedio: " << sum/rep << " ms";
}

void tiempos1(int tam, int rep){
  DoubleList<double> mean;
  for(int i = 0 ; i < rep ; i++){
    mean.push_back(generador_random_1_t(tam));
  }
  mean_(mean, tam);
}

void tiempos2(int tam, int rep){
  DoubleList<double> mean;
  for(int i = 0 ; i < rep ; i++){
    mean.push_back(generador_random_2_t(tam));
  }
  mean_(mean, tam);
}

void tiempos3(int tam, int rep){
  DoubleList<double> mean;
  for(int i = 0 ; i < rep ; i++){
    mean.push_back(generador_random_3_t(tam));
  }
  mean_(mean, tam);
}


//-------------------------------- segunda parte



string algorythm_P5(string syms, string vars, int n, DoubleList<string> rules){
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
    for(int i=1; i<rules.size(); i+=2){
        rightRules.push_back(rules[i]);
    }
    for(int i=0; i<rules.size(); i+=2){
        leftRules.push_back(rules[i]);
    } 
    
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
        /*
        for(int i=0; i<generator.size(); ++i){
            //cout<<generator[i]<<" ";
        } cout<<endl;
        */
    } while(changes != 0);

    // En caso el S esté dentro de generator, entonces el lenguaje NO es vacio y retornamos NO    
    if(generator.is_in(leftRules[0][0])){
        //cout<<leftRules[0][0]<<endl;
        return "NO";
    }
    // En caso el S NO esté dentro de generator, entonces el lenguaje SI es vacio y retornamos SI
    else{
        return "SI";
    }
}

string algorythm_P6(string syms, string vars, int n, DoubleList<string> rules){
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
    DoubleList<char> mStack; //Memory stack: Un stack que recuerdo (aquel que no ejerce pop)
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

char get_terminal(){
  char a;
  int z = (std::rand() % 26);
  int c = 0;
  for(char i = 'a'; i <= 'z' ; i++){
    if(c==z){
      a=i;
    }
    c++;
  }
  return a;
}

char get_var(){
  char a;
  int z = (std::rand() % 26);
  int c = 0;
  for(char i = 'A'; i <= 'Z' ; i++){
    if(c==z){
      a=i;
    }
    c++;
  }
  return a;
}


char get_symbol(string vars, string terminal){
  char rpta;
  string symbols = vars+terminal;
  int rand = (std::rand() % symbols.length());
  
  for(int i = 0; i < symbols.length() ; i++){
      if(i == rand){
        rpta = symbols[i];
      }
  }
  return rpta;
}


float generador_random_5_t(int tam){
  Timer Tr5;

  int size_terminal = (std::rand() % 26);
  int size_variables = (std::rand() % 26);
  string terminal;
  string vars;
  string symbol;

  for(int i = 0 ; i < size_terminal ; i++){
    terminal.push_back(get_terminal());
  }
  
  for(int i = 0 ; i < size_variables ; i++){
    vars.push_back(get_var());
  }

  for(int i = 0 ; i < size_variables+size_terminal ; i++){
    symbol.push_back(get_symbol(vars,terminal));
  }
  
  int n = tam;
  DoubleList<string> rules;
  for(int i = 0 ; i < tam*2 ; i++){
    if(i%2==0){ //par
      string aux1(1, vars[i]);
      rules.push_back(aux1);  
    } else {
      string aux2((std::rand() % 4)+1, symbol[i]);
      rules.push_back(aux2);  
    }
  }
  cout<<algorythm_P5(terminal, vars, n, rules)<<endl;
  
  return Tr5.get_duration();
}

float generador_random_6_t(int tam){
  Timer Tr6;

  int size_terminal = (std::rand() % 26);
  int size_variables = (std::rand() % 26);
  string terminal;
  string vars;
  string symbol;

  for(int i = 0 ; i < size_terminal ; i++){
    terminal.push_back(get_terminal());
  }
  
  for(int i = 0 ; i < size_variables ; i++){
    vars.push_back(get_var());
  }

  for(int i = 0 ; i < size_variables+size_terminal ; i++){
    symbol.push_back(get_symbol(vars,terminal));
  }
  
  int n = tam;
  DoubleList<string> rules;
  for(int i = 0 ; i < tam*2 ; i++){
    if(i%2==0){ //par
      string aux1(1, vars[i]);
      rules.push_back(aux1);  
    } else {
      string aux2((std::rand() % 4)+1, symbol[i]);
      rules.push_back(aux2);  
    }
  }
  cout<<algorythm_P6(terminal, vars, n, rules)<<endl;
  
  return Tr6.get_duration();
}



void tiempos5(int tam){
  generador_random_5_t(tam);
}

void tiempos6(int tam){
  generador_random_6_t(tam);
}

#endif