#include <stdlib.h>
#include "arbre_binaire.h"
#include "cle.h"
#include <stdio.h>

/*typedef struct ABR{
	cle * key;
	struct ABR * pere;
	struct ABR * gauche;
	struct ABR * droite;
} ABR;*/



ABR * ArbreVide(){
	ABR * tmp = malloc(sizeof(ABR));
	tmp->key = NULL;
	tmp->pere = NULL;
	tmp->gauche = NULL;
	tmp->droite = NULL;
	return tmp;
}

ABR * ArbreBinaire(cle * e, ABR * g, ABR * d, ABR * p){
	ABR * tmp = ArbreVide();
	if(e){
		tmp->key = e;
	}
	if(g->key){
		tmp->gauche = g;
	}
	if(d->key){
		tmp->droite = d;
	}
	if(p->key){
		tmp->pere = p;
	}
	return tmp;
}

int EstArbreVide(ABR * a){
	if(a->key == NULL){return 1;}
	return 0;
}

cle * Racine(ABR * a){
	return a->key;
}

ABR * SousArbreGauche(ABR * a){
	return a->gauche;
}

ABR * SousArbreDroit(ABR * a){
	return a->droite;
}

ABR * Pere(ABR * a){
	return a->pere;
}


void toStringABR(ABR * a){
	if(a != NULL){
		if(a->key){
			printf("Racine :");
			print(a->key);
		}
		if(!a->gauche){
			printf("fils gauche : NULL \n");
		}else{
			printf("\nfils gauche :");
			print(a->gauche->key);
		}
		if(!a->droite){
			printf("fils droite : NULL \n");
		}else{
			printf("\nfils droite :");
			print(a->droite->key);
			printf("\n");
		}
	}

}


ABR * ABR_Ajout (cle * e, ABR * A){
	//print(e);

	if (EstArbreVide(A)){
		//printf("\nA vide \n");
		ABR * a = ArbreBinaire(e, ArbreVide(), ArbreVide(), A);
		//toStringABR(a);
		return a;
	}else if (eg(e, A->key)){
		//printf("\neg \n");
		return A;
	}else if (inf(e, A->key)){
		if(A->gauche == NULL){A->gauche = ArbreBinaire(NULL, ArbreVide(), ArbreVide(), A);}
		ABR * a = ABR_Ajout(e, A->gauche);
		A->gauche = a;
		return A;
	}else{
		if(A->droite == NULL){A->droite = ArbreBinaire(NULL, ArbreVide(), ArbreVide(), A);}
		//printf("\ninf ajout a droite \n");
		ABR * a = ABR_Ajout(e, A->droite);
		A->droite = a;
		return A;
	}
}



int Hauteur(ABR * A){
	if(!A){
		return 0;
	}
	if(EstArbreVide(A)){
		return 0;
	}
	int h_g = 1 + Hauteur(SousArbreGauche(A));
	int h_d = 1 + Hauteur(SousArbreDroit(A));
	if(h_g >= h_d){
		return h_g;
	}
	return h_d;
}

/* Dans les fonctions de rotation faut vérifier le passage de paramètres soit par valeur soit par adresse*/
/* Ajout des free un peu partout*/



ABR * RG(ABR * A){
	ABR * b = A->droite;
	A->droite = b->gauche;
	b->gauche = A;
	return b;
}

ABR * RD(ABR * A){
	ABR * b = A->gauche;
	A->gauche = b->droite;
	b->droite = A;
	return b;
}




