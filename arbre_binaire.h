/*
 * arbre_binaire.h
 *
 *  Created on: 9 déc. 2018
 *      Author: moumouh
 */

#ifndef ARBRE_BINAIRE_H_
#define ARBRE_BINAIRE_H_

#include "cle.h"


typedef struct ABR{
	cle * key;
	struct ABR * pere;
	struct ABR * gauche;
	struct ABR * droite;
} ABR;



ABR * ArbreVide();
ABR * ArbreVide();
ABR * ArbreBinaire(cle * e, ABR * g, ABR * d, ABR * p);
int EstArbreVide(ABR * a);
cle * Racine(ABR * a);
ABR * SousArbreGauche(ABR * a);
ABR * SousArbreDroit(ABR * a);
ABR * Pere(ABR * a);
ABR * ABR_Ajout (cle * e, ABR * A);
int Hauteur(ABR * A);
//ABR * RG(ABR * T , ABR * x );
//ABR * RD(ABR * T, ABR * x);
ABR * RG(ABR * A);
ABR * RD(ABR * A);
//ABR * RGD(ABR * T, ABR * x);
//ABR * RDG(ABR * T, ABR * x);
ABR * ArbreDeRotation(ABR * A);
ABR * Equilibrage(ABR * A);
ABR * AVL_Ajout(cle * x, ABR * A);
ABR * Recherche(cle * c, ABR * A);

void toStringABR(ABR * a);

#endif /* ARBRE_BINAIRE_H_ */
