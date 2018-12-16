
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "cle.h"
#include "arbre_binaire.h"
//#include "tas_arbre.h"



int main(){

	int tailleFichier = 50000;
	FILE* fp = fopen("/home/moumouh/git/ALGAV/cles_alea/jeu_5_nb_cles_50000.txt", "r");
	if(!fp) return 0;
	cle * keys[tailleFichier];

	char temp[36] = {0};

	fgets(temp, 35, fp);
	cle * c = parse_cle(temp);
	int i = 1;
	keys[0] = c;
	while(fgets (temp, 35, fp) !=NULL ) {
	  cle * k = parse_cle(temp);
	   keys[i] = k;
	   if(eg(keys[i-1],k) == 0){
		  i++;
	   }

	}
	fclose(fp);



	ABR * a = ArbreVide();
	ABR * d = ArbreVide();
	time_t begin,end;

	for(int i = 0; i<tailleFichier; i++){
		d = ABR_Ajout(keys[i],d);
		d = Equilibrage(d);
	}
	struct timeval stop, start;
	gettimeofday(&start, NULL);

	ABR * res = Recherche(keys[0], d);
	toStringABR(res);

	gettimeofday(&stop, NULL);

	printf("temps d'execution %lu\n",stop.tv_usec - start.tv_usec);
	//
	//


	//printf("hauteur %d \n",Hauteur(d));
	//free(c);
	//free(b);
	//free(a);
	return 0;
}
