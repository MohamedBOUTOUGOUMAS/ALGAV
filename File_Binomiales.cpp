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
	int tailleFichier = 5000;
	string path = ("/home/moumouh/workspace_c++/FilesBinomiales/src/cles_alea/jeu_1_nb_cles_");
	string extension = to_string(tailleFichier) + ".txt";
	path = path + extension;
	//printf("%s",path.c_str());
	FILE* fp = fopen(path.c_str(), "r");
	//FILE* fp = fopen("/users/Etu9/3703039/c++_workspace/File_Binomiales/src/cles_alea/jeu_1_nb_cles_100.txt", "r");
	if(!fp){
		printf("merde");
		return 0;
	}



	cle * keys[tailleFichier];

	char temp[36] = {0};

	fgets(temp, 35, fp);
	cle * c = parse_cle(temp);
	int i = 1;
	keys[0] = c;
	while(fgets (temp, 35, fp) !=NULL) {
	  cle * k = parse_cle(temp);
	   keys[i] = k;
	   if(eg(keys[i-1],k) == 0){
		  i++;
	   }
	}
	fclose(fp);

	tournoi xp = mk_tournoi(keys[0]);
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
	file f = mk_from_tournoi(xp);
	//toStringFile(f);
	vector<cle *> vec;
	vec.reserve(tailleFichier);
	for(int i = 0; i< tailleFichier; i++){
		vec.push_back(keys[i]);
	}

	f = consinter(vec);
	toStringFile(f);
	//f.~vector();

	/*f = ajout(keys[1], f);
	f = ajout(keys[2], f);
	f = ajout(keys[3], f);*/
	//file x = reste(*f);
	//toStringFile(f);
	 //ajout(keys[3],f);
//	f->push_back(*mac);
//	f->push_back(*bref);

	/*file d = mk_file();
	d.reserve(1);

	file f = mk_file();
	f.reserve(1);
	f.push_back(mac);
	d = ajout(keys[0],f);*/
	//f = d;
	//f = ajout(keys[0],f);

	//std::cout<<f.size()<<endl;
	//free(t);
	//delete[]&vec;*/
	return 0;
}
