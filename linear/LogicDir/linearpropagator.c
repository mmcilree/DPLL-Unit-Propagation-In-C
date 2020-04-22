#include <stdlib.h>
#include <stdio.h>

#include "formula.h"
#include "clause.h"
#include "literal.h"

//Propogate the truth value of a given literal through the whole formula.
static void propagate(Literal x, Clause newUnits) {
    Formula clausesToEliminate = Literal_getClauseList(x);
    Formula clausesToModify = Literal_getClauseList(Literal_getNegation(x));
    Clause c;
    int index;

    //Remove Clauses containing the literal
    for(int i = 0; i < Formula_getLength(clausesToEliminate); i++) {
      c = Formula_getClause(clausesToEliminate, i);
      if(c == NULL || Clause_isNull(c)) continue;
      Clause_makeNull(c);
    }

    //Remove negation of literal from clauses containing the negation
    for(int i = 0; i < Formula_getLength(clausesToModify); i++) {
      c = Formula_getClause(clausesToModify, i);
      if(c == NULL || Clause_isNull(c)) continue;

      index = Clause_findLiteral(c, Literal_negate(x));
      Clause_removeLiteral(c, index);

      if(Clause_getLength(c) == 1) {
        //Length 1 means we have a new new unit
        Clause_addLiteral(newUnits, Clause_getLiteral(c, 0));
      } else if(Clause_getLength(c) == 0) {
        //Length 0 is a contradiction
        printf("-\n");
        exit(0);
      }
    }
}

//Helper function to add all units in a formula to a clause.
static void addUnits(Formula formula, Clause units) {
  Clause current;
  Literal u;

  //Search the formula for units.
  for(int i = 0; i < Formula_getLength(formula); i++) {
    current = Formula_getClause(formula, i);
    if(Clause_getLength(current) == 1) {
      u = Clause_getLiteral(current, 0);

      //Do not add if unit is already present in clause.
      if(Clause_findLiteral(units, u) == -1) {
        Clause_addLiteral(units, u);
      }
    } else if(Clause_getLength(current) == 0) {
      //Contradiction
      printf("-\n");
      exit(0);
    }
  }
}

Clause getUnits(Formula formula) {
  //Use Clause ADT to store a collection of Literals representing unit Clauses.
  Clause units = new_Clause();

  Clause tempUnits = new_Clause(); //'Queue' of units still to be propagated

  Clause newUnits = new_Clause(); // Units obtained from propagation.

  addUnits(formula, tempUnits); // Initialise queue with units already present.

  Literal x;

  while(Clause_getLength(tempUnits) != 0) {

    for(int i = 0; i < Clause_getLength(tempUnits); i++) {
      x = Clause_getLiteral(tempUnits, i);
      propagate(x, newUnits);
    }
    Clause_addAllDistinct(units, tempUnits);
    tempUnits = newUnits;
    newUnits = new_Clause();
  }

  Clause_sortLiterals(units);
  return units;
}
