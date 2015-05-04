#include <stdio.h>
#include <unistd.h>
#include <math.h>

int num(char *c);

void main(int argc, char **argv){

  char line[128], *tmp;
  int counter = 1, c;
  while( scanf("%s", line) > 0){
    c = num(line);
    write(1, &c, 2);
  }

}

int num(char *c){
  int n = 0, i = 0;

  for(i = 0; c[i] != 0; i++){
    if( c[i] == '1') n += pow(2, i);
    else i++;
    /*
    if( c[i] == '-' && c[++i] == '1');
    else n += pow(2, i)*1; //((int)c[i] - 48);;
    */

  }

  return n;
}
