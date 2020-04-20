#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    printf("Adding mapping (inside function).\n");
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
  bool found = false;
  printf("Associating clause...");
  Clause_print(clause);
  printf("\n");
  //For each literal in the clause
  for(int i = 0; i < Clause_getLength(clause); i++) {
    l = Clause_getLiteral(clause, i);
    printf("-Literal %d is ", i);
    Literal_print(l);
    printf("\n");

    //Try to find the mapping to add the clause to.
    for(int j = 0; j < this->length; j++) {
      if(Mapping_isForLiteral(this->mappings[j], l)) {
        if(Literal_isTrue(l)) {
          printf("-Found mapping already for ");
          Literal_print(l);
          printf("\n");
          Mapping_addPosClause(this->mappings[j], clause);
        } else {
          printf("-Found mapping already for ");
          Literal_print(l);
          printf("\n");
          Mapping_addNegClause(this->mappings[j], clause);
        }
        found = true;
        break;
      }
    }

    //If not found, create a new mapping.
    if(!found) {
      printf("-Making new mapping...\n");
      m = new_Mapping(l);
      addMapping(this, m);
      if(Literal_isTrue(l)) {
        Mapping_addPosClause(m, clause);
      } else {
        Mapping_addNegClause(m, clause);
      }
    } else {
      found = false;
    }
  }
}

Mapping Clausemap_getMapping(Clausemap this, int index) {
  return this->mappings[index];
}

int Clausemap_getLength(Clausemap this) {
  return this->length;
}

void Clausemap_print(Clausemap this) {
  printf("%d mappings: \n", this->length);
  for(int i = 0; i < this->length; i++) {
    Mapping_print(this->mappings[i]);
  }
}
