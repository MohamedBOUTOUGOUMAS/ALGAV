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
	FILE* fp = fopen("/home/moumouh/workspace_c++/FilesBinomiales/src/cles_alea/jeu_1_nb_cles_100.txt", "r");
	//FILE* fp = fopen("/users/Etu9/3703039/c++_workspace/File_Binomiales/src/cles_alea/jeu_1_nb_cles_100.txt", "r");
	if(!fp) return 0;

	cle * keys[4];

	char temp[36] = {0};

	fgets(temp, 35, fp);
	cle * c = parse_cle(temp);
	int i = 1;
	keys[0] = c;
	while(fgets (temp, 35, fp) !=NULL && i<5 ) {
	  cle * k = parse_cle(temp);
	   keys[i] = k;
	   if(eg(keys[i-1],k) == 0){
		  i++;
	   }

	}
	fclose(fp);

	tournoi xp = mk_tournoi(keys[0],1);
	//tournoi mac = mk_tournoi(keys[1],1);
	//tournoi t = mk_tournoi(keys[2],1);
	//tournoi u = uniont(xp,mac);
	//toStringTournoi(u);
	//tournoi v = uniont(u,t);
	//t = addChildTournoi(t,xp);
	//t = addChildTournoi(t,mac);
	//toStringTournoi(v);
	//toStringTournoi(t);
	//t = addChildTournoi(t,mac);

	//t->children.push_back();
	//toStringTournoi(t);
	//file f = mk_from_tournoi(xp);
	//vector<cle *> vec;
	//vec.reserve(4);
	/*for(int i = 0; i<4 ; i++){
		vec.push_back(keys[i]);
	}

	f = consinter(vec);*/
	/*f = ajout(keys[1], f);
	f = ajout(keys[2], f);
	f = ajout(keys[3], f);*/
	//file x = reste(*f);
	//toStringFile(f);
	 //ajout(keys[3],f);
//	f->push_back(*mac);
//	f->push_back(*bref);

	file f = mk_file();
	f = ajout(keys[0],f);
	//toStringFile(*f);
	//std::cout<<f.size()<<endl;
	//free(t);
	//delete[]&vec;
	//delete[]keys;
	//delete[]&mac;

	delete[]&f;
	delete[]&xp;
	return 0;
}
