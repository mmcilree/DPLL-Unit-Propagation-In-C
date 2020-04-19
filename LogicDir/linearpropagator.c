#include "formula.h"
#include "clause.h"
#include "literal.h"
#include "clausemap.h"

#include <stdlib.h>
#include <stdio.h>

static Clausemap buildClauseMap(Formula formula) {
  Clause c;
  Clausemap clausemap = new_Clausemap();

  for(int i = 0; i < Formula_getLength(formula); i++) {
    c = Formula_getClause(formula, i);
    Clausemap_associateClause(clausemap, c);
  }

  return clausemap;
}

Clause getUnitsLinear(Formula formula) {
  //Use Clause ADT to store a collection of Literals representing unit Clauses.
  Clause units = new_Clause();
  Clausemap clausemap = buildClauseMap(formula);


  return units;
}
