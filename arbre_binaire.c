#include "cle.c"

typedef struct ABR{
	cle * cle;
	struct ABR * pere;
	struct ABR * gauche;
	struct ABR * droite;
} ABR;



ABR * ArbreVide(){
	ABR * tmp;
	tmp->cle = NULL;
	tmp->pere = NULL;
	tmp->gauche = NULL;
	tmp->droite = NULL;
	return tmp;
}

ABR * ArbreBinaire(cle * e, ABR g, ABR d){
	ABR * tmp;
	tmp->cle = e;
	tmp->pere = NULL;
	tmp->gauche = g;
	tmp->droite = d;
	return tmp;
}

int EstArbreVide(ABR a){
	if(!a.cle){return 1;}
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
	if (EstArbreVide (A)){
		return ArbreBinaire (e, ArbreVide (), ArbreVide ());
	}else if (eg(e,Racine (A))){
		return A;
	}else if (inf(e, Racine (A))){
		return ArbreBinaire (Racine (A), ABR_Ajout (e, SousArbreGauche (A)),SousArbreDroit (A));
	}else{
		return ArbreBinaire (Racine (A), SousArbreGauche (A),ABR_Ajout (e, SousArbreDroit (A)));
	}
}

int Hauteur(ABR * A){
	ABR * p = A;
	if(!p){return 0;}
	if(EstArbreVide(p)){return 0;}
	int h_g = 1 + Hauteur(SousArbreGauche(p));
	int h_d = 1 + Hauteur(SousArbreDroit(p));
	if(h_g >= h_d){
		return h_g;
	}
	return h_d;
}


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

















