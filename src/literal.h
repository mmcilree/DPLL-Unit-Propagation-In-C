#ifndef LITERAL_H
#define LITERAL_H

#include <stdbool.h>

typedef struct Literal* Literal;

Literal new_Literal(char* name, bool truth);
void Literal_free(Literal);
char* Literal_getName(Literal);
bool Literal_isTrue(Literal);
bool Literal_compare(Literal this, Literal other);
void Literal_print(Literal);

#endif
