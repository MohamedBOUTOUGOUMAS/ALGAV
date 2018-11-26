#include "cle.c"

typedef struct tas {
  cle* cle;
  struct tas* gauche;
  struct tas* droite;
} tas;


// Verifier la hauteur des l'arbre resultant.
// Il faudra désallouer le résultat et l'argument.
tas* supprmin(tas* t) {
  if(!t->gauche) {return t->droite;}
  if(!t->droite) {return t->gauche;}

  tas *min, *max;
  if(inf(t->gauche->cle, t->droite->cle)) {
    min = t->gauche;
    max = t->droite;
  } else {
    min = t->droite;
    max = t->gauche;
  } 
  tas *ret = malloc(sizeof(tas));
  ret->cle = min->cle;
  ret->droite = max;
  ret->gauche = supprmin(min);
  return ret;
} 

tas* ajout(cle* c, tas* t) {
  
}
