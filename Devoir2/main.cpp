#include "classes.h"
#include <iostream>

using namespace std;

void affichervector(vector<char> myvect){
  cout<<"votre vector : ";
  for(int i=0; i<myvect.size(); ++i){
    cout<<myvect[i]<<" ";
  }
  cout<<endl;
}

int main (int argc, char **argv){
  Prefixe *pre=new Prefixe();
  string s="";
  int result=0;
  //vector<char> vec=chartovect(argc, argv);
  cout<<"Entrez la chaine de caracteres a evaluer 'entre deux quotes' sans espaces, les operateur separant les operandes :"<<endl;
  cin>>s;
  cout<<"Vous avez entre la chaine "<<s<<"\n"<<endl;
  vector<char> vec=stringtovect(s);
  if(pre->lecture(vec)){
    cout<<"Chaine valide\n"<<endl;
    if(pre->valider_expression(vec)){
      cout<<"Nombre de parentheses valide\n"<<endl;
      pre->transformernombres(vec);
      cout<<"Transformation en nombres acheve\n"<<endl;
      pre->transformerenpostfixe(vec);
      cout<<"Transformation en postfixe acheve\n"<<endl;
      afficherstack(pre->getpile());
      result=pre->evaluer_expression(pre->getpile().top());
      cout<<"Evaluation de l'expression achevee"<<endl;
      cout<<result<<endl;
    }
    else{
      cout<<"/!\\ Nombre ou placement des parentheses non valide\n"<<endl;
    }
  }
  else{ 
    cout<<"/!\\ Mauvaise expression : verifiez les caracteres (n'oubliez pas les quotes, votre expression doit avoir la forme : 'a+b*(c-d)/e'\n"<<endl;
  }  
  return 0;
}
