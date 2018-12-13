#ifndef TAS_ARBRE
#define TAS_ARBRE

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

#endif
