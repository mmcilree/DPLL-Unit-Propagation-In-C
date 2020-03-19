#ifndef CLAUSE_H
#define CLAUSE_H

#include "literal.h"

typedef struct Clause* Clause;

Clause new_Clause();
void Clause_free(Clause);
void Clause_addLiteral(Clause this, Literal l);
int Clause_getLength(Clause);
Literal Clause_getLiteral(Clause this, int index);
bool Clause_containsLiteral(Clause this, Literal l);
void Clause_print(Clause);
#endif
