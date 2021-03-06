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

typedef struct Clause* Clause; //Need to use forward declarations to avoid circular dependencies
typedef struct Formula* Formula;
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
 * Literal_equalsName: Returns true if the two Literals have the same name.        *                                                         *
 ***********************************************************************************/
bool Literal_equalsName(Literal this, Literal other);

/***********************************************************************************
 * Literal_compare: Comparator function for the qsort function: casts two void     *
 *                  pointers to pointers to the Literal type (itself a pointer to  *
 *                  the struct Literal), and compares on the lexicographical value *
 *                  of their names.                                                *
 ***********************************************************************************/
int Literal_compare(const void *, const void *);

/***********************************************************************************
 * Literal_associateClause: Add a clause to the literals clause list mapping.      *
 ***********************************************************************************/
void Literal_associateClause(Literal this, Clause clause);

/***********************************************************************************
 * Literal_getClauseList: Get all the clauses associated with this literal.        *
 ***********************************************************************************/
Formula Literal_getClauseList(Literal);

/***********************************************************************************
 * Literal_associateNegation: Set the reference to the literal's negation.         *
 ***********************************************************************************/
void Literal_associateNegation(Literal this, Literal negation);

/***********************************************************************************
 * Literal_associateNegation: Get the reference to the literal's negation.         *
 ***********************************************************************************/
Literal Literal_getNegation(Literal);

/***********************************************************************************
 * Literal_print: Prints the literal's name if true, or the literal's name         *
 *                preceded by a hyphen if false.                                   *
 ***********************************************************************************/
void Literal_print(Literal);

#endif
