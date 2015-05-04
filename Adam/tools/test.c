#include "fann.h"
#include <unistd.h>
#include <string.h>
#include <math.h>

void main(int argc, char **argv){

  int c, n = 5000, f = 0, a = 1, b = 0, size = 8, start = 0, end = 0, r = 0;
  char fileName[128], *token, delims[3] = "-:,";

  while( (c = getopt(argc, argv, "f:a:s:r:bh")) != -1){
    switch(c){
    case 'f':
      f = 1;
      strcpy(fileName, optarg);
      break;
    case 'a':
      a = atoi(optarg);
      break;
    case 's':
      size = atoi(optarg);
      break;
    case 'r':
      r = 1;
      token = strtok(optarg, delims);
      start = atoi(token);
      token = strtok(NULL, delims);
      end = atoi(token);
      break;
    case 'b':
      b = -1;
      break;
    case 'h':
      printf("Command Line options are -f for the NN file name and -h for help (i.e. this), -a for the output activation function (1 for THRESHOLD (0, 1), 2 for THRESHOLD_SYMMETRIC (-1, 1)... default is 1)\n");
      printf("For example, ./test -f shiftRightws8_1-2/nets/shiftRightws8_5.net -a 2\n");
      return;
    }
  }
  if( !f ){ printf("No function was specified. Should be run as: ./test -f shiftRightws8_1-2/nets/shiftRightws8_5.net for example\n"); return; }

  struct fann *ann = fann_create_from_file(fileName);

  fann_set_activation_function_output(ann, a);

  fann_type *calc_outs;
  fann_type inputs[8];

  if ( !r ) end = pow(2, size);
  int i, j;
  for(i = start; i < end; i++){
    for(j = 0; j < size; j++){
      inputs[j] = ((i >> j) & 1) == 1 ? 1 : b;
      printf("%d ", (int)inputs[j]);
    } 
    printf("\n");
    calc_outs = fann_run(ann, inputs);
    for(j = 0; j < size; j++){ 
      printf("%d ", (int)calc_outs[j]);
      }
    printf("\n");
  }
  
  fann_destroy(ann);

}

