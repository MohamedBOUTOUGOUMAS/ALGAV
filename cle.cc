#include "cle.c"
#include<vector>

struct tournoi {
  cle* cle;
  int degree;
  vector<tournoi> children;
};
typedef struct tournoi tournoi;

// est_vide(t) := t == null

// degree(t) := t.degree

tournoi* mk_trournoi(cle* c) {
  tournoi *t = malloc(sizeof(tournoi));
  t->cle = c;
  t->degree = 0;
  return t;
}

tournoi* union_tournoi(tournoi* t1, tournoi* t2) {
  tournoi* min = inf(t1->cle, t2->cle) ? t1 : t2;
  tournoi* max = inf(t1->cle, t2->cle) ? t2 : t1;
  min->children.push_back(max);
  return min;
}

file decapite(tournoi* t) {
  return t->children;
}

file mk_from_tournoi(tournoi* t) {
  return new vector().push_back(t);
}

typedef vector<tournoi> file;

file* mk_file() {
  return new vector();
}

