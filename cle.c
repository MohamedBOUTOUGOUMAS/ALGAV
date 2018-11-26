#include <stdlib.h>
#include <stdio.h>

typedef unsigned char cle;

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
  for(int i = 0; i < 16; i ++) {
    if(a[i] != b[i]) {
      return 0;
    }
  }
  return 1;
}

int inf(cle* a, cle* b) {
  int i = 0;
  while(a[i] == b[i] && i < 16) {
    i++;
  }
  if(i == 16) {return 0;}
  return a[i] <= b[i];
}

int test() {
  FILE* fp = fopen("/Users/polybulle/Downloads/cles_alea/jeu_1_nb_cles_100.txt", "r");
  if(!fp) return 1;
  char temp[36] = {0};

  fgets(temp, 35, fp);

  cle* c = parse_cle(temp);
  
  fclose(fp);

  for(int i = 0; i < 16; i++) {
    printf("%x", c[i]);
  }
  
  return 0;
}
