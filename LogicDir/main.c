#include "parser.h"
#include "propagator.h"
#include "formula.h"

int main(void) {
  Formula f = buildFormula();
  Clause units = getUnits(f);
  Clause_print(units);
}
