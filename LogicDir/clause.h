#ifndef CLAUSE_H
#define CLAUSE_H

#include "literal.h"

typedef struct Clause* Clause;

Clause new_Clause();
void Clause_free(Clause);
void Clause_addLiteral(Clause this, Literal l);
void Clause_removeLiteral(Clause this, int index);
int Clause_getLength(Clause);
Literal Clause_getLiteral(Clause this, int index);
int Clause_findLiteral(Clause this, Literal l);
void Clause_print(Clause);
void Clause_sortLiterals(Clause this);

#endif
