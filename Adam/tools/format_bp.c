#include <stdio.h>
#include <unistd.h>

void main(int argc, char **argv){

  int header = 0, size = 8, c;
  while( (c = getopt(argc, argv, "hs:")) != -1){
    switch(c){
    case 'h':
      header = 1;
      break;
    case 's':
      size = atoi(optarg);
      break;
    }
  }
  size *= 2;

//read these three in simply to skip them
if(header){
  if( scanf("%d %d %d", &c, &c, &c) < 0 ){
    printf("Problem reading header (are you sure you meant to specify -h?), exiting\n");
    return;
  }
 }

 
  char line[128], *tmp;
  int counter = 1;
  while( scanf("%s", line) > 0){
    for(tmp = line; *tmp != 0 && *tmp != 10; tmp++){
      if(*tmp == '-' && *(++tmp) == '1') printf("0");
      else if(*tmp == '1') printf("1");
    }
    if( counter++ % size == 0) printf("\n");
  }

}
