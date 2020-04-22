#include <stdlib.h>
#include <stdio.h>

#include "clause.h"
#include "formula.h"

#define INITIAL_CAPACITY 10

struct Formula {
  Clause* clauses;
  int length;
  int capacity;
};

Formula new_Formula() {
  Formula this = malloc(sizeof(struct Formula));
  if(this == NULL) {
    perror("Error creating new Formula");
    exit(1);
  }
  this->length = 0;

  //Create an array to hold the Clauses.
  this->clauses = malloc(sizeof(Clause)*INITIAL_CAPACITY);

  if(this->clauses == NULL) {
    perror("Error creating new Formula");
    exit(1);
  }
  this->capacity = INITIAL_CAPACITY;

  return this;
}

void Formula_free(Formula this) {
  //First free all of the Clauses in the array.
  for(int i = 0; i < this->length; i++) {
    Clause_free(this->clauses[i]);
  }

  //Then free the array itself.
  free(this->clauses);
  this->clauses = NULL;

  //Finally, can free the structure.
  free(this);
  this = NULL;
}

void Formula_addClause(Formula this, Clause c) {
  if(this->length < this->capacity) { //Within capacity.
    this->clauses[this->length++] = c;
  } else {
    //If we are about to exceed capacity, double it.
    this->capacity *= 2;
    this->clauses = realloc(this->clauses, sizeof(Clause)*this->capacity);

    if(this->clauses == NULL) {
      perror("Error adding Clause to Formula");
      exit(1);
    }
    this->clauses[this->length++] = c; //Then we can add as normal.
  }
}

void Formula_removeClause(Formula this, int index) {
  if(index >= this->length || index < 0) {
    return; //Can't remove out of bounds.
  }

  //Shift all clauses down a place.
  for(int i = index; i < this->length - 1; i++) {
    this->clauses[i] = this->clauses[i+1];
  }
  this->length--;
}

int Formula_getLength(Formula this) {
  return this->length;
}

Clause Formula_getClause(Formula this, int index) {
  if(index >= this->length || index < 0) {
    return NULL; //Return null if out of bounds.
  }

  return this->clauses[index];
}

void Formula_print(Formula this) {
  //For debugging purposes.
  Clause c;
  for(int i = 0; i < this->length; i++) {
    c = this->clauses[i];
    printf("Clause %d has %d literals: ", i, Clause_getLength(c));
    Clause_print(c);
  }
  printf("--------------\n");
}
