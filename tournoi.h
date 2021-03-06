#include "cle.h"
#include <vector>
#include <iostream>

using namespace std;

struct tournoi {
  cle * key = NULL;
  int degree = 0;
  vector<tournoi> * children = new vector<tournoi>();
};
typedef struct tournoi tournoi;

typedef vector<tournoi> file;

tournoi mk_tournoi(cle* c);

tournoi addChildTournoi(tournoi t, tournoi child);

tournoi uniont(tournoi t1, tournoi t2);

file decapite(tournoi t);

file mk_from_tournoi(tournoi t);

file mk_file();

tournoi mindeg(file f);

file reste(file f);

file ajout_min(tournoi t, file f);

bool vide(file f);

void toStringFile(file f);

void toStringTournoi(tournoi t);

file unionf(file f1, file f2);

file unionft(file f1, file f2, tournoi t);

cle * supprmin(file f);

file ajout(cle * c, file f);

file consinter(vector<cle *> ks);


