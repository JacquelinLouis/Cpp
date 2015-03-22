#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int getsize(char *elt){
  int count=0;
  if(elt!='\0'){
    while(elt[count]!='\0'){
      ++count;
    }
  }
  return count+1;
}

//Structure tab qui lie un cours "sigle", un entier "nb" et pointe sur un successeur "suivant"
struct tab{
  char* sigle;
  int value;
  tab* suivant;
};

struct Cours{
  char  *sigle;
  Cours *suivant;
};

struct Etudiants{
  char *nom;
  Etudiants *apres;
};

struct Professeur{
  char *nom;
  char *prenom;
  Cours *listecours;
  Etudiants *listetudiants;
  Professeur *suivant;
};

class DossierProfesseur{
  private:
  Professeur *tete;
  
 public:  
  DossierProfesseur(char *FP){
    string line;
    Professeur *curpro;
    Cours *curco;
    Etudiants *curet;
    ifstream infile(FP);
    //première itération, initialisation de tete
    if(getline(infile, line)){
      tete=new Professeur();
      curpro=tete;
      //nom
      curpro->nom=new char[line.size()+1];
      copy(line.begin(), line.end(), curpro->nom);
      curpro->nom[line.size()]='\0';
      //prenom
      if(getline(infile, line)){
	curpro->prenom=new char[line.size()+1];
	copy(line.begin(), line.end(), curpro->prenom);
	curpro->prenom[line.size()]='\0';
      }
      //cours
      if(getline(infile, line) && line !="&"){
	curpro->listecours=new Cours();
	curco=tete->listecours;
	curco->sigle=new char[line.size()+1];
	copy(line.begin(), line.end(), curco->sigle);
	curco->sigle[line.size()]='\0';
	while(getline(infile, line) && line!="&"){
	  curco->suivant=new Cours();
	  curco=curco->suivant;
	  curco->sigle=new char[line.size()+1];
	  copy(line.begin(), line.end(), curco->sigle);
	  curco->sigle[line.size()]='\0';
	}
	curco->suivant=NULL;
      }
      else{
	tete->listecours=NULL;
      }
      //etudiants
      if(getline(infile, line) && line !="&"){
	curpro->listetudiants=new Etudiants();
	curet=tete->listetudiants;
	curet->nom=new char[line.size()+1];
	copy(line.begin(), line.end(), curet->nom);
	curet->nom[line.size()]='\0';
	while(getline(infile, line) && line!="&"){
	  curet->apres=new Etudiants();
	  curet=curet->apres;
	  curet->nom=new char[line.size()+1];
	  copy(line.begin(), line.end(), curet->nom);
	  curet->nom[line.size()]='\0';
	}
	curet->apres=NULL;
      }
      else{
	tete->listetudiants=NULL;
      }
      //iteration pour construire les Professeurs suivants tant qu'on lit dans FP
      curpro=tete;
      while(getline(infile, line)){
	curpro->suivant=new Professeur();
	curpro=curpro->suivant;
	//nom
	curpro->nom=new char[line.size()+1];
	copy(line.begin(), line.end(), curpro->nom);
	curpro->nom[line.size()]='\0';
	//prenom
	if(getline(infile, line)){
	  curpro->prenom=new char[line.size()+1];
	  copy(line.begin(), line.end(), curpro->prenom);
	  curpro->prenom[line.size()]='\0';
	}
	//cours
	if(getline(infile, line) && line !="&"){
	  curpro->listecours=new Cours();
	  curco=curpro->listecours;
	  curco->sigle=new char[line.size()+1];
	  copy(line.begin(), line.end(), curco->sigle);
	  curco->sigle[line.size()]='\0';
	  while(getline(infile, line) && line!="&"){
	    curco->suivant=new Cours();
	    curco=curco->suivant;
	    curco->sigle=new char[line.size()+1];
	    copy(line.begin(), line.end(), curco->sigle);
	    curco->sigle[line.size()]='\0';
	  }
	  curco->suivant=NULL;
	}
	else{
	  curpro->listecours=NULL;
	}
	//etudiants
	if(getline(infile, line) && line !="&"){
	  curpro->listetudiants=new Etudiants();
	  curet=curpro->listetudiants;
	  curet->nom=new char[line.size()+1];
	  copy(line.begin(), line.end(), curet->nom);
	  curet->nom[line.size()]='\0';
	  while(getline(infile, line) && line!="&"){
	    curet->apres=new Etudiants();
	    curet=curet->apres;
	    curet->nom=new char[line.size()+1];
	    copy(line.begin(), line.end(), curet->nom);
	    curet->nom[line.size()]='\0';
	  }
	  curet->apres=NULL;
	}
	else{
	  curpro->listetudiants=NULL;
	}
      }
      //on oublie pas de fermer le fichier en sortant
      infile.close();
      curpro=NULL;
    }
  }
  
//fonction iterative qui libere les listes de cours et d'etudiants associees a la structure Professeur avant de liberer via la fonction delete les elements de la liste Professeur pointee par "tete"
  ~DossierProfesseur(){
    Professeur *par, *suppr=tete;
    Etudiants *paret, *supet;
    Cours *parco, *supco;
    while(suppr!=NULL){
      supco=suppr->listecours;
      delete [] suppr->nom;
      delete [] suppr->prenom;
      while(supco!=NULL){
	parco=supco;
	supco=supco->suivant;
	delete parco;
      }
      supet=suppr->listetudiants;
      while(supet!=NULL){
	paret=supet;
	supet=supet->apres;
	delete paret;
      }
      par=suppr;
      suppr=suppr->suivant;
      delete par;
    }
  }
  
  
  //fonction qui teste le nom et prenom du Professeur en cours avant de le supprimer ou de passer sur son suivant tant que celui-ci n'est pas null. A noter que renvoyer un entier ou un booleen aurait permis de savoir s'il avait ete supprime ou s'il n'etait pas present dans le Dossier Professeur.
  void supprimer(char *nom, char *prenom){
    Professeur *curpro=tete, *delpro=tete;
    Cours *curco, *delco;
    Etudiants *curet, *delet;
    if(tete!=NULL){
      if(strcmp(tete->nom,nom)==0 && strcmp(tete->prenom,prenom)==0){
	delpro=tete;
	tete=tete->suivant;
	delete[] delpro->nom;
	delete[] delpro->prenom;
	curco=delpro->listecours;
	while(curco!=NULL){
	  delco=curco;
	  curco=curco->suivant;
	  delete delco;
	}
	curet=delpro->listetudiants;
	while(curet!=NULL){
	  delet=curet;
	  curet=curet->apres;
	  delete delet;
	}
	delete delpro;
      }
      curpro=tete;
      while(curpro->suivant!=NULL){
	if(strcmp(curpro->suivant->nom, nom)==0 && strcmp(curpro->suivant->prenom, prenom)==0){
	  delpro=curpro->suivant;
	  curpro->suivant=curpro->suivant->suivant;
	  delete[] delpro->nom;
	  delete[] delpro->prenom;
	  curco=delpro->listecours;
	  while(curco!=NULL){
	    delco=curco;
	    curco=curco->suivant;
	    delete delco;
	  }
	  curet=delpro->listetudiants;
	  while(curet!=NULL){
	    delet=curet;
	    curet=curet->apres;
	    delete delet;
	  }
	  delete delpro;
	  return;
	}
	curpro=curpro->suivant;
	}
    }
  }

