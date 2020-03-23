#include <stdlib.h>
#include <stdio.h>

#include "literal.h"
#include "clause.h"

#define INITIAL_LENGTH 10

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
  this->literals = malloc(sizeof(Literal)*INITIAL_LENGTH);

  if(this->literals == NULL) {
    perror("Error creating new Clause");
    exit(1);
  }
  this->capacity = INITIAL_LENGTH;

  return this;
}

void Clause_free(Clause this) {
  for(int i = 0; i < this->length; i++) {
    Literal_free(this->literals[i]);
  }

  free(this->literals);
  free(this);
}

void Clause_addLiteral(Clause this, Literal l) {

  if(this->length < this->capacity) {
    this->literals[this->length++] = l;
  } else {
    this->capacity *= 2;
    this->literals = realloc(this->literals, sizeof(Literal)*this->capacity);

    if(this->literals == NULL) {
      perror("Error adding Literal to Clause");
      exit(1);
    }
    this->literals[this->length++] = l;
  }
}

void Clause_removeLiteral(Clause this, int index) {
  for(int i = index; i < this->length - 1; i++) {
    this->literals[i] = this->literals[i+1];
  }
  this->length--;
}

int Clause_getLength(Clause this) {
  return this->length;
}

Literal Clause_getLiteral(Clause this, int index) {
  if(index >= this->length) {
    return NULL;
  }

  return this->literals[index];
}

int Clause_findLiteral(Clause this, Literal l) {
  for(int i = 0; i < this->length; i++) {
    if(Literal_isEqual(l, this->literals[i])) {
      return i;
    }
  }

  return -1;
}

void Clause_print(Clause this) {
  Literal l;
  for(int i = 0; i < this->length; i++) {
    l = this->literals[i];
    Literal_print(l);
  }
  printf("\n");
}
