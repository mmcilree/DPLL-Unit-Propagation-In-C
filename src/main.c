#include "parser.h"
#include "propagator.h"
#include "formula.h"

int main(void) {
  Formula f = buildFormula();
  Literal x = Clause_getLiteral(Formula_getClause(f, 0), 0);
  propagate(f, x);

  Formula_print(f);
}
