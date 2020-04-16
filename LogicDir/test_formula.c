#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "literal.h"
#include "clause.h"
#include "formula.h"


static Formula testF;
static int successes = 0;


void setup() {
	testF = new_Formula();
}

void teardown() {
	Formula_free(testF);
	successes++;
}

void runTest(void (*testFunction)()) {
	setup();
	testFunction();
	teardown();
}

/**
 * createEmptyFormula: Checks that an empty formula has length 0.
 */
void createEmptyFormula() {
  assert(testF != NULL);
  assert(Formula_getLength(testF) == 0);
}

/**
 * getOutOfBounds: Checks that trying to get a clause with an out of bounds index
 *                 returns null.
 */
void getOutOfBounds() {
	Formula_addClause(testF, new_Clause());
	assert(Formula_getClause(testF, 1) == NULL);
	assert(Formula_getClause(testF, -1) == NULL);
}

/**
 * removeOutOfBounds: Checks that removing a clause with an out of bounds index
 *                    has no effect.
 */
void removeOutOfBounds() {
	Formula_addClause(testF, new_Clause());
	Formula_removeClause(testF, 1);
	Formula_removeClause(testF, -1);
	assert(Formula_getLength(testF) == 1);
}

/**
 * addOneClause: Checks that a single clause can be added to a formula.
 */
void addOneClause() {
  Clause c = new_Clause();
  Formula_addClause(testF, c);

  Clause a = Formula_getClause(testF, 0);

  assert(Clause_getLength(a) == 0);
  assert(Formula_getLength(testF) == 1);
}

/**
 * addTwoClauses: Checks that two different clauses can be added to a formula.
 */
void addTwoClauses() {
  Clause c1 = new_Clause();
  Clause c2 = new_Clause();

	Clause_addLiteral(c2, new_Literal("b", true));

  Formula_addClause(testF, c1);
  Formula_addClause(testF, c2);

  Clause a = Formula_getClause(testF, 0);
  Clause b = Formula_getClause(testF, 1);

  assert(Clause_getLength(a) == 0);
  assert(Clause_getLength(b) == 1);
  assert(Formula_getLength(testF) == 2);
}

/**
 * addTenClauses: Checks that a formula can be filled to its initial capacity.
 */
void addTenClauses() {
  for(int i = 0; i < 10; i++) {
    Formula_addClause(testF, new_Clause());
  }
  Clause a = Formula_getClause(testF, 0);


  assert(Clause_getLength(a) == 0);
  assert(Formula_getLength(testF) == 10);
}

/**
 * addElevenClauses: Checks that a formula's initial capcacity can be exceeded.
 */
void addElevenClauses() {
  for(int i = 0; i < 10; i++) {
    Formula_addClause(testF, new_Clause());
  }
	Clause c = new_Clause();
	Clause_addLiteral(c, new_Literal("b", true));

  Formula_addClause(testF, c);

  Clause a = Formula_getClause(testF, 0);
  Clause b = Formula_getClause(testF, 10);

	Literal b0 = Clause_getLiteral(b, 0);

  assert(Clause_getLength(a) == 0);
  assert(Clause_getLength(b) == 1);
	assert(strcmp(Literal_getName(b0), "b") == 0);
	assert(Literal_isTrue(b0) == true);

  assert(Formula_getLength(testF) == 11);
}

/**
 * addFiveThousandClauses: Checks that a very large number of clauses can be added
 *                         to the formula.
 */
void addFiveThousandClauses() {
  for(int i = 0; i < 2500; i++) {
    Formula_addClause(testF, new_Clause());
  }
	Clause c = new_Clause();
	Clause_addLiteral(c, new_Literal("b", true));
  Formula_addClause(testF, c);

  for(int i = 0; i < 2499; i++) {
    Formula_addClause(testF, new_Clause());
  }

  Clause a = Formula_getClause(testF, 0);
  Clause b = Formula_getClause(testF, 2500);

  assert(Clause_getLength(a) == 0);
	assert(Clause_getLength(b) == 1);
  assert(Formula_getLength(testF) == 5000);
}

/**
 * addAndRemoveClause: Checks that adding and removing a clause returns the
 *                     formula to its initial state.
 */
void addAndRemoveClause() {
	Clause c = new_Clause();
	Clause_addLiteral(c, new_Literal("b", true));
  Formula_addClause(testF, c);

	assert(Formula_getLength(testF) == 1);

	Formula_removeClause(testF, 0);

	assert(Formula_getLength(testF) == 0);
	assert(Formula_getClause(testF, 0) == NULL);
}

/**
 * addTwoAndRemoveOneClause: Checks that adding two clauses and removing one
 *                           leaves one remaining.                               
 */
void addTwoAndRemoveOneClause() {
	Clause c1 = new_Clause();
  Clause c2 = new_Clause();

	Clause_addLiteral(c2, new_Literal("b", true));

  Formula_addClause(testF, c1);
  Formula_addClause(testF, c2);

  assert(Formula_getLength(testF) == 2);

	Formula_removeClause(testF, 0);
	assert(Formula_getLength(testF) == 1);

	Clause n = Formula_getClause(testF, 1);
	Clause b = Formula_getClause(testF, 0);
	assert(Clause_getLength(b) == 1);
	assert(n == NULL);
}

int main(void) {
  runTest(createEmptyFormula);
	runTest(getOutOfBounds);
	runTest(removeOutOfBounds);
  runTest(addOneClause);
  runTest(addTwoClauses);
  runTest(addTenClauses);
  runTest(addElevenClauses);
  runTest(addFiveThousandClauses);
	runTest(addAndRemoveClause);
	runTest(addTwoAndRemoveOneClause);
	printf("All %d tests successful\n", successes);
}
