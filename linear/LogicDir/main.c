/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Main: This module contains the entry point for the unit propagation program.    *
 * 180004835                                                                       *
 ***********************************************************************************/
#include "parser.h"
#include "linearpropagator.h"
#include "formula.h"

#include <stdio.h>

int main(void) {
  Formula f = buildFormula();
  Clause units;


  units = getUnits(f);
  Clause_print(units);


  //Cleanup: free all the literals via the set created by the parser
  for(int i = 0; i < Clause_getLength(literalSet); i++) {
    Literal_free(Clause_getLiteral(literalSet, i));
  }
  Clause_free(literalSet);

  //Then we can free the formula
  Formula_free(f);
}

void cleanup() {

}
