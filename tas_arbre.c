
#include "cle.c"
#include <math.h>


typedef struct tas {
<<<<<<< HEAD
     cle* cle;
     int full;
     struct tas *gauche;
     struct tas *droite;
=======
  cle* cle;
  int full;
  int nb_noeuds;
  struct tas *gauche;
  struct tas *droite;
>>>>>>> e2c88a68ba46810fc0243aaa1ac4052f5201a6e3
} tas;

tas * newTas(){
	tas * p;
	p->cle = NULL;
	p->nb_noeuds = 0;
	p->gauche = NULL;
	p->droite = NULL;
	p->full = 0;
	return p;
}

void percoler(tas *arg) {
<<<<<<< HEAD
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
=======
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
  while(t) {
    if(!t->gauche) {return t;}
    if(!t->droite) {return t->gauche;}
    if(t->full) {
      t = t->droite;
    } else {
      t = t->gauche;
    }
  }
>>>>>>> e2c88a68ba46810fc0243aaa1ac4052f5201a6e3
}

cle* suppr_min(tas *t) {
     if(!t) {return NULL;}
     cle* min_cle = t->cle;
     t->cle = dernier(t)->cle;
     percoler(t);
     return min_cle;
}

<<<<<<< HEAD
void ajout(cle* c, tas* t) {
=======
int ajout(cle* c, tas* t, int hauteur, int nb_noeuds) {

	tas * p = t;
	if(!p){
		p = newTas();
		p->cle = c;
		return 1;
	}else if(!p->gauche){
		/* hauteur est initialisé a 1
		 *
		 * nb_noeuds+1 pour voir au dernier niveau si on
		 * ajoute dans une nouvelle ligne ou pas !
		 *
		 * hauteur et nb_noeuds sont donnés pendant le premier appel de ajout
		 * */
		if(hauteur >= ((int)log(nb_noeuds))+1){
			return 0;
		}
		tas * tmp;
		tmp->cle = c;
		p->gauche = tmp;
		percoler(p);
		t = p;
		return 1;
	}else if(!p->droite){
		if(hauteur >= ((int)log(nb_noeuds)) +1){
			return 0;
		}
		tas * tmp;
		tmp->cle = c;
		p->droite = tmp;
		percoler(p);
		t = p;
		return 1;
	}else if(ajout(c,p->gauche,hauteur+1,nb_noeuds) == 0){ // on n'a pas pu ajouter
		return ajout(c,p->droite,hauteur+1,nb_noeuds);
	}
return 0;
}

tas * consIter(cle * list[], tas * t){
	int taille = sizeof(list)/sizeof(cle);
	for(int i = 0; i<taille;i++){
		t->nb_noeuds = t->nb_noeuds + ajout(list[i],t,1,t->nb_noeuds);
	}
	return t;
}



int ajout_sans_percoler(cle * c, tas * t, int hauteur, int nb_noeuds){
	tas * tmp = newTas();
	tmp->cle = c;
	if(!t){
		t = tmp;
	}else if(!t->gauche){
		if(hauteur >= ((int)log(nb_noeuds)) +1){
			return 0;
		}
		t->gauche = tmp;
		return 1;
	}else if(!t->droite){
		if(hauteur >= ((int)log(nb_noeuds)) +1){
			return 0;
		}
		t->droite = tmp;
		return 1;
	}
	if(ajout_sans_percoler(c,t->gauche,hauteur+1,nb_noeuds) == 0){
		return ajout_sans_percoler(c,t->droite,hauteur+1,nb_noeuds);
	}
return 0;
}


void infix(tas * t,tas * tas_u) {
    if (t->gauche) infix(t->gauche,tas_u);
    tas_u->nb_noeuds = tas_u->nb_noeuds + ajout_sans_percoler(t->cle, tas_u, 1, tas_u->nb_noeuds);
    if (t->droite) infix(t->droite,tas_u);
>>>>>>> e2c88a68ba46810fc0243aaa1ac4052f5201a6e3
}

tas * Union(tas * t1, tas * t2){ 
	tas * tas_u = newTas();
	tas * p = t1;
	tas * q = t2;
	infix(p,tas_u);
	infix(q,tas_u);
	percoler(tas_u);
	return tas_u;
}











