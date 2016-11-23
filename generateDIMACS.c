/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <stdbool.h> */
/* #include "all.h" */
#include "generateDIMACS.h"

bool** done;
int nbClauses;

FILE *f;

int** hashColorToVariable;

bool isDone(int i, int j){
  return done[i][j];
}


//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

//Partie pour afficher les clauses dans la sortie standard
void type1Printf(int nbVertices, int nbCol){
  int i, j, k;
  printf("Type1 : \n");
  for(i = 0 ; i < nbVertices ; i++){
    for(j = 0 ; j < nbVertices ; j++){
      if(are_adjacent(i, j) && !(isDone(i, j) || isDone(j, i))){
	done[i][j] = true;
	done[j][i] = true;
	for(k = 0 ; k < nbCol ; k++){
	  printf("-%d%d V -%d%d \n", i, k, j, k);
	  nbClauses++;
	} 
      }
    }
  }

}

void type2Printf(int nbVertices, int nbCol){
  int i, j;
  printf("Type2 : \n"); 
  for(i = 0 ; i < nbVertices ; i++)
    for(j = 0 ; j < nbCol ; j++){
      if(j!=(nbCol-1))
	  printf("%d%d V ", i, j);
	else{
	  printf("%d%d\n\n", i, j);
	  nbClauses++;
	}
      }  
  }

  void annexeType3Printf(int i, int nbCol){
    int j, k;
    bool donee[nbCol][nbCol];
    for(j = 0 ; j < nbCol ; j++)
      for(k = 0 ; k < nbCol ; k++)
	donee[j][k] = false;

    for(k = 0 ; k < nbCol ; k++){
      for(j = 0 ; j < nbCol ; j++){
	if(!(donee[k][j] || donee[j][k]) && j != k){
	  donee[k][j] = true;
	  donee[j][k] = true;

	  printf("-%d%d V -%d%d\n", i, j, i, k);
	  nbClauses++;
	} 
      }
    }

  }

  void type3Printf(int nbVertices, int nbCol){
    int i;
  
    printf("Type3 : \n");
    for(i = 0 ; i < nbVertices ; i++){
      annexeType3Printf(i, nbCol); 
    }

    
  }




















  //------------------------------------------------------------------------------------//
  //------------------------------------------------------------------------------------//















  //Partie pour sortir du DIMACS
  void type1(int nbVertices, int nbCol){
    int i, j, k;
    for(i = 0 ; i < nbVertices ; i++){
      for(j = 0 ; j < nbVertices ; j++){
	if(are_adjacent(i, j) && !(isDone(i, j) || isDone(j, i))){
	  done[i][j] = true;
	  done[j][i] = true;
	  for(k = 0 ; k < nbCol ; k++){
	    fprintf(f, "-%d -%d 0\n", hashColorToVariable[i][k], hashColorToVariable[j][k]);
	  } 
	}
      }
    }
  }

void type2(int nbVertices, int nbCol){
  int i, j;
  for(i = 0 ; i < nbVertices ; i++)
    for(j = 0 ; j < nbCol ; j++){
      if(j!=(nbCol-1)){
	  fprintf(f, "%d ", hashColorToVariable[i][j]);
	}
	else{
	  fprintf(f, "%d 0\n", hashColorToVariable[i][j]);
	}
      }  
  }

void annexeType3(int i, int nbCol){
  int j, k;
  bool donee[nbCol][nbCol];
  for(j = 0 ; j < nbCol ; j++)
    for(k = 0 ; k < nbCol ; k++)
      donee[j][k] = false;  

    for(k = 0 ; k < nbCol ; k++){
      for(j = 0 ; j < nbCol ; j++){
	if(!(donee[k][j] || donee[j][k]) && j != k){
	  donee[k][j] = true;
	  donee[j][k] = true;

	  fprintf(f, "-%d -%d 0\n", hashColorToVariable[i][j], hashColorToVariable[i][k]); 
	} 
      }
    }

  }

void type3(int nbVertices, int nbCol){
  int i;
  
  for(i = 0 ; i < nbVertices ; i++){
    annexeType3(i, nbCol); 
  }

    
}

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

