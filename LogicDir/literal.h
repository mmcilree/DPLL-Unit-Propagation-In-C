#ifndef LITERAL_H
#define LITERAL_H

#include <stdbool.h>

typedef struct Literal* Literal;

Literal new_Literal(char* name, bool truth);
Literal Literal_negate(Literal);
void Literal_free(Literal);
char* Literal_getName(Literal);
bool Literal_isTrue(Literal);
bool Literal_isEqual(Literal this, Literal other);
int Literal_compare(const void * p, const void * q);
void Literal_print(Literal);

#endif
