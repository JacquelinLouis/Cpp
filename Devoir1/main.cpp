#include "classes.h"

//envoyer devoir a 8SIF109@gmail.com avec dossier en .zip, nommé en nom_prenom_codePermanent_TPnoTP.zip

using namespace std;

void afficherplusetudiant(DossierProfesseur *thisdos){
  cout<<thisdos->afficherleprofplusetudiant()<<endl;
}

void afficherplusdemande(DossierProfesseur *thisdos){
  cout<<thisdos->affichercoursplusdemande()<<endl;
}

void afficherprofcours(DossierProfesseur *thisdos, char *cours){
  cout<<thisdos->affichernbreprofpouruncours(cours)<<endl;
}

int afficherTest(){
  string test="This is a test";
  char *chatest=new char[test.size()+1];
  copy(test.begin(), test.end(), chatest);
  chatest[test.size()]='\0';
  cout<<chatest<<endl;
  return 0;
}

int afficherContenuFichier(char *FP){
  ifstream infile(FP);
  string line="";
  while(getline(infile, line)){
    char* chaline=new char[line.size()+1];
    copy(line.begin(), line.end(), chaline);
    chaline[line.size()]='\0';
    cout<<chaline<<endl;
    delete [] chaline;
  }
  return 0;
}

void afficherDossierProfesseur(DossierProfesseur *thisdos){
  Professeur *pro=thisdos->getete();
  int x=0;
  Cours *cou;
  Etudiants *etu;
  while(pro!=NULL){
    cout<<pro->nom<<endl;
    cout<<pro->prenom<<endl;
    cou=pro->listecours;
    while(cou!=NULL){
      cout<<cou->sigle<<endl;
      cou=cou->suivant;
    }
    cout<<"&"<<endl;
    etu=pro->listetudiants;
    while(etu!=NULL){
      cout<<etu->nom<<endl;
      etu=etu->apres;
    }
    if(pro->suivant!=NULL)
      cout<<"&"<<endl;
    pro=pro->suivant;
  }
  cout<<endl;
  cout<<"Fin du DossierProfesseur"<<endl;
}

void recopierDossierProfesseur(char* FP, DossierProfesseur *thisdos){
  thisdos->recopier(FP);
  cout<<endl;
  cout<<"DossierProfesseur recopie dans "<<FP<<endl;
}

void lireInstructions(char *FT, DossierProfesseur* thisdos){
  string line, FP="FP.txt";
  char op, *nom, *prenom, *chaFP=new char[FP.size()+1];
  copy(FP.begin(),FP.end(),chaFP);
  chaFP[FP.size()]='\0';
  ifstream infile(FT);
  int i, ref=0, cate=0;
  while(getline(infile, line)){
    i=0;
    op=line[i];
    ++i;
    if(i==line.size()){//line[i]=='\n'){
      if(op=='#'){
	cout<<"Professeur ayant le plus d'etudiants :"<<endl;
	cout<<thisdos->afficherleprofplusetudiant()<<endl;
      }else if(op=='*'){
	cout<<"Cours le plus demande :"<<endl;
	cout<<thisdos->affichercoursplusdemande()<<endl;
      }else if(op=='$'){
	cout<<"Recopie le DossierProfesseur dans "<<chaFP<<endl;
	thisdos->recopier(chaFP);
      }
    }
    //cas d'une instruction avec parametre ou suppression avec deux parametre
    else if(i<line.size()){
      i=i+1;
      ref=i;
      while(i!=line.size() && line[i]!=','){
	++i;
      }
      nom=new char[i-ref+1];
      for(int x=0;x<i-ref;++x){
	nom[x]=line[ref+x];
      }
      nom[i-ref]='\0';
      //cas d'une instruction avec parametre
      if(i==line.size()){
	if(op=='%'){
	  cout<<"Affiche le nombre de prof pour le cours : "<<nom<<endl;
	  cout<<thisdos->affichernbreprofpouruncours(nom)<<endl;
	}
      }
      //cas d'une instruction de suppression avec deux parametres
      if(line[i]==',' && op=='-'){
	i=i+2;
	ref=i;
	while(i!=line.size()){
	  ++i;
	}
	prenom=new char[i-ref+1];
	for(int y=0; y<i-ref; ++y){
	  prenom[y]=line[ref+y];
	}
	prenom[i-ref]='\0';
	thisdos->supprimer(nom,prenom);
	cout<<"Le professeur "<<nom<<" "<<prenom<<" a ete supprime du DossierProfesseur (s'il etait present)"<<endl;
      }
    }
    cout<<endl;
    line="";
  }
  infile.close();
}

int main(int argc, char **argv){
  string FP="FP.txt", FT="FT.txt";
  char *chaFP=new char[FP.size()+1], *chaFT=new char[FT.size()+1];
  copy(FP.begin(),FP.end(),chaFP); copy(FT.begin(), FT.end(), chaFT);
  chaFP[FP.size()]='\0'; chaFT[FT.size()]='\0';
  DossierProfesseur *thisdos=new DossierProfesseur(chaFP);
  lireInstructions(chaFT, thisdos);
  return 0;
}
