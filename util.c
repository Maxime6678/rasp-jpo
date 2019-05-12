#include "header/util.h"

double dot(int* vec1, int* vec2){
  // On assume que taille de vec1 est égale a vec2
  double r = 0.0;
  int i;
  for (i = 0; i < 2; i++) {
    r+= vec1[i]*vec2[i];
  }
  return r;
}
