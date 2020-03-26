#include <stdlib.h>
#include <stdio.h>

#include "clause.h"
#include "formula.h"

#define INITIAL_LENGTH 10

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
  this->clauses = malloc(sizeof(Clause)*INITIAL_LENGTH);

  if(this->clauses == NULL) {
    perror("Error creating new Formula");
    exit(1);
  }
  this->capacity = INITIAL_LENGTH;

  return this;
}

void Formula_free(Formula this) {
  for(int i = 0; i < this->length; i++) {
    Clause_free(this->clauses[i]);
  }

  free(this->clauses);
  free(this);
}

void Formula_addClause(Formula this, Clause c) {
  if(this->length < this->capacity) {
    this->clauses[this->length++] = c;
  } else {
    this->capacity *= 2;
    this->clauses = realloc(this->clauses, sizeof(Clause)*this->capacity);

    if(this->clauses == NULL) {
      perror("Error adding Clause to Formula");
      exit(1);
    }
    this->clauses[this->length++] = c;
  }
}

void Formula_removeClause(Formula this, int index) {
  for(int i = index; i < this->length - 1; i++) {
    this->clauses[i] = this->clauses[i+1];
  }
  this->length--;
}

int Formula_getLength(Formula this) {
  return this->length;
}

Clause Formula_getClause(Formula this, int index) {
  if(index >= this->length) {
    return NULL;
  }

  return this->clauses[index];
}

void Formula_print(Formula this) {
  Clause c;
  for(int i = 0; i < this->length; i++) {
    c = this->clauses[i];
    printf("Clause %d has %d literals: ", i, Clause_getLength(c));
    Clause_print(c);
  }
  printf("--------------\n");
}
