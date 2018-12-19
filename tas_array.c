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
  size_t min = i;
  if(l < t->size && inf(t->a[l], t->a[i]))
    min = l;
  if(r < t->size && inf(t->a[r], t->a[min]))
    min = r;
  if(min != i) {
    cle* tmp = t->a[min];
    t->a[min] = t->a[i];
    t->a[i] = tmp;
    percoler(t, min);
  }
}

void resize(tas *t, size_t newsize) {
  t->size = newsize;
  if(newsize > t->capacity) {
    t->a = realloc(t->a, t->capacity * sizeof(cle*) * 2);
    t->capacity = t->capacity * 2;
  }
}


/* Ajoute un élément à un tas en respectant l'invariant.
 */
void ajout(tas *t, cle* c) {
  resize(t, t->size + 1);
  t->a[t->size - 1] = c;
  size_t i = t->size - 1;
  while(i > 1 && inf(t->a[i], t->a[PARENT(i)])) {
    cle *tmp = t->a[i];
    t->a[i] = t->a[PARENT(i)];
    t->a[PARENT(i)] = tmp;
    i = PARENT(i);
  }
}

cle* mintas(tas *t) {
  return t->a[0];
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
  tas* t = malloc(sizeof(tas));
  t->a = malloc(MIN_CAPACITY * sizeof(cle*));
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
  t->capacity = size;
  for(int i = t->size / 2; i >= 0; i--) {
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

tas * uniontas(tas *t, tas *u) {
  size_t new_size = t->size + u->size;
  cle** new_a = malloc(new_size * sizeof(cle*));
  size_t i = 0;
  while(i < t->size) {
    new_a[i] = t->a[i];
    i++;
  }
  while(i < new_size) {
    new_a[i] = u->a[i - t->size];
    i++;
  }
  destroytas(t);
  destroytas(u);
  return consiter(new_a, new_size);
}

/* tas* uniontas(tas* t, tas* u) { */
/*   tas *big, *small; */
/*   if(t->capacity > u->capacity) { */
/*     big = t; */
/*     small = u; */
/*   } else { */
/*     big = u; */
/*     small = t; */
/*   } */
/*   size_t old_big_size = big->size; */
/*   resize(big, big->size + small->size); */
/*   memcpy(big->a + old_big_size * sizeof(cle*), small->a, */
/*          small->size * sizeof(cle*)); */
/*   tas *result = consiter(big->a, big->size); */
/*   destroytas(small); */
/*   destroytas(big); */
/*   return result; */
/* } */
