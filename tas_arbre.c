#include <stdlib.h>

#include "tas_arbre.h"

void percolate(node* n) {
  node *min = n;
  if(n->left && inf(n->left->key, n->key))
    min = n->left;
  if(n->right && inf(n->left->key, min->key))
    min = n->right;
  if(min != n) {
    cle *tmp = n->key;
    n->key = min->key;
    min->key = tmp;
    percolate(min);
  }
}

int vide(tas* t) {
  return t->root == NULL;
}

cle *mintas(tas *t) {
  return t->root->key;
}

node *go_to(node* n, int i) {
  if(i == 1)
    return n;
  if(n->parent == NULL)
    return NULL;
  node* parent = go_to(n, i/2);
  if(i % 2 == 0)
    return parent->left;
  else
    return parent->right;
}

void remove_last(tas *t) {
  node* last = t->last;
  node* parent = last->parent;
  free(last);
  if(parent->left == last)
    parent->left = NULL;
  else
    parent->right = NULL;
}

node *add_at_end(tas *t) {
  // TODO
}

void ajout(tas *t, cle* c) {
  node* n = add_at_end(t);
  n->key = c;
  while(n->parent != NULL && inf(n->key, n->parent->key)) {
    cle *tmp = n->key;
    n->key = n->parent->key;
    n->parent->key = tmp;
    n = n->parent;
  }
}

tas* consiter(cle** keys, size_t size) {
  tas* t = malloc(sizeof(tas));
  t->root = NULL;
  t->last = NULL;
  t->size = 0;
  for(size_t i = 0; i < size; i++)
    ajout(t, keys[i]);
  return t;
}

cle *supprmin(tas *t) {
  if(vide(t))
    return NULL;
  cle* min = mintas(t);
  t->root->key = t->last->key;
  remove_last(t);
  percolate(t->root);
  return min;
}

tas *uniontas(tas *t, tas *u) {
  // TODO
}
