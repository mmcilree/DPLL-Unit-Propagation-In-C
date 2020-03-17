#ifndef CLAUSE_H
#define CLAUSE_H

typedef struct Clause* Clause;

Clause new_Clause();
void Clause_free(Clause);
void Clause_addLiteral(Clause this, Literal l);
int Clause_getLength(Clause);
Literal Clause_getLiteral(Clause this, int index);
#endif
