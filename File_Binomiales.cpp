//============================================================================
// Name        : File_Binomiales.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "cle.h"

#include "tournoi.h"
using namespace std;


int main(){

	//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	/*

	int tailleFichier1 = 50000;
	string path1 = ("/home/moumouh/workspace_c++/FilesBinomiales/src/cles_alea/jeu_1_nb_cles_");
	string extension1 = to_string(tailleFichier1) + ".txt";
	path1 = path1 + extension1;
	//printf("%s",path.c_str());
	FILE* fp1 = fopen(path1.c_str(), "r");
	//FILE* fp = fopen("/users/Etu9/3703039/c++_workspace/File_Binomiales/src/cles_alea/jeu_1_nb_cles_100.txt", "r");
	if(!fp1){
		printf("merde");
		return 0;
	}



	cle * keys1[tailleFichier1];

	char temp1[36] = {0};

	fgets(temp1, 35, fp1);
	cle * c1 = parse_cle(temp1);
	int i = 1;
	keys1[0] = c1;
	while(fgets (temp1, 35, fp1) !=NULL) {
	  cle * k = parse_cle(temp1);
	   keys1[i] = k;
	   if(eg(keys1[i-1],k) == 0){
		  i++;
	   }
	}
	fclose(fp1);

*/
	/**
	 *
	 *
	 *
	 *
	 *
	 * **/
	/*
	int tailleFichier2 = 20000;
		string path = ("/home/moumouh/workspace_c++/FilesBinomiales/src/cles_alea/jeu_3_nb_cles_");
		string extension = to_string(tailleFichier2) + ".txt";
		path = path + extension;
		//printf("%s",path.c_str());
		FILE* fp = fopen(path.c_str(), "r");
		//FILE* fp = fopen("/users/Etu9/3703039/c++_workspace/File_Binomiales/src/cles_alea/jeu_1_nb_cles_100.txt", "r");
		if(!fp){
			printf("merde");
			return 0;
		}



		cle * keys2[tailleFichier2];

		char temp[36] = {0};

		fgets(temp, 35, fp);
		cle * c = parse_cle(temp);
		int j = 1;
		keys2[0] = c;
		while(fgets (temp, 35, fp) !=NULL) {
		  cle * k = parse_cle(temp);
		   keys2[j] = k;
		   if(eg(keys2[j-1],k) == 0){
			  j++;
		   }
		}
		fclose(fp);



	tournoi t1 = mk_tournoi(keys1[0]);
	file f1 = mk_from_tournoi(t1);
	//toStringFile(f);
	vector<cle *> vec1;
	vec1.reserve(tailleFichier1);
	for(int i = 0; i< tailleFichier1; i++){
		vec1.push_back(keys1[i]);
	}
	f1 = consinter(vec1);


	tournoi t2 = mk_tournoi(keys1[0]);
	file f2 = mk_from_tournoi(t2);
	//toStringFile(f);
	vector<cle *> vec2;
	vec2.reserve(tailleFichier1);
	for(int i = 0; i< tailleFichier2; i++){
		vec2.push_back(keys2[i]);
	}
	f2 = consinter(vec2);
	*/
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	int tailleFichier = 50000;
	string path = ("/home/moumouh/workspace_c++/FilesBinomiales/src/cles_alea/jeu_3_nb_cles_");
	string extension = to_string(tailleFichier) + ".txt";
	path = path + extension;
	//printf("%s",path.c_str());
	FILE* fp = fopen(path.c_str(), "r");
	//FILE* fp = fopen("/users/Etu9/3703039/c++_workspace/File_Binomiales/src/cles_alea/jeu_1_nb_cles_100.txt", "r");
	if(!fp){
		return 0;
	}



	cle * keys[tailleFichier];

	char temp[36] = {0};

	fgets(temp, 35, fp);
	cle * c = parse_cle(temp);
	int j = 1;
	keys[0] = c;
	while(fgets (temp, 35, fp) !=NULL) {
	  cle * k = parse_cle(temp);
	   keys[j] = k;
	   if(eg(keys[j-1],k) == 0){
		  j++;
	   }
	}
	fclose(fp);



	tournoi t1 = mk_tournoi(keys[0]);
	file f1 = mk_from_tournoi(t1);
	//toStringFile(f);
	vector<cle *> vec;
	vec.reserve(tailleFichier);
	for(int i = 0; i< tailleFichier; i++){
		vec.push_back(keys[i]);
	}
	f1 = consinter(vec);
	//toStringFile(f1);

	//
	//file f3 = unionf(f1,f2);

	//toStringFile(f3);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Total time "
			  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			  << "ms.\n";
	cout<<"end" << endl;

	return 0;
}
