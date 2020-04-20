/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Propagator: This module provides an implementation of the unit propagation part *
 *             of the DPLL algorithm.                                              *                                                                   *
 * 180004835                                                                       *
 ***********************************************************************************/
#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include "formula.h"
#include "literal.h"

/************************************************************************************
 * getUnits: Return all the units that can be obtained by unit propogation,         *
 *           grouped in one clause for convenience.                                 *
 ************************************************************************************/
Clause getUnits(Formula formula);

/***********************************************************************************
 * addUnits: Helper function to add all units in a formula to a clause.            *
 ***********************************************************************************/
void addUnits(Formula formula, Clause units);

#endif
