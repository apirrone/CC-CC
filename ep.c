int orderG(){
  return 4;}

int sizeG(){
  return 4;}

int are_adjacent(int u, int v){
  if(((u == 0 && v == 1) || (v == 0 && u == 1)) ||
     ((u == 0 && v == 2) || (v == 0 && u == 2)) ||
     ((u == 0 && v == 3) || (v == 0 && u == 3)) ||
     ((u == 2 && v == 3) || (v == 2 && u == 3)))
    return 1;
  else
    return 0;
  
}
