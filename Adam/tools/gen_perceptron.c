#include "fann.h"
#include <stdio.h>
//somewhere with fann installed, compile with
//gcc gen_perceptron.c -Wall -lfann -o percep

int main(int argc, char* argv[])
{
  struct fann *ann = fann_create_standard(2,2,1);
  fann_set_activation_function_output(ann, FANN_THRESHOLD);
  int out[4], i, j, count = 0, fn_counter[16];

  for(i=0;i<16;i++)
    fn_counter[i] = 0;
  //Switch binary or bipolar representation
  //  fann_type arr[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} };
  fann_type arr[4][2] = { {-1,-1}, {-1,1}, {1,-1}, {1,1} };

  for(i=0;i<1000000;i++)
    {
      fann_randomize_weights(ann, -1, 1);

      for(j=0;j<4;j++)
	out[j] = *fann_run(ann, arr[j]);

      count ++;
      int fn_number = 0;
      for(j=0;j<4;j++)
	if(out[j]==1)
	  fn_number+= powf(2,j);
      fn_counter[fn_number]++;
    }
  
  for(i=0;i<16;i++)
    printf("chance f%d: %f \n",i, fn_counter[i] / (float) count );
  
  
  fann_destroy(ann);
  return 0;
}
