#ifndef LITERAL_H
#define LITERAL_H

#include <stdbool.h>

typedef struct Literal* Literal;

Literal new_Literal(char* name, bool truth);
void Literal_free(Literal this);
char* Literal_getName(Literal this);
bool Literal_isTrue(Literal this);

#endif
