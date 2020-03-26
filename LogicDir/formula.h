#ifndef FORMULA_H
#define FORMULA_H

#include "clause.h"

typedef struct Formula* Formula;

Formula new_Formula();
void Formula_free(Formula);
void Formula_addClause(Formula this, Clause c);
void Formula_removeClause(Formula this, int index);
int Formula_getLength(Formula);
Clause Formula_getClause(Formula this, int index);
void Formula_print(Formula);

#endif
