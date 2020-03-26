#include "formula.h"
#include "clause.h"
#include "literal.h"

#include <stdlib.h>
#include <stdio.h>

void propagate(Formula formula, Literal x) {
  Clause currentClause;
  int index, nindex;
  Literal nx = Literal_negate(x);

  for(int i = 0; i < Formula_getLength(formula); i++) {
    currentClause = Formula_getClause(formula, i);

    index = Clause_findLiteral(currentClause, x);
    nindex = Clause_findLiteral(currentClause, nx);

    if(index != -1) {
      Formula_removeClause(formula, i);
      i--; //so we don't accidentally skip a clause.
    } else if (nindex != -1) {
      Clause_removeLiteral(currentClause, nindex);
    }

    if(Clause_getLength(currentClause) == 0) {
      //Contradiction
      printf("-\n");
      exit(0);
    }
  }
}

void addUnits(Formula formula, Clause units) {
  Clause current;
  Literal u;
  for(int i = 0; i < Formula_getLength(formula); i++) {
    current = Formula_getClause(formula, i);
    if(Clause_getLength(current) == 1) {
      u = Clause_getLiteral(current, 0);
      if(Clause_findLiteral(units, u) == -1) {
        Clause_addLiteral(units, u);
      }
    }
  }
}

Clause getUnits(Formula formula) {
  Clause units = new_Clause();
  Clause unitClause;
  Literal x;

  while(Formula_getLength(formula) != 0) {
    addUnits(formula, units);

    for(int i = 0; i < Formula_getLength(formula); i++) {
      unitClause = Formula_getClause(formula, i);
      if(unitClause == NULL) {
        Clause_sortLiterals(units);
        return units;
      } else if(Clause_getLength(unitClause) == 1) {
        break;
      } else if(i == Formula_getLength(formula) - 1) {
        Clause_sortLiterals(units);
        return units;
      }
    }
    x = Clause_getLiteral(unitClause, 0);
    propagate(formula, x);
  }

  Clause_sortLiterals(units);
  return units;
}
