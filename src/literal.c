#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

  this->name = strdup(name);
  this->truth = truth;

  return this;
}

Literal Literal_negate(Literal this) {
  Literal neg = malloc(sizeof(struct Literal));
	if(this == NULL) {
		perror("Error creating new Literal");
		exit(1);
	}

  neg->name = strdup(this->name);
  neg->truth = !this->truth;

  return neg;
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

bool Literal_isEqual(Literal this, Literal other) {
  return (strcmp(this->name, other->name) == 0) && (this->truth == other->truth);
}

void Literal_print(Literal this) {
   printf("%s%s ", this->truth ? "" : "-", this->name);
 }