  //fonction iterative qui ne prend pas de parametre et parcours la liste des etudiants de chaque professeurs en incrementant un compteur qui est ensuite compare au maximum du nombre d'eleves obtenu jusqu'alors
  char *afficherleprofplusetudiant () const{
    Professeur *plus=tete, *parc=tete;
    int c=0, max=0;
    Etudiants *etu=parc->listetudiants;
    while(parc!=NULL){
      etu=parc->listetudiants;
      c=0;
      while(etu!=NULL){
	++c;
	etu=etu->apres;
      }
      if(max<c){
	max=c;
	plus=parc;
      }
      parc=parc->suivant;
    }
    return plus->nom;
  }

  //fonction iterative qui construit une liste chainee de type tab, et la parcours apres avoir parcouru le DossierProfesseur pour retourner le sigle ayant la plus grande valeur
  char *affichercoursplusdemande () const{
    tab *head=NULL, *my;
    int max=0;
    bool added=false;
    Cours *curco=tete->listecours;
    char *best;
    Professeur *curpro=tete;
    //parcours de la liste des professeurs
    while(curpro!=NULL){
      curco=curpro->listecours;
      //si la listecours n'est pas nulle, on créer un nouvel élément de type tab;
      if(head==NULL && curco!=NULL){
	head=new tab;
	head->sigle=new char[getsize(curco->sigle)];
	strncpy(head->sigle,curco->sigle,getsize(head->sigle));
	head->value=1;
	head->suivant=NULL;
      	curco=curco->suivant;
      }
      //on parcours les cours et on creer ou ajoute+1 aux cours 
      while(curco!=NULL){
	my=head;
	while(!added){
	  if(strcmp(my->sigle,curco->sigle)==0){
	    ++my->value;
	    added=true;
	  }
	  if(!added && my->suivant==NULL){
	    my->suivant=new tab;
	    my->suivant->sigle=new char[getsize(curco->sigle)];
	    strncpy(my->suivant->sigle, curco->sigle, getsize(curco->sigle));
	    my->suivant->value=1;
	    my->suivant->suivant=NULL;
	    added=true;
	  }
	  my=my->suivant;
	}
	my=head;
	added=false;
	curco=curco->suivant;
      }
      curpro=curpro->suivant;
    }
    //maintenant on parcours la liste pour chercher le cours le plus demande
    while(my!=NULL){
      if(my->value>max){
	max=my->value;
	best=my->sigle;
      }	
      my=my->suivant;
    }
    return(best); 
  }

  //fonction iterative qui parcours la liste de chaque professeur et incremente un compteur a chaque fois que le cours en question apparait.
  int affichernbreprofpouruncours(char *coursdonne) const{
    Professeur *curpro=tete;
    Cours* curco;
    int count=0;
    while(curpro!=NULL){
      curco=curpro->listecours;
      while(curco!=NULL){
	if(strcmp(curco->sigle,coursdonne)==0){
	  ++count;
	}
	curco=curco->suivant;
      }
      curpro=curpro->suivant;
    }
    return count;
  }
  
  //recopie la structure DossierProfesseur dans le fichier FP
  void recopier (char *FP){
    ofstream myfile(FP);
    Professeur *curpro=tete;
    Cours *curco;
    Etudiants *curet;
     if(myfile.is_open()){
       while(curpro!=NULL){
	 curco=curpro->listecours;
	 myfile<<curpro->nom<<endl;
	 myfile<<curpro->prenom<<endl;
	 while(curco!=NULL){
	   myfile<<curco->sigle<<endl;
	   curco=curco->suivant;
	 }
	 myfile<<"&"<<endl;
	 curet=curpro->listetudiants;
	 while(curet!=NULL){
	   myfile<<curet->nom<<endl;
	   curet=curet->apres;
	 }
	 if(curpro->suivant!=NULL){
	   myfile<<"&"<<endl;
	 }
	 curpro=curpro->suivant;
       }
      myfile.close();
    }
  }

  //retourne simplement le pointeur sur la tete du DossierProfesseur  
  Professeur *getete(){
    return tete;
  }
};

#endif
