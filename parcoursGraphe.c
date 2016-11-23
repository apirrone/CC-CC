#include <stdio.h>
#include <stdlib.h>
#include "all.h"

int main(int argc, char* argv[]){
  int i, j;
  for(i = 0 ; i < orderG() ; i++){
    for(j = 0 ; j < orderG() ; j++){
      if(are_adjacent(i, j))
	printf("%d, %d :  oui\n", i, j);
      else
	printf("%d, %d :  non\n", i, j);
    }
  } 
}
