#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//passer une valeur en parametre a l'execution

void sablier(int base){
  int line=base, esp=0;
  while(line>1){
    esp=0;
    while(esp<(base-line)/2){
      printf(" ");
      ++esp;
    }
    esp=0;
    while(esp<line){
      printf("*");
      ++esp;
    }
    printf("\n");
    line=line-2;
  }
  esp=0;
  if(base%2==0){
    while(esp<(base-line)/2){
      printf(" ");
      ++esp;
    }
    printf("*");
  }
  while(line<=base){
    esp=0;
    while(esp<(base-line)/2){
      printf(" ");
      ++esp;
    }
    esp=0;
    while(esp<line){
      printf("*");
      ++esp;
    }
    printf("\n");
    line=line+2;
  }
}

int main(int argc, char **argv){
  if(argc==2)
    sablier(atoi(argv[1]));
  return 0;
}
