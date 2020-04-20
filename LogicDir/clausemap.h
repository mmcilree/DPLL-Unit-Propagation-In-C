/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Clausemap: This module provides an abstract data type (ADT), representing a     *
 *            a list of mappings from a literal to a list of clauses. This allows  *
 *            for a more efficient linear propagation algorithm.                   *
 * 180004835                                                                       *
 ***********************************************************************************/
#ifndef CLAUSEMAP_H
#define CLAUSEMAP_H

#include "clause.h"
#include "mapping.h"

typedef struct Clausemap* Clausemap;

/***********************************************************************************
 * new_Clausemap: Constructor for the Clausemap ADT.                               *
 ***********************************************************************************/
Clausemap new_Clausemap();

/***********************************************************************************
 * Clausemap_free: Destructor for the Clausemap ADT.                               *
 ***********************************************************************************/
void Clausemap_free(Clausemap);

/************************************************************************************
 * Clausemap_associateClause: Add each clause to the mapping for each of its        *
 *                            literals                                              *
 ************************************************************************************/
void Clausemap_associateClause(Clausemap, Clause);

/***********************************************************************************
 * Clausemap_print: Display the clausemap (for debugging purposes).                *
 ***********************************************************************************/
void Clausemap_print(Clausemap);

Mapping Clausemap_getMapping(Clausemap, int index);

int Clausemap_getLength(Clausemap);

#endif
