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

void createEmptyFormula() {
  assert(testF != NULL);
  assert(Formula_getLength(testF) == 0);
}

void addOneClause() {
  Clause c = new_Clause();
  Formula_addClause(testF, c);

  Clause a = Formula_getClause(testF, 0);

  assert(Clause_getLength(a) == 0);
  assert(Formula_getLength(testF) == 1);
}

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

void addTenClauses() {
  for(int i = 0; i < 10; i++) {
    Formula_addClause(testF, new_Clause());
  }
  Clause a = Formula_getClause(testF, 0);


  assert(Clause_getLength(a) == 0);
  assert(Formula_getLength(testF) == 10);
}

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

int main(void) {
  runTest(createEmptyFormula);
  runTest(addOneClause);
  runTest(addTwoClauses);
  runTest(addTenClauses);
  runTest(addElevenClauses);
  runTest(addFiveThousandClauses);
	printf("All %d tests successful\n", successes);
}
