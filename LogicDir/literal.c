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

  this->name = strdup(name); //copy the string
  this->truth = truth;

  return this;
}

Literal Literal_negate(Literal this) {
  //Create new literal with opposite truth value.
  Literal neg = new_Literal(this->name, !this->truth);
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

bool Literal_equalsName(Literal this, Literal other) {
  return (strcmp(this->name, other->name) == 0);
}

int Literal_compare(const void * p, const void * q) {
   //Comparator for qsort must cast from void * type.
   char* l = Literal_getName(*(Literal*)p);
   char* r = Literal_getName(*(Literal*)q);
   return strcmp(l, r);
}

void Literal_print(Literal this) {
   printf("%s%s ", this->truth ? "" : "-", this->name);
 }
