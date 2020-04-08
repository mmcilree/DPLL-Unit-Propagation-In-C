#include <stdlib.h>
#include <stdio.h>

#include "literal.h"
#include "clause.h"

#define INITIAL_CAPACITY 10

struct Clause {
  Literal* literals;
  int length;
  int capacity;
};

Clause new_Clause() {
  Clause this = malloc(sizeof(struct Clause));
  if(this == NULL) {
    perror("Error creating new Clause");
    exit(1);
  }
  this->length = 0;

  //Create an array to hold the literals.
  this->literals = malloc(sizeof(Literal)*INITIAL_CAPACITY);

  if(this->literals == NULL) {
    perror("Error creating new Clause");
    exit(1);
  }
  this->capacity = INITIAL_CAPACITY;

  return this;
}

void Clause_free(Clause this) {
  //First free all of the Literals in the array
  for(int i = 0; i < this->length; i++) {
    Literal_free(this->literals[i]);
  }

  //Then free the array itself.
  free(this->literals);

  //Finally, can free the structure.
  free(this);
}

void Clause_addLiteral(Clause this, Literal l) {
  if(this->length < this->capacity) { //Within capacity
    this->literals[this->length++] = l;
  } else { //If we are about to exceed capacity, double it.
    this->capacity *= 2;
    this->literals = realloc(this->literals, sizeof(Literal)*this->capacity);

    if(this->literals == NULL) {
      perror("Error adding Literal to Clause");
      exit(1);
    }
    this->literals[this->length++] = l; //Then we can add as normal.
  }
}

void Clause_removeLiteral(Clause this, int index) {
  //Shift all literals down a place.
  for(int i = index; i < this->length - 1; i++) {
    this->literals[i] = this->literals[i+1];
  }
  this->length--;
}

int Clause_getLength(Clause this) {
  return this->length;
}

Literal Clause_getLiteral(Clause this, int index) {
  if(index >= this->length || index < 0) {
    return NULL;
  }

  return this->literals[index];
}

int Clause_findLiteral(Clause this, Literal l) {
  //Perform a linear search of the array
  for(int i = 0; i < this->length; i++) {
    if(Literal_isEqual(l, this->literals[i])) {
      return i;
    }
  }

  return -1; //If not found.
}

void Clause_print(Clause this) {
  Literal l;
  for(int i = 0; i < this->length; i++) {
    l = this->literals[i];
    Literal_print(l);
  }
  printf("\n");
}

void Clause_sortLiterals(Clause this) {
  qsort((void*)this->literals, this->length, sizeof(this->literals[0]), Literal_compare);
}
