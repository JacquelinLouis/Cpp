#include <queue>
#include <stack>
#include <limits>
#include <math.h>
#include <boost/lexical_cast.hpp>

using namespace std;

struct noeud{
  int valeur;
  noeud *gauche, *droit;
};

bool feuille(noeud *node){
  return(node->gauche==NULL && node->droit==NULL);
}

void affichnode(noeud *n){
  if(n!=NULL){
    cout<<" "<<n->valeur<<endl;
    if(n->gauche!=NULL)
      cout<<n->gauche->valeur;
    else
      cout<<"*";
    if(n->droit!=NULL)
      cout<<" "<<n->droit->valeur<<endl;
    else
      cout<<" *"<<endl;
  }
  else
    cout<<" *"<<endl;
}

void agencer(int niveau){
  for(int i=0; i<niveau; ++i)
    cout<<" ";
}

int stoi(string src){
  return atoi(src.c_str());
}

noeud *nodinit(int d){
  noeud *node=new noeud();
  node->valeur=d;
  node->gauche=NULL;
  node->droit=NULL;
  return node;
}

int findmin(noeud *racine){
  if(racine->gauche==NULL)
    return racine->valeur;
  else
    return findmin(racine->gauche);
}

int findmax(noeud *racine){
  if(racine->droit==NULL)
    return racine->valeur;
  else
    return findmax(racine->droit);
}
 
int max(int a, int b){
  if(a<b)
    return b;
  return a;
}


int size(noeud *racine){
  if(racine==NULL)
    return 0;
  else
    return(1+size(racine->gauche)+size(racine->droit));
}

noeud *findnode(noeud *racine, int val){
  noeud *point;
  if(racine==NULL)
    return NULL;
  else{
    if(racine->valeur==val)
      return racine;
    else{
      if(val<racine->valeur)
	return findnode(racine->gauche, val);
      else
	return findnode(racine->droit, val);
    }  
  }
}

void rec_Supprimer(noeud *node, int d){
  if(node!=NULL){
    if(node->gauche!=NULL && node->gauche->valeur==d && feuille(node->gauche)){
	delete[] node->gauche;
	node->gauche=NULL;
    }
    else if(node->droit!=NULL && node->droit->valeur==d && feuille(node->droit)){
	delete[] node->droit;
	node->droit=NULL;
    }
    else if(node->valeur==d){
      if(node->gauche!=NULL){
	node->valeur=findmax(node->gauche);
	if(feuille(node->gauche)){
	  delete[] node->gauche;
	  node->gauche=NULL;
	}
	else
	  rec_Supprimer(node->gauche, node->valeur);
      }
      else if(node->droit!=NULL){
	node->valeur=findmin(node->droit);
	if(feuille(node->droit)){
	  delete[] node->droit;
	  node->droit=NULL;
	}
	else
	  rec_Supprimer(node->droit, node->valeur);
      }	  
    }
    else if(node->valeur>d){
      rec_Supprimer(node->gauche, d);
    }
    else{
      rec_Supprimer(node->droit, d);
    }
  }
}

string rec_Archiver(noeud* rac){
  string result="";
  if(rac!=NULL)
    result=boost::lexical_cast<string>(rac->valeur)+" "+rec_Archiver(rac->gauche)+" "+rec_Archiver(rac->droit);
  else
    result="/";
  return result;
}

class ABR{
private:
  noeud *racine;
public:
  ABR(noeud *rac){
    racine=rac;
  }

  ~ABR(){
    if(racine!=NULL){
      if(racine->gauche!=NULL)
	delete[] racine->gauche;
      if(racine->droit!=NULL)
	delete[] racine->droit;
      delete[] racine;
      racine=NULL;
    }
  }

  void Inserer(noeud *rac, int d){
    if(rac->valeur>d){
      if(rac->gauche!=NULL)
	Inserer(rac->gauche, d);
      else{
	rac->gauche=nodinit(d);
      }
    }
    else{
      if(rac->droit!=NULL)
	Inserer(rac->droit, d);
      else{
	rac->droit=nodinit(d);
      }
    }
  }
  
  void Supprimer(noeud *rac, int d){
    if(racine!=NULL){
      if(racine->valeur==d){
	if(feuille(racine)){
	  delete[] racine;
	  racine=NULL;
	}
	else if(racine->gauche==NULL && racine->droit!=NULL)
	  racine=racine->droit;
	else if(racine->gauche!=NULL && racine->droit==NULL)
	  racine=racine->gauche;
	else{
	  racine->valeur=findmax(racine->gauche);
	  rec_Supprimer(racine->gauche, racine->valeur);
	}
      }
      else{
	rec_Supprimer(racine, d);
      }
    }
  }

