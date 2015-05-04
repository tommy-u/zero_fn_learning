#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#define ESC 27

void main(int argc, char **argv){
  
  char *fA, *fB;
  int c, size = 8;
  while( ( c = getopt(argc, argv, "a:b:s:")) != -1){
    switch(c){
    case 'a':
      fA = optarg;
      break;
    case 'b':
      fB = optarg;
      break;
    case 's':
      size = atoi(optarg);
      break;
    }
  }
  size *= 2;

  FILE *A = fopen(fA, "r");
  if(A == NULL) { fprintf(stderr, "Could not open %s\n", fA); return;}

  FILE *B = fopen(fB, "r");
  if(B == NULL) { fprintf(stderr, "Could not open %s\n", fB); return;}

  
  char lineA[128], lineB[128];
  int wrongLines = 0, rightLines = 0, hw = 0;
  int *xs = (int *)calloc(size, sizeof(int));
  while( fscanf(A, "%s", lineA) > 0 && fscanf(B, "%s", lineB) > 0){
    if( strcmp(lineA, lineB) == 0 ){
      rightLines++;
      printf(KGRN "A: %s \nB: %s \n" RESET, lineA, lineB);
    }
    else{
      wrongLines++; 
      //printf(KRED "A: %s \nB: %s \n" RESET, lineA, lineB);
      printf(KRED "A: %s \nB: ", lineA);
      for(c = 0; lineA[c] != 0 && lineB[c] != 0; c++){
	if(lineA[c] != lineB[c]) { printf("%c[1m",ESC); hw++; xs[c]++; } // BOLD if wrong
	printf(KRED "%c", lineB[c]);
	printf("%c[0m",ESC);

      }
      printf("\n" RESET);
    }
    printf("\n");
  }    

  printf("Output Bit Failures:\n");
  for(c = size/2; c < size; c++){
    printf("%d: %d\n", c - size/2, xs[c]);
  }
  printf("\nRight: %d Wrong: %d Hamming Weight: %d\n", rightLines, wrongLines, hw);
}
