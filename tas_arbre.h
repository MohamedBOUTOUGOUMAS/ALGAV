#ifndef TAS_ARBRE
#define TAS_ARBRE

#include <stdlib.h>

#include "cle.h"

typedef struct node{
  cle *key;
  struct node *parent;
  struct node *left;
  struct node *right;
} node;
struct node;


typedef struct tas {
  node *root;
  node *last;
  int size;
} tas;

tas *mktas();

int empty(tas* t);

cle *mintas(tas *t);

void ajout(tas *t, cle* c);

tas* consiter(cle** keys, size_t size);

cle *supprmin(tas *t);

tas *uniontas(tas *t, tas *u);

void destroytas(tas *t);

#endif
