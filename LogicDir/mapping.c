#include "mapping.h"
#include "formula.h"
#include "literal.h"
#include "clause.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Mapping {
  Literal literal;
  Formula clauses;
};

Mapping new_Mapping(Literal l) {
  Formula c = new_Formula();
  Mapping m = malloc(sizeof(struct Mapping));
  if(m == NULL) {
    perror("Error creating new mapping");
    exit(1);
  }

  m->literal = l;
  m->clauses = c;

  return m;
}

void Mapping_free(Mapping this) {
  free(this);
}

void Mapping_addClause(Mapping this, Clause c) {
  Formula_addClause(this->clauses, c);
}

bool Mapping_isForLiteral(Mapping this, Literal l) {
  return Literal_isEqual(this->literal, l);
}