/*ABR * RG(ABR * T , ABR * x ){
	ABR * y = ArbreBinaire(SousArbreDroit(x)->key, SousArbreDroit(x)->gauche, SousArbreDroit(x)->droite, SousArbreDroit(x)->pere);
	x->droite = SousArbreGauche(y);
	if (SousArbreGauche(y)){
		SousArbreGauche(y)->pere = x;
	}
	y->pere = x->pere;
	if(!x->pere){
		T = y;
		//T = ArbreBinaire(y->key,&y->gauche,&y->droite, &y->pere);
	}else if(eg(x->key,SousArbreGauche(x->pere)->key)){
		x->pere->gauche = y;
	}else{
		x->pere->droite = y;
	}
	y->gauche = x;
	x->pere = y;
	return T;
}

/*

ABR * RD(ABR * T, ABR * x){
	ABR * y = ArbreBinaire(SousArbreGauche(x)->key, SousArbreGauche(x)->gauche, SousArbreGauche(x)->droite, SousArbreGauche(x)->pere);
	x->gauche = SousArbreDroit(y);
	if(SousArbreDroit(y)){
		SousArbreDroit(y)->pere = x;
	}
	y->pere = x->pere;
	if(!x->pere){
		T = y;
		//T = ArbreBinaire(y->key,y->gauche,y->droite);
	}else if(eg(x->key,SousArbreDroit(x->pere)->key)){
		x->pere->droite = y;
	}else{
		x->pere->gauche = y;
	}
	y->droite = x;
	x->pere = y;
	return T;
}



ABR * RGD(ABR * T, ABR * x){
	return RD(RG(T,x),x); // à revoir
}

ABR * RDG(ABR * T, ABR * x){
	return RG(RD(T,x),x);
}

ABR * ArbreDeRotation(ABR * A){ // fonction qui cherche le noeud a faire pivoter
	int h_g = Hauteur(SousArbreGauche(A));
	int h_d = Hauteur(SousArbreDroit(A));
	int cpt = 0;
	if((h_g == 1 && h_d > 1)||(h_d == 1 && h_g > 1)){
		if(h_g >= h_d){
			if(h_g - h_d > 2){
				return ArbreDeRotation(SousArbreGauche(A));
			}else{
				return A->gauche;
			}
		}else{
			if(h_d - h_g > 2){
				return ArbreDeRotation(SousArbreDroit(A));
			}else{
				return A->droite;
			}
		}
	}
	if(h_g >= h_d){
		return ArbreDeRotation(SousArbreGauche(A));
	}else{
		return ArbreDeRotation(SousArbreDroit(A));
	}
}

ABR * Equilibrage(ABR * A){
	ABR * p = ArbreBinaire(A->key,&A->gauche,&A->droite, &A->pere);
	ABR * ar = ArbreDeRotation(p); // arbre a faire pivoter
	ABR * papa = ar->pere;
	int h_g = Hauteur(SousArbreGauche(ar));
	int h_d = Hauteur(SousArbreDroit(ar));
	if(papa->gauche == ar){
		if(h_g >= h_d){
			return RD(p, papa);
		}else{
			return RGD(p, papa);
		}
	}else if(papa->droite == ar){
		if(h_g >= h_d){
			return RDG(p, papa);
		}else{
			return RG(p, papa);
		}
	}
	return p;
}
*/

ABR * Equilibrage(ABR * A){
	ABR * g = A->gauche;
	ABR * d = A->droite;
	int h_g = Hauteur(g);
	int h_d = Hauteur(d);
	int diff = h_g - h_d;
	if(diff == 2){
		if(Hauteur(g->gauche) < Hauteur(g->droite)){
			A->gauche = RG(g);
		}
		return RD(A);
	}else if(diff == -2){
		if(Hauteur(d->gauche) > Hauteur(d->droite)){
			A->droite = RD(d);
		}
		return RG(A);
	}else{
		return A;
	}
}
/*
ABR * AVL_Ajout(cle * x, ABR * A){
	if (EstArbreVide(A)){
		return ArbreBinaire(x, ArbreVide (), ArbreVide (), ArbreVide());
	}
	if (x == Racine(A)){
		return A;
	}
	if (inf(x,Racine(A))){
		return Equilibrage(ArbreBinaire(Racine(A),AVL_Ajout(x,SousArbreGauche(A)),SousArbreDroit(A), &A->pere));
	}else{
		return Equilibrage ( ArbreBinaire ( Racine (A),SousArbreGauche (A),AVL_Ajout (x, SousArbreDroit (A)), &A->pere));
	}
}


ABR * Recherche(cle * c, ABR * A){
	if(eg(c,Racine(A))){
		return A;
	}else if(inf(c,Racine(A))){
		return Recherche(c, &A->gauche);
	}else{
		return Recherche(c, &A->droite);
	}
}


*/






