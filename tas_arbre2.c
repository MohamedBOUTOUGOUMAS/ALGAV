#include "cle.c"

typedef struct tas {
  cle* cle;
  int full;
  struct tas *gauche;
  struct tas *droite;
} tas;

void percoler(tas *arg) {
  tas *t = arg;
  while(t) {
    tas *min = t;
    if(tas->gauche && inf(tas->gauche->cle, tas->cle)) {
      min = tas.gauche;
    }
    if(tas->droite && inf(tas->droite->cle, min->cle)) {
      min = tas.droite;
    }
    if(min != t) {
      cle* tmp = t->cle;
      t->cle = min->cle;
      min->cle = tmp;
      t = min;
    } else {
      t = NULL;
    }
  }
}

tas* dernier(tas* arg) {
  tas *t = arg;
  if(!t) {return NULL;}
  while(...) {
    if(!t->gauche) {return t;}
    if(!t->droite) {return t->gauche;}
    if(t->full) {
      t = t->droite;
    } else {
      t = t->gauche;
    }
  }
}

cle* suppr_min(tas *t) {
  if(!t) {return NULL;}
  cle* min_cle = t->cle;
  t->cle = dernier(t)->cle;
  percoler(t);
  return min_cle;
}

tas* 

void ajout(cle* c, tas* t) {
}