  //on insere et affiche l'element de l'arbre que si le pointeur associe a l'entier teste est different de NULL
  void Afficher_Arbre(noeud *rac){
    queue<int> myq;
    stack<int> mystack;
    int max=numeric_limits<int>::max();//marqueur de changement de niveau
    int min=numeric_limits<int>::min();//marqueur de feuille et noeud inexistant
    int niveau=Afficher_hauteur(racine)+1, premier=0;;
    if(rac!=NULL){
      myq.push(rac->valeur);
      myq.push(max);
      while(!myq.empty() && myq.size()>1){
	mystack.push(myq.front());
	if(myq.front()==max){//marque le changement de niveau
	  cout<<endl;
	  myq.push(max);
	  --niveau;
	  premier=0;
	}
	else if(myq.front()==min && niveau>0){
	  if(premier++==0)
	    agencer(niveau);
	  cout<<"*";
	  agencer(niveau/2);
	  myq.push(min);
	  myq.push(min);
	}
	else if(myq.front()!=min){
	  if(premier++==0)
	    agencer(niveau);
	  cout<<myq.front();
	  agencer(niveau/2);
	  if(findnode(rac, myq.front())->gauche!=NULL){
	    myq.push(findnode(rac, myq.front())->gauche->valeur);
	  }
	  else
	    myq.push(min);
	  if(findnode(rac, myq.front())->droit!=NULL)
	    myq.push(findnode(rac, myq.front())->droit->valeur);
	  else
	    myq.push(min);
	}
	myq.pop();
      }
    }

    //suppression du dernier niveau
    while(!mystack.empty() && mystack.top()==min)
      mystack.pop();
    mystack.pop();

    premier=0;
    niveau=1;

    cout<<"Affichage bonus de l'arbre"<<endl;
    while(!mystack.empty()){
      if(mystack.top()==max){
	cout<<endl;
	premier=0;
	++niveau;
      }
      else if(mystack.top()==min){
	if(premier++==0)
	  agencer(niveau);
	cout<<"*";
	agencer(niveau/2);
      }
      else{
	if(premier++==0)
	  agencer(niveau);
	cout<<mystack.top();
	agencer(niveau/2);
      }
      mystack.pop();
    }
    cout<<endl;
  }

  int Afficher_hauteur(noeud *rac){
    if(rac==NULL)
      return -1;
    else
      return 1+max(Afficher_hauteur(rac->gauche), Afficher_hauteur(rac->droit));
  }
  
  void Afficher_Ascendant(noeud *rac, int d){
    if(rac!=NULL){
      if(rac->gauche!=NULL && rac->gauche->valeur==d){
	cout<<rac->valeur<<endl;
	Afficher_Ascendant(racine, rac->valeur);
      }
      else
	Afficher_Ascendant(rac->gauche, d);
      if(rac->droit!=NULL && rac->droit->valeur==d){
	cout<<rac->valeur<<endl;
	Afficher_Ascendant(racine, rac->valeur);
      }
      else
	Afficher_Ascendant(rac->droit, d);
    }
  }

  void Archiver(noeud *rac){
    ofstream myfile("ABR_Archive.txt");
    string result="";
    if(rac!=NULL)
      result=boost::lexical_cast<string>(rac->valeur)+" "+rec_Archiver(rac->gauche)+" "+rec_Archiver(rac->droit);
    else
      result="/";
    myfile<<result<<"\n";
    cout<<result<<endl;
    myfile.close();
  }

  void Archiver2(noeud *rac){
    ofstream myfile("ABR_Archive.txt");
    int size=pow(2,Afficher_hauteur(rac)+1)-1, max=numeric_limits<int>::max();
    int *tab=new int[size+1];
    noeud *point;
    for(int o=1; o<size+1; ++o)
      tab[o]=1;
    if(racine==NULL)
      tab[1]=max;
    else
      tab[1]=racine->valeur;    
    for(int i=1; i<(size/2)+1; ++i){
      if(tab[i]==max){
	tab[i*2]=max;
	tab[i*2+1]=max;
      }
      else{
	point=findnode(racine, tab[i]);
	if(point->gauche!=NULL)
	  tab[i*2]=point->gauche->valeur;
	else
	  tab[2*i]=max;
	if(point->droit!=NULL)
	  tab[i*2+1]=point->droit->valeur;
	else
	  tab[i*2+1]=max;
      }
    }
    for(int j=1; j<size; ++j){
      if(tab[j]==max){
	myfile<<"/ ";
	cout<<"/ ";
      }
      else{
	myfile<<tab[j]<<' ';
	cout<<tab[j]<<' ';
      }
    }
    myfile<<'\n';
    cout<<'\n';
    myfile.close();
  }

  noeud *GetRacine(){
    return racine;
  }
  
  void SetRacine(noeud *rac){
    racine=rac;
  }
};
