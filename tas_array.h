#include "cle.h"
#include <stdlib.h>

typedef struct {
  size_t size;
  size_t capacity;
  cle** a;
} tas;

void ajout(tas *t, cle* c);

int empty(tas *t);

cle* mintas(tas *t);

cle * supprmin(tas *t);

tas * mktas();

tas * consiter(cle** c, size_t size);

tas* uniontas(tas* t, tas* u);

void destroytas(tas *t);
