#include "mapping.h"
#include "formula.h"
#include "literal.h"
#include "clause.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Mapping {
  Literal literal;
  Formula posClauses;
  Formula negClauses;
};

Mapping new_Mapping(Literal l) {
  Formula pc = new_Formula();
  Formula nc = new_Formula();
  Mapping m = malloc(sizeof(struct Mapping));
  if(m == NULL) {
    perror("Error creating new mapping");
    exit(1);
  }

  //Store the true version of the literal by default.
  //if(Literal_isTrue(l)) {
    m->literal = l;
  //} else {
  //  m->literal = Literal_negate(l);
  //}

  m->posClauses = pc;
  m->negClauses = nc;

  return m;
}

void Mapping_free(Mapping this) {
  free(this);
}

void Mapping_addPosClause(Mapping this, Clause c) {
  printf("---ADD CLAUSE to pos:");
  Clause_print(c);
  printf("\n");
  Formula_addClause(this->posClauses, c);
}

void Mapping_addNegClause(Mapping this, Clause c) {
  printf("---ADD CLAUSE to neg:");
  Clause_print(c);
  printf("\n");
  Formula_addClause(this->negClauses, c);
}

bool Mapping_isForLiteral(Mapping this, Literal l) {
  printf("--(checking literal mapping)\n");
  return Literal_equalsName(this->literal, l);
}

Literal Mapping_getLiteral(Mapping this) {
  return this->literal;
}

int Mapping_getPosLength(Mapping this) {
  return Formula_getLength(this->posClauses);
}

int Mapping_getNegLength(Mapping this) {
  return Formula_getLength(this->negClauses);
}

Clause Mapping_modifyClauses(Mapping this) {
  printf("Modifying clauses...\n");
  Clause units = new_Clause();
  Clause c;
  int index;

  printf("%d clause with pos literal\n", Formula_getLength(this->posClauses));
  for(int i = 0; i < Formula_getLength(this->posClauses); i++) {

    if (c == NULL) continue;
    c = Formula_getClause(this->posClauses, i);
    printf("--Nulling clause: ");
    Clause_print(c);
    printf("\n");
    Clause_makeNull(c);
  }

  printf("%d clause with neg literal\n", Formula_getLength(this->negClauses));
  for(int i = 0; i < Formula_getLength(this->negClauses); i++) {
    c = Formula_getClause(this->negClauses, i);
    Clause_print(c);
    if (c == NULL) continue;
    printf("--Removing from clause: ");
    Clause_print(c);
    printf("\n");



    index = Clause_findLiteral(c, Literal_negate(this->literal));
    printf("Found literal at index: %d\n", index);
    Clause_removeLiteral(c, index);
    if(Clause_getLength(c) == 1) {
      Clause_addLiteral(units, Clause_getLiteral(c, 0));
    }
  }

  return units;
}

void Mapping_print(Mapping this) {
  if(this == NULL) {
    printf("WE'VE GOT A NULL POINTER.\n");
  }
  Literal_print(this->literal);
  printf(": ");
  for(int i = 0; i < Formula_getLength(this->posClauses); i++) {
    printf("(");
    Clause_print(Formula_getClause(this->posClauses, i));
    printf(") ");
  }
  printf("\n");
  Literal_print(Literal_negate(this->literal));
  printf(": ");
  for(int i = 0; i < Formula_getLength(this->negClauses); i++) {
    printf("(");
    Clause_print(Formula_getClause(this->negClauses, i));
    printf(") ");
  }
  printf("\n\n");
}
