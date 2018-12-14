#include <vector>
#include "cle.h"
#include "assert.h"
#include "tournoi.h"
#include <iostream>
using namespace std;


tournoi* mk_tournoi(cle * c, int degree) {
	tournoi * t = (tournoi*) malloc(sizeof(tournoi));
	t->children =(vector<tournoi> *) malloc(degree * sizeof(struct tournoi));
	t->key = c;
	t->degree = degree;
	return std::move(t);
}

tournoi * addChildTournoi(tournoi * t, tournoi * child){
	printf("\n");
	//toStringTournoi(t);
	t->children->push_back(*child);
	t->degree = t->degree + 1;
	//toStringTournoi(t);
	return t;
}


void toStringFile(file * f){
	printf("File {\n");
	for(tournoi i : *f){
		toStringTournoi(&i);
	}
	printf("}\n");
}
void toStringTournoi(tournoi * t){
	printf("Tournoi {\n");
	if(t->key){
		print(t->key);
	}
	printf("  Children :");
	if(t->children->size() > 0 ){
		printf("\n   Child :");
		for(tournoi it : *(t->children)){
			toStringTournoi(&it);
		}
	}else{
		printf("0\n");
	}
	printf("}\n");
}

tournoi* uniont(tournoi* t1, tournoi* t2) {
  tournoi* min = inf(t1->key, t2->key) ? t1 : t2;
  tournoi* max = inf(t1->key, t2->key) ? t2 : t1;
  min->children->push_back(*max);
  return min;
}

file decapite(tournoi* t) {
  return *(t->children);
}

file* mk_from_tournoi(tournoi t) {
	auto f = new vector<tournoi>();
	f->reserve(1);
	f->push_back(t);
	return f;
}

file* mk_file() {
  return new vector<tournoi>();
}

bool vide(file f) {
  return f.size() == 0;
}

tournoi* mindeg(file f) {
  return &(f[0]);
}

file reste(file f) {
  return vector<tournoi>(f.begin()+1, f.end());
}

file ajout_min(tournoi* t, file f) {
  tournoi* min = mindeg(f);
  assert(min->degree > t->degree);
  f.insert(f.begin(), *t);
  return f;
}

file unionf(file f1, file f2);

file unionft(file f1, file f2, tournoi* t) {
	printf("unionft !!!!!!!!!!!");
  if(t->key == NULL) {
    if(vide(f1))
    	printf("f1");
      return f2;
    if(vide(f2))
    	printf("f2");
      return f1;
    tournoi* t1 = mindeg(f1);
    tournoi* t2 = mindeg(f2);
    if(t1->degree < t2->degree)
      return ajout_min(t1, unionf(reste(f1), f2));
    else if(t2->degree < t1->degree)
      return ajout_min(t2, unionf(reste(f2), f1));
    else
      return unionft(reste(f1), reste(f2), uniont(t1,t2));
  }
  else {
    if(vide(f1))
      return unionf(*mk_from_tournoi(*t), f2);
    if(vide(f2))
      return unionf(*mk_from_tournoi(*t), f1);
    tournoi* t1 = mindeg(f1);
    tournoi* t2 = mindeg(f2);
    if(t->degree < t1->degree && t->degree < t2->degree)
      return ajout_min(t, unionf(f1,f2));
    if(t->degree == t1->degree && t->degree == t2->degree)
      return ajout_min(t, unionft(reste(f1),reste(f2), uniont(t1,t2)));
    if(t->degree == t1->degree && t->degree < t2->degree)
      return unionft(reste(f1), f2, uniont(t1,t2));
    if(t->degree < t1->degree && t->degree == t2->degree)
      return unionft(reste(f2), f2, uniont(t2,t));
  }
}

file unionf(file f1, file f2) {
	printf("unionf\n");
	//toStringFile(&f1);
	//toStringFile(&f2);
	//file * f = mk_file();
	tournoi * t = (tournoi*) malloc(sizeof(tournoi));
  return unionft(f1, f2, t);
}

cle * supprmin(file* f) {
  tournoi* min = NULL;
  for(tournoi t : *f) {
    if(min == NULL || inf(t.key, min->key))
      min = &t;
  }
  cle * res = min->key;
  *f = unionf(*f, decapite(min));
  return res;
}

file * ajout(cle* c, file* f) {
	//print(c);
	tournoi* t = mk_tournoi(c,1);
	file * f1 = mk_from_tournoi(*t);
	//toStringFile(f);
	*f = unionf(*f, *f1);
	return f;
}

file consinter(vector<cle> ks) {
  file f = vector<tournoi>();
  for(cle k : ks) {
    ajout(&k, &f);
  }
  return f;
}
