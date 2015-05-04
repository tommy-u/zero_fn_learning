#include "fann.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void main(int argc, char **argv)
{
    
  int c, H = 8, n = 5000, f = 0, a = 3, size = 8, net_specified = 0, r = 0, start = 0, length = 256, random = 0;
  char fileName[128], func[128], netName[128], *tokens/*=calloc(4, sizeof(char))*/, *delims, *saveptr;

  while( (c = getopt(argc, argv, "N:n:f:a:s:H:r:Rh") ) != -1){
    switch(c){
    case 'N':
      net_specified = 1;
      strcpy(netName, optarg);
      break;
    case 'n': 
      n = atoi(optarg);
      break;
    case 'f':
      f = 1;
      strcpy(func, optarg);
      break;
    case 'a':
      a = atoi(optarg);
      break;
    case 's':
      size = atoi(optarg);
      break;
    case 'H':
      H = atoi(optarg);
      break;
    case 'r':
      r = 1;
      tokens = strtok_r(optarg, "," , &saveptr);
      start = tokens != NULL ? atoi(tokens) : 0;
      tokens = strtok_r(NULL, ",", &saveptr);
      length = tokens != NULL? atoi(tokens) - start + 1 : 256;
      break;
    case 'R':
      random = 1;
      break;
    case 'h':
      printf("Command Line options are:\n-n for number of max epochs\n-f for the function name (without .txt extension)\n-a for the activation function number (3 (default) for SIGMOID, 5 for SIGMOID_SYMMETRIC)\n-h for help (i.e. this message)\n");
      printf("For example, ./train -n 5 -f shiftRightws8 \n");
      return;
    }
  }
  if( !f ) { printf("No training file specified. Run as: ./test -n 5 -f shiftRightws8 for example.\n"); return; }



  const float bit_fail_limit = .49;
  const float desired_error = (const float) 0.00000000001;
  const uint max_epochs = n;
  const uint epochs_between_reports = 2;

  struct fann *ann;
  if(net_specified) {
    ann = fann_create_from_file(netName);
  }
  else{
    const uint num_layers = 3 - 1*(H == 0);
    uint layers[num_layers];
    if( H ){
      layers[0] = size;
      layers[1] = H;
      layers[2] = size;
    }else{
      layers[0] = size;
      layers[1] = size;
    }

    ann = fann_create_standard_array(num_layers, layers);
    fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);

    fann_set_activation_function_hidden(ann, a);
    fann_set_activation_function_output(ann, a);

    fann_set_bit_fail_limit(ann, bit_fail_limit);
    //fann_set_train_stop_function(ann, FANN_STOPFUNC_BIT);
  }

  strcpy(fileName, func);
  strcat(fileName, ".txt");
  
  //fann_train_on_file(ann, fileName, max_epochs, epochs_between_reports, desired_error);
  
  struct fann_train_data *full_data = fann_read_train_from_file(fileName);
  if( random ) fann_shuffle_train_data(full_data);
  if( !r ) length = fann_length_train_data(full_data);
  struct fann_train_data *data = fann_subset_train_data(full_data, start, length);

  int i, bit_fail;
  float error;
  for(i = 1 ; i <= max_epochs ; i++) {
    fann_train_epoch(ann, data);
    fann_test_data(ann,data); //to get the accurate values of bit fail and MSE

    error = fann_get_MSE(ann);
    bit_fail = fann_get_bit_fail(ann);

    if( i % epochs_between_reports == 1) printf("Epochs: %d\tMSE: %f\tBit Fail: %d\n", i, error, bit_fail);

    if ( error < desired_error ) break;

  }
  fann_destroy_train(data);

  printf("%d ", i - 1);

  char num[32], oFileName[128];
  sprintf(num, "%d", n);
  strcpy(oFileName, func);
  strcat(oFileName, "_");
  strcat(oFileName, num);
  strcat(oFileName, ".net");


  //fann_print_connections(ann);

  fann_save(ann, oFileName);
  fann_destroy(ann);
}