void clausesPrintf(int nbCol, int nbVertices, char* graphName){
  int i;
  done = (bool**)malloc(nbVertices*sizeof(bool*));
  for(i = 0 ; i < nbVertices ; i++)
    done[i] = malloc(nbVertices*sizeof(bool));

  int nbType1Clauses = sizeG()*nbCol;
  printf("predicted 1 : %d\n", nbType1Clauses);
  int nbType2Clauses = nbVertices;
  printf("predicted 2 : %d\n", nbType2Clauses);

  int nbType3Clauses = 0;
  for(i = 1 ; i < nbCol ; i++)
    nbType3Clauses += (nbCol - i);

  nbType3Clauses = nbType3Clauses*nbVertices;
  //  nbType3Clauses = nbVertices*nbCol;
  printf("predicted 3 : %d\n", nbType3Clauses);
  int predicted = nbType1Clauses+nbType2Clauses+nbType3Clauses;
  
  printf("c\n");
  printf("c Graph : %s\n", graphName);
  printf("c k = %d\n", nbCol);
  printf("c\n");
  printf("p cnf %d %d\n", nbCol*nbVertices, 202020);

  

  type1Printf(nbVertices, nbCol);
  printf("nbClauses type1 : %d\n",nbClauses);
  int tmp = nbClauses;

  type2Printf(nbVertices, nbCol);
  printf("nbClauses type2 : %d\n",nbClauses-tmp);
  tmp = nbClauses;

  type3Printf(nbVertices, nbCol);
  printf("nbClauses type3 : %d\n",nbClauses-tmp);
  tmp = nbClauses;


  printf("\nPREDICTED nbClauses : %d\n", predicted);
  printf("\nACTUAL nbClauses : %d\n", nbClauses);

  
  for(i = 0 ; i < nbVertices ; i++)
    free(done[i]);
  free(done);
  
   
}


void generateDIMACS(int nbCol, int nbVertices, char* graphName){
  
  int i, j;
  done = (bool**)malloc(nbVertices*sizeof(bool*));
  for(i = 0 ; i < nbVertices ; i++)
    done[i] = malloc(nbVertices*sizeof(bool));

  hashColorToVariable = (int**)malloc(nbVertices*sizeof(int*));
  for(i = 0 ; i < nbVertices ; i++)
    hashColorToVariable[i] = malloc(nbCol*sizeof(int));
  
  int k = 1;
  for(i = 0 ; i < nbVertices ; i++)
    for(j = 0 ; j < nbCol ; j++){
      hashColorToVariable[i][j] = k;
      k++;
    }

    
  int nbType1Clauses = sizeG()*nbCol;
  int nbType2Clauses = nbVertices;

  int nbType3Clauses = 0;
  for(i = 1 ; i < nbCol ; i++)
    nbType3Clauses += (nbCol - i);

  nbType3Clauses = nbType3Clauses*nbVertices;
  int predicted = nbType1Clauses+nbType2Clauses+nbType3Clauses;
  
  fprintf(f, "c\n");
  fprintf(f, "c Graph : %s\n", graphName);
  fprintf(f, "c k = %d\n", nbCol);
  fprintf(f, "c\n");
  fprintf(f, "p cnf %d %d\n", nbCol*nbVertices, predicted);
  type1(nbVertices, nbCol);

  type2(nbVertices, nbCol);

  type3(nbVertices, nbCol);

  for(i = 0 ; i < nbVertices ; i++)
    free(done[i]);
  
  free(done);
  	
	
}

//Get graph name without "./"
char* getGraphName(char* raw){
  char a;
  int j;
  int i = 0;

  do{
    a = raw[i];
    i++;
  }while(a != '\0');

  char* res = malloc((i-2)*sizeof(char)); 
  
  for(j = 2 ; j < i ; j++)
    res[j-2] = raw[j];
  return res;
}



int main(int argc, char* argv[]){
  if(argc != 3){
    printf("Usage : ./%s <nb-colors> <filename>\n", getGraphName(argv[0]));
    return 0;
  }

  int nbCol = atoi(argv[1]);

  if(nbCol > orderG()){
    printf("ERROR : Number of colors can't be greater than the number of edges in the graph\n");
    return 0;
  }

    
    
  f = fopen(argv[2], "w");
  if (f == NULL) {
    printf("Error opening file!\n");
    return 0;
  }

    
    
  nbClauses = 0;

  //Verbose display
  //clausesPrintf(nbCol, orderG(), getGraphName(argv[0]));

  nbClauses = 0;
  generateDIMACS(nbCol, orderG(), getGraphName(argv[0]));

  fclose(f);
    
  return 0;
}







