#ifndef MAPPING_H
#define MAPPING_H

#include "literal.h"
#include "clause.h"
#include <stdbool.h>

typedef struct Mapping* Mapping;

Mapping new_Mapping(Literal l);
void Mapping_free(Mapping m);
void Mapping_addClause(Mapping m, Clause c);
bool Mapping_isForLiteral(Mapping m, Literal l);

#endif
