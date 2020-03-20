#include "formula.h"
#include "clause.h"
#include "literal.h"

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
  }
}
