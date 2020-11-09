/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Main: This module contains the entry point for the unit propagation program.    *
 * 180004835                                                                       *
 ***********************************************************************************/
#include "parser.h"
#include "propagator.h"
#include "formula.h"

int main(void) {
  Formula f = buildFormula();
  Clause units = getUnits(f);
  Clause_print(units);
}
