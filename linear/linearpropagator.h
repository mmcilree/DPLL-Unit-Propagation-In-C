/***********************************************************************************
 * CS2002 W07-C2 Practical:                                                        *
 * Linear Propagator: This module provides an implementation of the unit           *
 *                    propagation part of the DPLL algorithm that is closer to     *
 *                    running in linear time.                                      *
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

#endif
