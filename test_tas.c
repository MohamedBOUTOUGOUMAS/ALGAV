#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "tas_array.h"
#include "tas_arbre.h"

static int tailles[8] = {100, 200, 500, 1000, 5000, 10000, 20000, 50000};

char* file_for(int jeu, int taille) {
  char* res;
  asprintf(&res, "cles_alea/jeu_%d_nb_cles_%d.txt", jeu, taille);
  return res;
}

int main() {
  for(int jeu1_n = 1; jeu1_n <= 5; jeu1_n++)
    for(int taille1 = 0; taille1 < 8; taille1++) {
      //for(int jeu2_n = 1; jeu2_n <= 5; jeu2_n++) {
      
      
          char* nom1 = file_for(jeu1_n, tailles[taille1]);
          size_t jeu1_size = tailles[taille1];
          cle** cles1 = malloc(jeu1_size * sizeof(cle*));
          FILE* jeu1 = fopen(nom1, "r");
      
          char ligne[50];
          size_t i = 0;
          while(fgets(ligne, 50, jeu1)) 
            cles1[i++] = parse_cle(ligne);

          /* char* nom2 = file_for(jeu2_n, tailles[taille1]); */
          /* size_t jeu2_size = tailles[taille1]; */
          /* cle** cles2 = malloc(jeu2_size * sizeof(cle*)); */
          /* FILE* jeu2 = fopen(nom2, "r"); */
      
          /* i = 0; */
          /* while(fgets(ligne, 50, jeu2))  */
          /*   cles2[i++] = parse_cle(ligne); */

          /* /\* tas *t2 = consiter(cles2, jeu2_size); *\/ */
          clock_t begin = clock();
          tas *t1 = consiter(cles1, jeu1_size);
          /* uniontas(t1,t2); */
          clock_t end = clock();
          int elapsed = (int)((double)(end - begin) / CLOCKS_PER_SEC * 1000000);
          printf("%d\t%d\t%d\n", jeu1_n, tailles[taille1], elapsed);
        }
  return 0;
}

