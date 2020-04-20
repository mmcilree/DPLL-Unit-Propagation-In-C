#include "formula.h"
#include "clause.h"
#include "literal.h"
#include "clausemap.h"
#include "propagator.h"
#include "mapping.h"

#include <stdlib.h>
#include <stdio.h>

static Clausemap buildClauseMap(Formula formula) {
  Clause c;
  Clausemap clausemap = new_Clausemap();

  for(int i = 0; i < Formula_getLength(formula); i++) {
    c = Formula_getClause(formula, i);
    Clausemap_associateClause(clausemap, c);
  }
  Clause_free(c);
  return clausemap;
}

Clause getUnitsLinear(Formula formula) {
  //Use Clause ADT to store a collection of Literals representing unit clauses.
  Clause finalUnits = new_Clause();

  //Also temporarily store each newly discovered set of unit clauses.
  Clause unitsToPropagate = new_Clause();

  Clause newUnits;
  Clause unitsDiscovered = new_Clause();

  Clausemap clausemap = buildClauseMap(formula);

  Clausemap_print(clausemap);

  printf("nope.\n");
  /*
  Mapping currentMapping;
  Literal currentUnit;

  addUnits(formula, unitsToPropagate);

  printf("UP: ");
  Clause_print(unitsToPropagate);
  printf("\n");

  for(int i = 0; i < Clause_getLength(unitsToPropagate); i++) {
    if(Clause_findLiteral(finalUnits, Clause_getLiteral(unitsToPropagate, i)) == -1) {
      Clause_addLiteral(finalUnits, Clause_getLiteral(unitsToPropagate, i));
    }
  }
  //Clause_print(finalUnits);

  while(Clause_getLength(unitsToPropagate) != 0) {

    for(int i = 0; i < Clause_getLength(unitsToPropagate); i++) {

      currentUnit = Clause_getLiteral(unitsToPropagate, i);

      for(int j = 0; j < Clausemap_getLength(clausemap); j++) {
        currentMapping = Clausemap_getMapping(clausemap, j);
        if(Literal_equalsName(Mapping_getLiteral(currentMapping), currentUnit)) {

          newUnits = Mapping_modifyClauses(currentMapping);
          Clause_print(newUnits);
          for(int k = 0; k < Clause_getLength(newUnits); i++) {
            Clause_addLiteral(unitsDiscovered, Clause_getLiteral(newUnits, k));
          }
        }
      }
    }


    Clause_clear(unitsToPropagate);
    for(int i = 0; i < Clause_getLength(unitsDiscovered); i++) {
      if(Clause_findLiteral(finalUnits, Clause_getLiteral(unitsDiscovered, i)) == -1) {
        Clause_addLiteral(finalUnits, Clause_getLiteral(unitsDiscovered, i));
      }

      Clause_addLiteral(unitsToPropagate, Clause_getLiteral(unitsDiscovered, i));
    }

    Clause_clear(unitsDiscovered);
  }

  Clause_sortLiterals(finalUnits);
  Clause_free(unitsToPropagate);
  Clause_free(newUnits);
  Clause_free(unitsDiscovered);
  Formula_free(formula);*/

  return finalUnits;
}
