/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Formula: This module provides an abstract data type (ADT), representing a       *
 *          formula in CNF, that is, a conjuction of clauses.                      *
 * 180004835                                                                       *
 ***********************************************************************************/
#ifndef FORMULA_H
#define FORMULA_H

#include "clause.h"

typedef struct Formula* Formula;

/***********************************************************************************
 * new_Formula: Constructor for the Formula ADT.                                   *
 ***********************************************************************************/
Formula new_Formula();

/***********************************************************************************
 * Formula_free: Destructor for the Formula ADT.                                   *
 ***********************************************************************************/
void Formula_free(Formula);

/***********************************************************************************
 * Formula_addClause: Appends the given clause to the formula.                     *
 ***********************************************************************************/
void Formula_addClause(Formula this, Clause c);

/***********************************************************************************
 * Formula_removeClause: Removes the given clause from the formula.                *
 ***********************************************************************************/
void Formula_removeClause(Formula this, int index);

/***********************************************************************************
 * Formula_getLength: Returns the number of clauses in the formula.                *
 ***********************************************************************************/
int Formula_getLength(Formula);

/***********************************************************************************
 * Formula_getClause: Return the clause at the given position in the formula.      *
 ***********************************************************************************/
Clause Formula_getClause(Formula this, int index);

/***********************************************************************************
 * Formula_print: Print each of the clauses in turn, along with number of literals *
 *                in each.                                                         *
 ***********************************************************************************/
void Formula_print(Formula);

#endif
