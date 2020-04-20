#ifndef MAPPING_H
#define MAPPING_H

#include "literal.h"
#include "clause.h"
#include <stdbool.h>

typedef struct Mapping* Mapping;

Mapping new_Mapping(Literal l);
void Mapping_free(Mapping m);
void Mapping_addPosClause(Mapping m, Clause c);
void Mapping_addNegClause(Mapping m, Clause c);
bool Mapping_isForLiteral(Mapping m, Literal l);
int Mapping_getLength(Mapping);
Literal Mapping_getLiteral(Mapping);
Clause Mapping_modifyClauses(Mapping);
void Mapping_print(Mapping);
#endif
