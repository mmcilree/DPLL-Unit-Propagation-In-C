/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Clause: This module provides an abstract data type (ADT), representing a        *
 *         clause as part of a formula in CNF: a collection (disjunction) of       *
 *         literals                                                                *
 * 180004835                                                                       *
 ***********************************************************************************/
#ifndef CLAUSE_H
#define CLAUSE_H

#include <stdbool.h>

#include "literal.h"

typedef struct Clause* Clause;

/***********************************************************************************
 * new_Clause: Constructor for the Clause ADT.                                     *
 ***********************************************************************************/
Clause new_Clause();

/***********************************************************************************
 * Clause_free: Destructor for the Clause ADT.                                     *
 ***********************************************************************************/
void Clause_free(Clause);

/***********************************************************************************
 * Clause_addLiteral: Append the given literal to the clause.                      *
 ***********************************************************************************/
void Clause_addLiteral(Clause this, Literal l);

/***********************************************************************************
 * Clause_removeLiteral: Remove the given literal from the clause.                 *
 ***********************************************************************************/
void Clause_removeLiteral(Clause this, int index);

/***********************************************************************************
 * Clause_getLength: Return the number of literals in the clause.                  *
 ***********************************************************************************/
int Clause_getLength(Clause);

/***********************************************************************************
 * Clause_getLiteral: Get the literal at the specified position within the clause. *
 ***********************************************************************************/
Literal Clause_getLiteral(Clause this, int index);

/***********************************************************************************
 * Clause_findLiteral: Return the index of the given literal, or -1 if it is not   *
 *                     present within the clause.                                  *
 ***********************************************************************************/
int Clause_findLiteral(Clause this, Literal l);

/***********************************************************************************
 * Clause_print: Print all of the literals in the clause on one line.              *
 ***********************************************************************************/
void Clause_print(Clause);

/***********************************************************************************
 * Clause_sortLiterals: Sort the literals in the clause in lexigraphical order.    *
 ***********************************************************************************/
void Clause_sortLiterals(Clause this);

/***********************************************************************************
 * Clause_makeNull: Signify that the clause has been made null by some part of the *
 *                  program and should be ignored                                  *
 ***********************************************************************************/
void Clause_makeNull(Clause this);

/***********************************************************************************
 * Clause_isNull: Check whether the clause has been made null.                     *
 ***********************************************************************************/
bool Clause_isNull(Clause this);

/***********************************************************************************
 * Clause_addAllDistinct: Add all the literals not already in the clause to the    *
 *                        clause.                                                  *
 ***********************************************************************************/
void Clause_addAllDistinct(Clause this, Clause other);
#endif
