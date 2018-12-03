#include "cle.c"
#include <math.h>


typedef struct tas {
  cle* cle;
  int full;
  int nb_noeuds;
  struct tas *gauche;
  struct tas *droite;
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
		if(hauteur >= int(log(nb_noeuds))+1){
			return 0;
		}
		tas * tmp;
		tmp->cle = c;
		p->gauche = tmp;
		percoler(p);
		t = p;
		return 1;
	}else if(!p->droite){
		if(hauteur >= int(log(nb_noeuds))+1){
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

}

tas * consIter(cle * list[], tas * t){
	int taille = sizeof(list)/sizeof(struct cle);
	for(int i = 0; i<taille;i++){
		t->nb_noeuds = t->nb_noeuds + ajout(list[i],t,1,t->nb_noeuds);
	}
	return t;
}



tas * Union(tas * t1, tas * t2){ /* a terminer!!!!!!!!!!!*/
	tas * tas_u = newTas();
	tas * p = t1;
	tas * q = t2;
	while(p && q){
		tas * tmp_g = newTas();
		tas * tmp_d = newTas();
		if(inf(p->cle,q->cle)){
			if(!tas_u->cle){
				tas_u->cle = p->cle;
				tmp_g->cle = q->cle;
				tas_u->gauche = tmp_g;
			}else if(!tas_u->gauche){
				tmp_g->cle = p->cle;
				tmp_d->cle = q->cle;
				tas_u->gauche = tmp_g;
				tas_u->droite = tmp_d;
			}else if(!tas_u->droite){
				tmp_d->cle = p->cle;
				tmp_g->cle = q->cle;
				tas_u->droite = tmp_d;
				tas * next = newTas();
				next = tas_u->gauche;
				next->gauche = tmp_g;
			}
		}else{
			if(!tas_u->cle){
				tas_u->cle = q->cle;
				tmp_g->cle = p->cle;
				tas_u->gauche = tmp_g;
			}else if(!tas_u->gauche){
				tmp_g->cle = q->cle;
				tmp_d->cle = p->cle;
				tas_u->gauche = tmp_g;
				tas_u->droite = tmp_d;
			}else if(!tas_u->droite){
				tmp_d->cle = q->cle;
				tmp_g->cle = p->cle;
				tas_u->droite = tmp_d;
				tas * next = newTas();
				next = tas_u->gauche;
				next->gauche = tmp_g;
			}
		}
		p = p->gauche;
		q = q->gauche;
	}
}











