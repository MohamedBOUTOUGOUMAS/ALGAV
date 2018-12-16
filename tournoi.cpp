#include <vector>
#include "cle.h"
#include "assert.h"
#include "tournoi.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

tournoi mk_tournoi(cle * c) {
	tournoi * t = (tournoi*) malloc(sizeof(tournoi));
	t->key = c;
	t->degree = 0;
	t->children = new vector<tournoi>();
	return std::move(*t);
}

tournoi addChildTournoi(tournoi t, tournoi child) {
	printf("\n");
	//toStringTournoi(t);
	t.children->push_back(child);
	t.degree = t.degree + 1;
	//toStringTournoi(t);
	return t;
}

void toStringFile(file f) {
	printf("File {\n");
	printf("Tournois : %d\n",f.size());
	for (tournoi i : f) {
		toStringTournoi(i);
	}
	printf("}\n");
}
void toStringTournoi(tournoi t) {
	int sz = 0;
	sz = t.degree;
	printf("Tournoi {\n");
	if (t.key) {
		print(t.key);
	}
	printf("Children : %d", sz);
	if (sz > 0) {
		for (tournoi it : *t.children) {
			printf("\nChild :");
			toStringTournoi(it);
		}
	}
	printf("\n}\n");
}

tournoi uniont(tournoi t1, tournoi t2) {
	tournoi min = inf(t1.key, t2.key) ? t1 : t2;
	tournoi max = inf(t1.key, t2.key) ? t2 : t1;
	min.children->push_back(max);
	min.degree = min.degree + 1;
	return min;
}

file decapite(tournoi t) {
	return *t.children;
}

file mk_from_tournoi(tournoi t) {
	auto f = new vector<tournoi>();
	f->reserve(1);
	f->push_back(t);
	return *f;
}

file mk_file() {
	return vector<tournoi>();
}

bool vide(file f) {
	return f.size() == 0;
}

tournoi mindeg(file f) {
	return std::move(f.at(0));
}

file reste(file f) {
	return vector<tournoi>(f.begin() + 1, f.end());
}

file ajout_min(tournoi t, file f) {
	tournoi min = f.at(0);
	assert(min.degree > t.degree);
	f.insert(f.begin(), t);
	return std::move(f);
}

file unionf(file f1, file f2);

file unionft(file f1, file f2, tournoi t) {
	//std::cout<<"unionft"<<std::endl;
	if (t.key == NULL) {
		//std::cout<<"ok"<<std::endl;
		if (vide(f1)) {
			//std::cout<<"f2"<<std::endl;
			return std::move(f2);
		}
		if (vide(f2)){
			//std::cout<<"f1"<<std::endl;
			return std::move(f1);
		}
		tournoi t1 = f1.at(0);/*mindeg(f1);*/
		tournoi t2 = f2.at(0);/*mindeg(f2);*/
		if (t1.degree < t2.degree){
			//std::cout<<"!!!!!!!!!!!!!!"<<std::endl;
			file u = mk_file();
			u = unionf(reste(f1), f2);
			file res = mk_file();
			res = ajout_min(t1, u);
			return std::move(res);
		}
		else if (t2.degree < t1.degree){
			//std::cout<<"???????????????"<<std::endl;
			file res = mk_file();
			res = ajout_min(t2, unionf(reste(f2), f1));
			return std::move(res);
		}
		else{
			//std::cout<<"piiiiiiiiiiiiiiii"<<std::endl;
			tournoi u = uniont(t1, t2);
			file res = mk_file();
			res = unionft(reste(f1), reste(f2), u);
			return std::move(res);
		}
	} else {
		//std::cout<<"yeahhhhhhhhhhhhhhhhh"<<std::endl;
		if (vide(f1)){
			//std::cout<<"^^^^^^^^^^^^^^^^^^^"<<std::endl;
			file ftmp = mk_from_tournoi(t);
			file u = mk_file();
			u = unionf(ftmp, f2);
			return std::move(u);
		}
		if (vide(f2)){
			//std::cout<<"$$$$$$$$$$$$$$$$$$$"<<std::endl;
			file ftmp = mk_from_tournoi(t);
			file u = mk_file();
			u = unionf(ftmp, f1);
			return std::move(u);
		}
		tournoi t1 = f1.at(0);
		tournoi t2 = f2.at(0);
		if (t.degree < t1.degree && t.degree < t2.degree){
			//std::cout<<"jjjjjjjjjjjjjjjjjjjjjjjj"<<std::endl;
			file u = mk_file();
			u = unionf(f1, f2);
			file res = mk_file();
			res = ajout_min(t, u);
			return std::move(res);
		}
		if (t.degree == t1.degree && t.degree == t2.degree){
			//std::cout<<"ùùùùùùùùùùùùùùùùùùùùù"<<std::endl;
			tournoi ut = uniont(t1, t2);
			file uf = mk_file();
			uf = unionft(reste(f1), reste(f2), ut);
			file res = mk_file();
			res = ajout_min(t, uf);
			return std::move(res);
		}
		if (t.degree == t1.degree && t.degree < t2.degree){
			//std::cout<<"......................."<<std::endl;
			tournoi ut = uniont(t1, t2);
			file uf = mk_file();
			uf = unionft(reste(f1), f2, ut);
			return std::move(uf);
		}
		if (t.degree < t1.degree && t.degree == t2.degree){
			//std::cout<<"/////////////////////////"<<std::endl;
			tournoi ut = uniont(t2, t);
			file uf = mk_file();
			uf = unionft(reste(f2), f2, ut);
			return std::move(uf);
		}
	}
	return std::move(f1);
}

file unionf(file f1, file f2) {
	//std::cout<<"unionf"<<std::endl;
	tournoi * t = (tournoi*) malloc(sizeof(tournoi));
	t->key = NULL;
	t->degree = 0;
	t->children = new vector<tournoi>();
	file res = mk_file();
	res = unionft(f1, f2, *t);
	//toStringFile(res);
	//toStringFile(f2);
	free(t);
	return std::move(res);
}

cle * supprmin(file f) {
	tournoi min = mk_tournoi(NULL);
	for (tournoi t : f) {
		if (min.key == NULL || inf(t.key, min.key))
			min = t;
	}
	cle * res = min.key;
	f = unionf(f, decapite(min));
	return std::move(res);
}

file ajout(cle * c, file f) {
	//std::cout<<"ajout"<<std::endl;
	tournoi t = mk_tournoi(c);
	file f1 = mk_from_tournoi(t);
	file u = unionf(f, f1);
	//toStringFile(u);
	return std::move(u);
}

file consinter(vector<cle *> ks) {
	file f = mk_file();
	for (unsigned i = 0; i<ks.size(); i++) {
		f = ajout(ks.at(i),f);
	}
	//toStringFile(f);
	return std::move(f);
}
