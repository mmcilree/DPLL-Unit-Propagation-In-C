/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Propagator: This module provides an implementation of the unit propagation part *
 *             of the DPLL algorithm. It first builds a mapping structure that     *
 *             allows it to subsequently run in linear time.                       *                                                                   *
 * 180004835                                                                       *
 ***********************************************************************************/
#ifndef LINEARPROPAGATOR_H
#define LINEARPROPAGATOR_H

#include "formula.h"
#include "clause.h"

/************************************************************************************
 * getUnits: Return all the units that can be obtained by unit propogation,         *
 *           grouped in one clause for convenience.                                 *
 ************************************************************************************/
Clause getUnitsLinear(Formula formula);

#endif
