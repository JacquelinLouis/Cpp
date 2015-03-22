#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

string operer(char ope, string left, string right){
  int result=0, l=atoi(left.c_str()), r=atoi(right.c_str());
  stringstream out;
  if(ope=='+')
    result=l+r;
  if(ope=='-')
    result=l-r;
  if(ope=='*')
    result=l*r;
  if(ope=='/')
    result=l/r;
  if(ope=='%')
    result=l%r;
  out<<result;
  return out.str();
}

bool estoperateur(char val){
  return(val=='+' || val=='-' || val=='*' || val=='/' ||  val=='%');
}
bool estentier(char val){
  return(val<='9' && val>='0');
}

bool estsuperieur(char a, char b){
  return(((a=='('||a==')')&&(b!='(' && b!=')'))||((b=='+'||b=='-')&&(a!='+'&&a!='-')));
}

void afficherstack(stack<string> p){
  cout<<"top"<<endl;
  while(!p.empty()){
    cout<<p.top()<<endl;
    p.pop();
  }
  cout<<"down\n"<<endl;
}

//converti une string passee en parametre en un vector de char en se debarrassant au passage d'eventuels espaces
vector<char> stringtovect(string s){
  vector<char> vec;
  int i=0;
  while(i<s.size()){
    //on disseque les mots
    if(s[i]!=' ')
      vec.push_back(s[i]);
    ++i;
  }
  return vec;
}

class Prefixe{
 private:
  //les operateurs
  stack<string> pile;
  //les valeurs a utiliser
  vector<string> tableau;
 public:
  //constructeur
  Prefixe(){
  }
  //destructeur
  ~Prefixe(){
    while(!pile.empty()){
      pile.pop();
    }
    tableau.clear();
  }
  //fonction booleenne qui lit l'expression et verifie qu'elle ne contient que les caracteres permis
  bool lecture(vector<char> tab){
    bool valid=true;
    int i=0, quote=0;
    while(i<tab.size() && valid){
      if(tab[i]=='\'')
	++quote;
      if(!estentier(tab[i]) && !estoperateur(tab[i]) && tab[i]!='(' && tab[i]!=')' && tab[i]!='\''){
	valid=false;
	++i;
      }
      ++i;
    }
    return (valid && quote==2);
  }
  //verifie le nombre de parentheses et le nombre de nombres(quelle belle phrase) et d'operateurs
  bool valider_expression(vector<char> tab){
    int cpar=0;
    for(int i=0; i<tab.size(); ++i){
      if(tab[i]=='(')
	++cpar;
      if(tab[i]==')' && cpar>0)
	--cpar;
    }
    return cpar==0;;
  }

  
  //transforme le vector de char, passe en parametre, en vector de string pour regrouper les composantes des nombres. Modifie egalement le parametre "tableau" de la classe
  vector<string> transformernombres(vector<char> tab){
    vector<string> result;
    string tot="";
    int i=1;
    while(i<tab.size()){
      //chiffre ou nombre
      if(estentier(tab[i])){
	tot="";
	while(i<tab.size() && estentier(tab[i])){
	  tot+=tab[i];
	  ++i;
	}
	result.push_back(tot);
      }
      //operateur
      if(estoperateur(tab[i]) || tab[i]=='(' || tab[i]==')'){
	tot="";
	tot+=tab[i];
	result.push_back(tot);
      }
      ++i;
    }
    tableau=result;
    return result;
  }
  
