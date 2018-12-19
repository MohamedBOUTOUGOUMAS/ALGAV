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

node *mknode() {
  node* n = malloc(sizeof(node));
  n->parent = NULL;
  n->left = NULL;
  n->right = NULL;
  n->key = NULL;
  return n;
}

tas *mktas() {
  tas *t = malloc(sizeof(tas));
  t->root = NULL;
  t->last = NULL;
  t->size = 0;
  return t;
}

int empty(tas* t) {
  return t->root == NULL;
}

int is_root(node* n) {
  return n->parent == NULL;
}

cle *mintas(tas *t) {
  if(empty(t))
    return NULL;
  return t->root->key;
}

node *go_to(tas* t, int i) {
  if(empty(t))
    return NULL;
  if(i == 1)
    return t->root;
  node* parent = go_to(t, i/2);
  if(i % 2 == 0)
    return parent->left;
  else
    return parent->right;
}

void remove_last(tas *t) {
  if(empty(t))
    return;
  node* last = t->last;
  if(!last->parent) { // then there's only one element
    free(t->root);
    return;
  } // Otherwise, there's more
  node* parent = last->parent;
  if(parent->left == last)
    parent->left = NULL;
  else
    parent->right = NULL;
  free(last);
  t->size--;
  t->last = go_to(t, t->size);
}

node *add_at_end(tas *t) {
  node *new_last = mknode();
  if(empty(t)) {
    t->root = new_last;
    t->last = new_last;
  } else {
    node *parent = go_to(t, (t->size + 1) / 2);
    new_last->parent = parent;
    if(!parent->left)
      parent->left = new_last;
    else
      parent->right = new_last;
  }
  t->size++;
  return new_last;
}

void ajout(tas *t, cle* c) {
  node* n = add_at_end(t);
  n->key = c;
  while(!is_root(n) && inf(n->key, n->parent->key)) {
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
  if(empty(t))
    return NULL;
  cle* min = mintas(t);
  t->root->key = t->last->key;
  remove_last(t);
  percolate(t->root);
  return min;
}

int fill_from_node(node* n, cle** k, int idx) {
  if(!n)
    return idx;
  idx = fill_from_node(n->left, k, idx);
  idx = fill_from_node(n->right, k, idx);  
  k[idx] = n->key;
  return idx + 1;
}

cle** keys(tas* t) {
  cle** k = malloc(t->size * sizeof(cle*));
  fill_from_node(t->root, k, 0);
  return k;
}

tas *uniontas(tas *t, tas *u) {
  tas *big, *small;
  if(t->size > u->size) {
    big = t;
    small = u;
  } else {
    big = u;
    small = t;
  }
  cle** cles = keys(small);
  for(size_t i = 0; i < small->size; i++)
    ajout(big, cles[i]);
  return big;
}

void destroynode(node *n) {
  if(!n)
    return;
  destroynode(n->left);
  destroynode(n->right);
  free(n);
}

void destroytas(tas *t) {
  if(!t)
    return;
  destroynode(t->root);
  free(t);
}
