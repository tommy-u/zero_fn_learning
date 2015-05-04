#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "gentbl.h"

typedef wtype Row[2];

void ascii_byte(wtype b)
{
  int i;
  for(i = 0; i < WORD_SIZE; i++) printf("%d ", ((b >> i) & 1) == 1 ? 1 : -1);
  /*
  printf("%d ", ((b>>0) & 1) == 1 ? 1 : -1);
  printf("%d ", ((b>>1) & 1) == 1 ? 1 : -1);
  printf("%d ", ((b>>2) & 1) == 1 ? 1 : -1);
  printf("%d ", ((b>>3) & 1) == 1 ? 1 : -1);
  printf("%d ", ((b>>4) & 1) == 1 ? 1 : -1);
  printf("%d ", ((b>>5) & 1) == 1 ? 1 : -1);
  printf("%d ", ((b>>6) & 1) == 1 ? 1 : -1);
  printf("%d ", ((b>>7) & 1) == 1 ? 1 : -1);*/
}

fann_out(Row row) 
{
  wtype *bptr = (wtype *)row;
  int i,j;

  for (i=0; i<sizeof(Row)/sizeof(wtype); i++) {
    for (j=0; j<sizeof(wtype); j++) {
      ascii_byte(bptr[i*sizeof(wtype)+j]);
    }
    printf("\n");
  }
}

void 
fann_traininghdr(void)
{
  const int len=sizeof(wtype)*8;
  const size_t num=((wtype)-1)+1;
  printf("%zd %d %d\n", num, len, len);
}

int 
main(int argc, char **argv)
{
  size_t n;
  wtype x=0;
  Row row;

  if (argc>1) fann_traininghdr();

  while (1) {
    row[0]=x;
    row[1]=func(x);
    if (argc == 1) {
      n=write(STDOUT_FILENO, row, sizeof(row));
      assert(n==sizeof(row));
    } else {
      fann_out(row);
    }
    if (x==(wtype)(-1)) break;
    x++;
  }
  return 0;
}
