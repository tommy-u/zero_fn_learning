#include <stdio.h>
#include <unistd.h>

void main(int argc, char **argv){


  char *fA, *fB;
  int c;
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
  int counter = 0, i;
  while( fscanf(A, "%s", lineA) > 0 && fscanf(B, "%s", lineB) > 0){
    for(i = 0; lineA[i] != 0 && lineA[i] != 10 && lineB[i] != 0 && lineB[i] != 10; i++){
      if((lineA[i] == '0' || lineA[i] == '1') && lineA[i] != lineB[i]) counter++;
    }
  }

  printf("%d\n", counter);

  fclose(A);
  fclose(B);
}
