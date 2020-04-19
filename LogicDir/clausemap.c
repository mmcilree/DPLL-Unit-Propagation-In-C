#include <stdlib.h>
#include <stdio.h>

#include "clausemap.h"
#include "formula.h"
#include "clause.h"
#include "literal.h"
#include "mapping.h"

#define INITIAL_CAPACITY 10

struct Clausemap {
  Mapping* mappings;
  int length;
  int capacity;
};

static void addMapping(Clausemap this, Mapping m) {
  if(this->length < this->capacity) { //Within capacity.
    this->mappings[this->length++] = m;
  } else {
    //If we are about to exceed capacity, double it.
    this->capacity *= 2;
    this->mappings = realloc(this->mappings, sizeof(Mapping)*this->capacity);

    if(this->mappings == NULL) {
      perror("Error adding mapping to Clausemap");
      exit(1);
    }
    this->mappings[this->length++] = m; //Then we can add as normal.
  }
}

Clausemap new_Clausemap() {
  Clausemap this = malloc(sizeof(struct Clausemap));
  if(this == NULL) {
    perror("Error creating new Clausemap");
    exit(1);
  }
  this->length = 0;

  //Create an array to hold the mappings.
  this->mappings = malloc(sizeof(Mapping)*INITIAL_CAPACITY);

  if(this->mappings == NULL) {
    perror("Error creating new Clausemap");
    exit(1);
  }
  this->capacity = INITIAL_CAPACITY;

  return this;
}

void Clausemap_free(Clausemap this) {
  //First free all of the mappings in the array.
  for(int i = 0; i < this->length; i++) {
    Mapping_free(this->mappings[i]);
  }

  //Then free the array itself.
  free(this->mappings);

  //Finally, can free the structure.
  free(this);
}

void Clausemap_associateClause(Clausemap this, Clause clause) {
  Literal l;
  Mapping m;

  //For each literal in the clause
  for(int i = 0; i < Clause_getLength(clause); i++) {
    l = Clause_getLiteral(clause, i);

    //Find the mapping to add the clause to.
    for(int j = 0; j < this->length; j++) {
      if(Mapping_isForLiteral(this->mappings[j], l)) {
        Mapping_addClause(this->mappings[j], clause);
        break;
      }

      //If we reach the end and have not found the literal
      //we need a new mapping.
      if(j == this->length - 1) {
        m = new_Mapping(l);
        addMapping(this, m);
        Mapping_addClause(m, clause);
      }
    }
  }
}
