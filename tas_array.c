#include <stdlib.h>
#include <string.h>

#include "cle.h"
#include "tas_array.h"

#define PARENT(n) ( (n) / 2 )
#define LEFT(n) ( (n) * 2 )
#define RIGHT(n) ( (n) * 2 + 1 )
#define MIN_CAPACITY 16

/* Maintient l'invariant des tas:
   Si les sous-tas enracinés en LEFT(i) et RIGHT(i) satisfont l'invariant,
   Alors après l'exécution le sous-tas enraciné en i le satisfait.
 */
void percoler(tas* t, size_t i) {
  size_t l = LEFT(i);
  size_t r = RIGHT(i);
  size_t max = i;
  if(l <= t->size && inf(t->a[l], t->a[i]))
    max = l;
  if(r <= t->size && inf(t->a[r], t->a[max]))
    max = r;
  if(max != i) {
    cle* tmp = t->a[max];
    t->a[max] = t->a[i];
    t->a[i] = tmp;
    percoler(t, max);
  }
}

void resize(tas *t, size_t newsize) {
  if(newsize < t->capacity / 2) {
    t->a = realloc(t->a, t->capacity * sizeof(cle*) / 2);
    t->capacity = t->capacity / 2;
  }
  else if(newsize > t->capacity) {
    t->a = realloc(t->a, t->capacity * sizeof(cle*) * 2);
    t->capacity = t->capacity * 2;
  }
}


/* Ajoute un élément à un tas en respectant l'invariant.
 */
void ajout(tas *t, cle* c) {
  resize(t, t->size + 1);
  t->a[t->size] = c;
  size_t i = t->size - 1;
  while(i > 1 && inf(t->a[i], t->a[PARENT(i)])) {
    cle *tmp = t->a[i];
    t->a[i] = t->a[PARENT(i)];
    t->a[PARENT(i)] = tmp;
  }
}

cle* min(tas t) {
  return t.a[0];
}

int empty(tas *t) {
  return t->size == 0;
}

/* Supprime et renvoie la clé minimale d'un tas.
   Respecte l'invariant
 */
cle * supprmin(tas *t) {
  cle *c = t->a[0];
  t->a[0] = t->a[t->size-1];
  t->size--;
  percoler(t, 0);
  resize(t, t->size);
  return c;
}

/* créer un tas de faible capacité sans éléments
 * le tas retourné devra être libéré par l'appelant
 */
tas * mktas() {
  tas* t = malloc(sizeof(tas) * MIN_CAPACITY);
  t->capacity = MIN_CAPACITY;
  t->size = 0;
  return t;
}

/* Crée un tas à partir d'un tableau de clé,
   en utilisant un tableau de clé pour le stockage.
   la fonction prend le controle de c.
   les clés ne sont pas copiées.
   Le tas doit être détruit par l'appelant
*/
tas * consiter(cle** c, size_t size) {
  tas *t = malloc(sizeof(tas));
  t->a = c;
  t->size = size;
  t->capacity = sizeof(c)/sizeof(cle*);;
  for(int i = t->size / 2; i > 0; i--) {
    percoler(t, i);
  }
  return t;
}

void destroytas(tas *t) {
  free(t->a);
  free(t);
}

/* fait l'union de deux tas en temps linéaire
   détruit les deux tas en arguments
   le tas résultant doit être détruit par l'appelant
*/
tas* uniontas(tas* t, tas* u) {
  tas *big, *small;
  if(t->capacity > u->capacity) {
    big = t;
    small = u;
  } else {
    big = u;
    small = t;
  }
  resize(big, big->size + small->size);
  memcpy(big->a + big->size * sizeof(cle*), small->a,
         small->size * sizeof(cle*));
  destroytas(small);
  return consiter(big->a, big->size + small->size);
}
