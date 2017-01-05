
#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

void usage(){
  printf("./example -r <row> -c <column> -o <bool>\n");
  exit(0);
}
int main(int argc, char * argv[]){
  int c;
  char col;
  int row;
  bool on = false;
  
  while((c=getopt(argc,argv,"r:c:o:"))!=-1){
    printf("%c\n", c);
    switch(c){
    case 'r':
      row = atoi(optarg);
      break;
    case 'c':
      col = optarg[0];
      break;
    case 'o':
      if(strcmp(optarg, "true")==0)
	on = true;
      else if(strcmp(optarg, "false")==0)
	on = false;
      break;
    case '?':
      usage();
      break;
    default:
      usage();
      break;
    }
  }
  led_init();
  led_turn_on_off(row, col, on);
  return 0;
}
