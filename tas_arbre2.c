
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
          if(t->gauche && inf(t->gauche->cle, t->cle)) {
               min = t->gauche;
          }
          if(t->droite && inf(t->droite->cle, min->cle)) {
               min = t->droite;
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
     while(1) {
          if(!t->gauche) {return t;}
          if(!t->droite) {return t->gauche;}
          if(t->full)    {t = t->droite; continue;}
          if(t->droite->full) {t = t->gauche; continue;}
          t = t->droite;
     }
}

cle* suppr_min(tas *t) {
     if(!t) {return NULL;}
     cle* min_cle = t->cle;
     t->cle = dernier(t)->cle;
     percoler(t);
     return min_cle;
}

void ajout(cle* c, tas* t) {
}
