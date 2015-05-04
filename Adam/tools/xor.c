#include <stdio.h>
#include <unistd.h>
#include <math.h>

void main(int argc, char **argv){

  int c;
  char *fA, *fB;
  while( (c = getopt(argc, argv, "a:b:")) != -1){
    switch(c){
    case 'a':
      fA = optarg;
      break;
    case 'b':
      fB = optarg;
      break;
    }
  }

  FILE *A = fopen(fA, "r");
  if(A == NULL){ fprintf(stderr, "Could not open %s\n", fA); return;}
  FILE *B = fopen(fB, "r");
  if(B == NULL){ fprintf(stderr, "Could not open %s\n", fB); return;}

  
  char lineA[128], lineB[128];
  int counter = 1, i;
  while( fscanf(A, "%s", lineA) > 0 && fscanf(B, "%s", lineB) > 0){
    //printf("%d" num(lineA)^num(lineB));
    for(i = 0; lineA[i] != 0 && lineB[i] != 0; i++){ 
      printf("%d", ((int)lineA[i] - 48)^((int)lineB[i] - 48));
    }
    printf("\n");
  }

  fclose(A);
  fclose(B);

}
