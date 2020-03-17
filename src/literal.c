#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "literal.h"

struct Literal {
  char* name;
  bool truth;
};

Literal new_Literal(char* name, bool truth) {
  Literal this = malloc(sizeof(struct Literal));
	if(this == NULL) {
		perror("Error creating new Literal");
		exit(1);
	}

  this->name = name;
  this->truth = truth;

  return this;
}

void Literal_free(Literal this) {
  free(this);
}
char* Literal_getName(Literal this) {
  return this->name;
}

bool Literal_isTrue(Literal this) {
  return this->truth;
}
