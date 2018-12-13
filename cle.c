#include <stdlib.h>
#include <stdio.h>
#include "cle.h"


//fonctionne, ne pas toucher
cle* parse_cle(char* s) {
  s += 2;
  cle* res = malloc(16);
  char temp[2] = {0};
  for(int i = 0; i < 16; i++) {
    temp[0] = s[2*i];
    temp[1] = s[2*i + 1];
    sscanf(temp, "%x", res + i);
  }
  return res;
}

int eg(cle* a, cle* b) {
  for(int i = 0; i < 16; i ++) 
    if(a[i] != b[i])
      return 0;
  return 1;
}

int inf(cle* a, cle* b) {
  int i = 0;
  while(a[i] == b[i] && i < 16) {
    i++;
  }
  if(i == 16) 
    return 0;
  return a[i] <= b[i];
}

void print(cle * c){
	printf("cle.c : ");
	for(int i = 0; i < 16; i++) {
		printf("%x", c[i]);
	}
	printf("\n");
}

