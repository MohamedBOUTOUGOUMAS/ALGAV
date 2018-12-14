//============================================================================
// Name        : File_Binomiales.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include "cle.h"

#include "tournoi.h"
using namespace std;


int main(){

	FILE* fp = fopen("/users/Etu9/3703039/c++_workspace/File_Binomiales/src/cles_alea/jeu_1_nb_cles_100.txt", "r");
	if(!fp) return 0;
	cle * keys[100];

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

	tournoi * xp = mk_tournoi(keys[0],2);
	//tournoi * mac = mk_tournoi(keys[2],2);

	//tournoi * t = mk_tournoi(keys[0],3);

	//t = addChildTournoi(t,xp);
	//t = addChildTournoi(t,mac);
	//toStringTournoi(n);
	//toStringTournoi(t);
	//t = addChildTournoi(t,mac);

	//t->children.push_back();
	//toStringTournoi(t);
	file * f = mk_from_tournoi(*xp);
	f = ajout(keys[1], f);
	//toStringFile(f);
	 //ajout(keys[3],f);
//	f->push_back(*mac);
//	f->push_back(*bref);

	//print(keys[0]);
	//free(mac);
	free(xp);
	//free(t);
	return 0;
}