  //le vector de char alterne des operateurs et des operandes, la stack "sta" est ici inutile, on utilisera le caractere ";" pour séparer les nombres
  void transformerenpostfixe(vector<char> vec){
    string right="", nbr="", tot="", separateur=" ";
    bool run=true;
    //les operandes sont type string pour pouvoir concatener les expressions
    stack<string> operand;
    stack<char> operat;
    while(!vec.empty()){
      if(vec.front()=='\'')
	vec.erase(vec.begin());
      else{
	if(estentier(vec.front())){
	  tot="";
	  //si le premier caractere lu est chiffre, il compose peut etre un nombre, il faut regrouper ses composantes
	  while(!vec.empty() && estentier(vec.front())){
	    tot+=vec.front();
	    vec.erase(vec.begin());
	  }
	  //on ajoute sur la pile des operandes
	  operand.push(tot);
	}
	//ce n'est pas un nombre
	else{
	  //si c'est une parenthese, la pile est vide, ou que l'operateur lut est prioritaire a celui en tete de pile
	  if((vec.front()=='(' || operat.empty() || estsuperieur(vec.front(), operat.top()))&&vec.front()!=')'){
	    operat.push(vec.front());
	    vec.erase(vec.begin());
	  }
	  else{
	    if(vec.front()==')'){
	      while(operat.top()!='('){
		//du fait de l'empilement, les operateur gauche et droit son inverses
		right=operand.top();
		//depiler l'operande droite
		operand.pop();
	       	right=(operat.top()+separateur+operand.top()+separateur+right);
		//depiler l'operande gauche
		operand.pop();
		//depiler l'operateur
		operat.pop();
		operand.push(right);
	      }
	      //depiler la parenthese "("
	      operat.pop();
	      vec.erase(vec.begin());
	    }
	    else{
	      //l'element est un operateur et n'est pas prioritaire par rapport au sommet de la pile operator
	      if(!estsuperieur(vec.front(), operat.top())){
		if(!operat.empty() && !estsuperieur(vec.front(), operat.top()) && operat.top()!='('){
		  right=operand.top();
		  operand.pop();
		  if(!operand.empty()){
		    right=(operat.top()+separateur+operand.top()+separateur+right);
		    operand.pop();
		    operat.pop();
		  }
		  operand.push(right);
		}
		operat.push(vec.front());
		vec.erase(vec.begin());
	      }
	    }
	  }
	}	
      }
    }
    //on rassemble l'expression
    while(!operat.empty()){
      right=operand.top();
      operand.pop();
      right=(operat.top()+separateur+operand.top()+separateur+right);
      operat.pop();
      operand.pop();
      operand.push(right);
    }
    pile=operand;
  }

  //calcule l'expression
  int evaluer_expression(string src){
    int resultat=0, i=0;
    string right="";
    stack<char> operat;
    stack<string> operand;
    bool precentier=false;
    while(i<src.size()){
      if(src[i]!=' '){
	if(estoperateur(src[i])){
	  operat.push(src[i]);
	  precentier=false;
	}
	if(i<src.size() && estentier(src[i])){
	  if(!precentier){
	    operand.push("");
	    while(i<src.size() && estentier(src[i]))
	      operand.top()+=src[i++];
	    precentier=true;
	  }
	  else{
	      right="";
	      //on assemble les composantes du nombre
	      while(i<src.size() && estentier(src[i]))
		right+=src[i++];
	      //on saute le separateur
	      right=operer(operat.top(), operand.top(), right);
	      operat.pop();
	      operand.pop();
	      operand.push(right);
	  }
	}
      }
      ++i;
    }
    while(!operat.empty()){
      right=operand.top();
      operand.pop();
      right=operer(operat.top(), operand.top(),right);
      operat.pop();
      operand.pop();
      operand.push(right);
    }
    resultat=atoi(operand.top().c_str());
    return resultat;
  }

  void affichertableau(){
    int i=0;
    cout<<"first :";
    if(!tableau.empty()){
      cout<<tableau[i++];
      while(i<tableau.size()){
	cout<<" "<<tableau[i++];
      }
    }
    cout<<": last"<<endl;
  }

  void afficherpile(){
    stack<string> copy=pile;
    cout<<"down"<<endl;
    while(!copy.empty()){
      cout<<copy.top()<<endl;
      copy.pop();
    }
    cout<<"top"<<endl;
  }

  stack<string> getpile(){
    return pile;
  }
  
  vector<string> gettableau(){
    return tableau;
  }
};
 #endif
