/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Literal: This module provides an abstract data type (ADT), representing a       *
 *          logical literal, that is, an indentifier and associated truth value.   *
 * 180004835                                                                       *
 ***********************************************************************************/
#ifndef LITERAL_H
#define LITERAL_H

#include <stdbool.h>

typedef struct Literal* Literal;

/***********************************************************************************
 * new_Literal: Constructor for the Literal ADT.                                   *
 ***********************************************************************************/
Literal new_Literal(char* name, bool truth);

/***********************************************************************************
 * Literal_free: Destructor for the Literal ADT.                                   *
 ***********************************************************************************/
void Literal_free(Literal);

/***********************************************************************************
 * Literal_negate: Negates the truth value of the literal.                         *
 ***********************************************************************************/
Literal Literal_negate(Literal);

/***********************************************************************************
 * Literal_getName: Getter for the literal's name.                                 *
 ***********************************************************************************/
char* Literal_getName(Literal);

/***********************************************************************************
 * Literal_isTrue: Getter for the literal's truth value                            *
 ***********************************************************************************/
bool Literal_isTrue(Literal);

/***********************************************************************************
 * Literal_isEqual: Returns true if the two Literals have the same name and truth  *
 *                  value                                                          *
 ***********************************************************************************/
bool Literal_isEqual(Literal this, Literal other);

/***********************************************************************************
 * Literal_compare: Comparator function for the qsort function: casts two void     *
 *                  pointers to pointers to the Literal type (itself a pointer to  *
 *                  the a struct Literal), and compares on the lexigraphical value *
 *                  of their names.                                                *
 ***********************************************************************************/
int Literal_compare(const void *, const void *);

/***********************************************************************************
 * Literal_print: Prints the literal's name if true, or the literal's name         *
 *                preceded by a hyphen if false.                                   *
 ***********************************************************************************/
void Literal_print(Literal);

#endif
