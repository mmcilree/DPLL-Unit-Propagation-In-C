#include "formula.h"
#include "clause.h"
#include "literal.h"

#include <stdlib.h>
#include <stdio.h>

//Propogate the truth value of a given literal through the whole formula.
static void propagate(Formula formula, Literal x) {
  Clause currentClause;
  int index, nindex; //Index of literal and its negation.
  Literal nx = Literal_negate(x);

  //printf(" do this %d times: \n", Formula_getLength(formula));

  //Iterate through the clauses of the formula
  for(int i = 0; i < Formula_getLength(formula); i++) {
    currentClause = Formula_getClause(formula, i);

    index = Clause_findLiteral(currentClause, x); //Find literal
    //printf("   found");
    nindex = Clause_findLiteral(currentClause, nx); //Find its negation

    if(index != -1) { //If the literal is in the clause, remove the whole clause.
      Formula_removeClause(formula, i);
      i--; //Backtrack by one so we don't accidentally skip a clause.
    } else if (nindex != -1) { //If the negation of the literal is in the clause, remove that literal.
      Clause_removeLiteral(currentClause, nindex);
    }

    if(Clause_getLength(currentClause) == 0) {
      //Contradiction
      printf("-\n");
      exit(0);
    }
  }

}


//Helper function to add all units in a formula to a clause.
void addUnits(Formula formula, Clause units) {
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
    }
  }
}


Clause getUnits(Formula formula) {
  //Use Clause ADT to store a collection of Literals representing unit Clauses.
  Clause units = new_Clause();

  Clause unitClause;
  Literal x;

  while(Formula_getLength(formula) != 0) {
    addUnits(formula, units);

    //Iterate through the formula to find a unit clause.
    for(int i = 0; i < Formula_getLength(formula); i++) {
      //Take a potential unit clause.
      unitClause = Formula_getClause(formula, i);

      if(Clause_getLength(unitClause) == 1) {
        //If it has length 1, we have found a unitClause and so can continue
        break;
      } else if(i == Formula_getLength(formula) - 1) {
        //If not, and there are no more units, there is no more propagation to be done.
        Clause_sortLiterals(units);
        return units;
      }

    }

    //Take the only literal in the unit clause and propagate it.
    x = Clause_getLiteral(unitClause, 0);
    //printf("loop #%d ", XXcount++);
    propagate(formula, x);

  }

  //Formula has been reduced to 0 clauses, so return.
  Clause_sortLiterals(units);
  return units;
}
