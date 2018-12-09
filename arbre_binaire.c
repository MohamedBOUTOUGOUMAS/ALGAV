#include "arbre_binaire.h"
#include "cle.c"


ABR * ArbreVide(){
	ABR * tmp;
	tmp->cle = NULL;
	tmp->pere = NULL;
	tmp->gauche = NULL;
	tmp->droite = NULL;
	return tmp;
}

ABR * ArbreBinaire(cle * e, ABR * g, ABR * d){
	ABR * tmp;
	tmp->cle = e;
	tmp->pere = NULL;
	tmp->gauche = g;
	tmp->droite = d;
	return tmp;
}

int EstArbreVide(ABR * a){
	if(!a->cle){return 1;}
	return 0;
}

cle * Racine(ABR * a){
	return a->cle;
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


ABR * ABR_Ajout (cle * e, ABR * A){
	if (EstArbreVide(A)){
		return ArbreBinaire(e, ArbreVide(), ArbreVide());
	}else if (eg(e,Racine(A))){
		return A;
	}else if (inf(e, Racine(A))){
		return ArbreBinaire(Racine(A), ABR_Ajout (e, SousArbreGauche(A)),SousArbreDroit(A));
	}else{
		return ArbreBinaire(Racine(A), SousArbreGauche(A),ABR_Ajout(e, SousArbreDroit(A)));
	}
}

int Hauteur(ABR * A){
	ABR * p = A;
	if(!p){return 0;}
	if(EstArbreVide(p)){return 0;}
	if(!p->gauche){return 0;}
	if(!p->droite){return 0;}
	int h_g = 1 + Hauteur(SousArbreGauche(p));
	int h_d = 1 + Hauteur(SousArbreDroit(p));
	if(h_g >= h_d){
		return h_g;
	}
	return h_d;
}

/* Dans les fonctions de rotation faut vérifier le passage de paramètres soit par valeur soit par adresse*/
/* Ajout des free un peu partout*/


ABR * RG(ABR * T , ABR * x ){
	ABR * y = SousArbreDroit(x);
	x->droite = SousArbreGauche(y);
	if (SousArbreGauche(y)){
		SousArbreGauche(y)->pere = x;
	}
	y->pere = x->pere;
	if(!x->pere){
		T = y;
	}else if(eg(x->cle,SousArbreGauche(x->pere)->cle)){
		x->pere->gauche = y;
	}else{
		x->pere->droite = y;
	}
	y->gauche = x;
	x->pere = y;
	return T;
}



ABR * RD(ABR * T, ABR * x){
	ABR * y = SousArbreGauche(x);
	x->gauche = SousArbreDroit(y);
	if(SousArbreDroit(y)){
		SousArbreDroit(y)->pere = x;
	}
	y->pere = x->pere;
	if(!x->pere){
		T = y;
	}else if(eg(x->cle,SousArbreDroit(x->pere)->cle)){
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
	ABR * p = A;
	ABR * ar = ArbreDeRotation(p); // arbre a faire pivoter
	ABR * papa = ar->pere;
	int h_g = Hauteur(SousArbreGauche(ar));
	int h_d = Hauteur(SousArbreDroit(ar));
	if(papa->gauche == ar){
		if(h_g >= h_d){
			RD(p, papa);
		}else{
			RGD(p, papa);
		}
	}else if(papa->droite == ar){
		if(h_g >= h_d){
			RDG(p, papa);
		}else{
			RG(p, papa);
		}
	}
	A = p;
	return A;
}

ABR * AVL_Ajout(cle * x, ABR * A){
	if (EstArbreVide(A)){
		return ArbreBinaire(x, ArbreVide (), ArbreVide ());
	}
	if (x == Racine(A)){
		return A;
	}
	if (inf(x,Racine(A))){
		return Equilibrage(ArbreBinaire(Racine(A),AVL_Ajout(x,SousArbreGauche(A)),SousArbreDroit(A)));
	}else{
		return Equilibrage ( ArbreBinaire ( Racine (A),SousArbreGauche (A),AVL_Ajout (x, SousArbreDroit (A))));
	}
}


ABR * Recherche(cle * c, ABR * A){
	if(eg(c,Racine(A))){
		return A;
	}else if(inf(c,Racine(A))){
		return Recherche(c,A->gauche);
	}else{
		return Recherche(c,A->droite);
	}
}









