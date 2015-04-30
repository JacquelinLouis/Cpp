#ifdef __llvm__
#pragma GCC diagnostic ignored "-Wdangling-else"
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "classes.hpp"

using namespace std;

int getnumber(string line){
  string numb="";
  int i=2;
  while(i<line.size())
    numb+=line[i++];
  return atoi(numb.c_str());
}

int readfile(char *src){
  ABR *tree=NULL;
  string line, numb;
  int i=2;
  ifstream infile(src);
  while(getline(infile, line)){
    cout<<"Instruction "<<line<<endl;
    if(line[0]=='I'){
      if(tree==NULL){
	noeud *racine=nodinit(getnumber(line));
	tree=new ABR(racine);
	cout<<"Creation de l'arbre "<<getnumber(line)<<endl;
      }
      else{
	tree->Inserer(tree->GetRacine(), getnumber(line));
	cout<<"Insertion du noeud de valeur "<<getnumber(line)<<endl;
      }
    }
    else if(line[0]=='S'){
      if(tree!=NULL)
	if(line[1]==','){
	  tree->Supprimer(tree->GetRacine(), getnumber(line));
	  cout<<"Tentative de suppression du noeud de valeur "<<getnumber(line)<<endl;
	}
    }
    else if(line[0]=='A'){
      cout<<"Affichage de l'arbre"<<endl;
      tree->Afficher_Arbre(tree->GetRacine());
    }
    else if(line[0]=='H'){
      cout<<"Affichage de la hauteur"<<endl;
      cout<<tree->Afficher_hauteur(tree->GetRacine())<<endl;
    }
    else if(line[0]=='G'){
      if(line[1]==','){
	cout<<"Affichage des ascendants du noeud "<<getnumber(line)<<endl;
	tree->Afficher_Ascendant(tree->GetRacine(), getnumber(line));
      }
    }
    else if(line[0]=='T'){
      cout<<"Archivage"<<endl;
      tree->Archiver(tree->GetRacine());
    }
  }  
  return 0;
}

int main(int argc, char ** argv){
  if (argc==1)
    cout<<"Veuiller entrer le nom du fichier d'instructions a la suite de la commande d'execution du programme"<<endl;
  readfile(argv[1]);
  return 0;
}
