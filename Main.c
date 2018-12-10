
#include <stdlib.h>
#include <stdio.h>
#include "cle.h"
#include "arbre_binaire.h"

int main(){
	cle * c = getKey();
	ABR * a = ArbreVide();
	a->cle = c;
	print(a->cle);
	return 0;
}
