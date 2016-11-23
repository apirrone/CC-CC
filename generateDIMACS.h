#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "all.h"

bool isDone(int i, int j);
void type1Printf(int nbVertices, int nbCol);
void type2Printf(int nbVertices, int nbCol);
void annexeType3Printf(int i, int nbCol);
void type3Printf(int nbVertices, int nbCol);
void type1(int nbVertices, int nbCol);
void type2(int nbVertices, int nbCol);
void annexeType3(int i, int nbCol);
void type3(int nbVertices, int nbCol);
void clausesPrintf(int nbCol, int nbVertices, char* graphName);
void generateDIMACS(int nbCol, int nbVertices, char* graphName);
char* getGraphName(char* raw);
int main(int argc, char* argv[]);





