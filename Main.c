
#include <stdlib.h>
#include <stdio.h>
#include "cle.h"
#include "arbre_binaire.h"
#include "tas_arbre.h"



int main(){


	FILE* fp = fopen("/users/Etu9/3703039/git/ALGAV/cles_alea/jeu_1_nb_cles_100.txt", "r");
	if(!fp) return 0;
	cle * keys[100];

	char temp[36] = {0};

	fgets(temp, 35, fp);
	cle * c = parse_cle(temp);
	int i = 1;
	keys[0] = c;
	while(fgets (temp, 35, fp) !=NULL ) {
	  cle * k = parse_cle(temp);
	   //printf("%d \n",i);
	   keys[i] = k;
	   if(eg(keys[i-1],k) == 0){
		  i++;
	   }

	}
	fclose(fp);

	//for(int i =0;i<100;i++){
		//print(keys[1]);
	//}

	ABR * a = ArbreVide();
	a = ArbreBinaire(keys[0], &a->gauche, &a->droite, &a->pere);
	ABR * b = ArbreBinaire(a->key, &a->gauche, &a->droite, &a->pere);
	//print(a->key);
	//
	//ABR * b = ArbreVide();
	//b = SousArbreGauche(a);
	b = ABR_Ajout(keys[1],b);
	b = ABR_Ajout(keys[2],b);
	b = ABR_Ajout(keys[3],b);
	toStringABR(b->gauche->gauche);
//	for(int i =0;i<100;i++){
//		printf("%d \n",eg(keys[i],keys[i+1]));
//	}

	//printf(" hauteur %d \n",Hauteur(b));
	//free(c);
	//free(b);
	//free(a);
	return 0;
}
