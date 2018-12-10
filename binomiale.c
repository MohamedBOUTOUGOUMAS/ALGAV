#include "cle.c"

struct tournoi {
  cle* cle;
  int degree;
  struct tournoi *children;
};
typedef struct tournoi tournoi;


struct file {
  tournoi* t;
  struct file *rest;
};
typedef struct file file;

file* mk_file() {
  return NULL;
}

tournoi* mk_trournoi(cle* c) {
  tournoi *t = malloc(sizeof(tournoi));
  t->cle = c;
  t->degree = 0;
  t->children = NULL;
  return t;
}

