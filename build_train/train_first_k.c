#include "fann.h"
#include <stdio.h>
float fann_train_epoch_irpropm(struct fann *ann, struct fann_train_data *data);

int main(int argc, char* argv[]) {
  //Create net with input and output layers
  struct fann *ann = fann_create_standard(2,8,8);
  //Build data set
  struct fann_train_data *data = fann_read_train_from_file(argv[1]);
  
  struct fann_train_data *subset_first_64 = fann_subset_train_data(data, 0, atoi(argv[3]));
  if (atoi(argv[2])){
    printf("shuffle \n");
    fann_shuffle_train(subset_first_64);
  }
  while(1){
    fann_train_epoch_irpropm(ann, subset_first_64);
    fann_test_data(ann, subset_first_64);
    if (fann_get_bit_fail(ann) == 0)
      break;
  }
  fann_test_data(ann, data);
  printf("%u is bit fail\n", fann_get_bit_fail(ann));

  fann_destroy(ann);
  fann_destroy_train(data);
return 0;
}
