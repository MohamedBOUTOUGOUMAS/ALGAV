#include "cle.h"

typedef struct {
  size_t size;
  size_t capacity;
  cle** a;
} tas;

void ajout(tas *t, cle* c);

cle* min(tas t);

cle * supprmin(tas *t);

tas * mktasvide();

tas * consiter(cle** c, size_t size);

tas* uniontas(tas* t, tas* u);

void destroytas(tas *t);
