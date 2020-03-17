#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "literal.h"
#include "clause.h"

static Clause testC;
static int successes = 0;


void setup() {
	testC = new_Clause();
}

void teardown() {
	Clause_free(testC);
	successes++;
}

void runTest(void (*testFunction)()) {
	setup();
	testFunction();
	teardown();
}

void createEmptyClause() {
  assert(testC != NULL);
  assert(Clause_getLength(testC) == 0);
}

void addOneLiteral() {
  Literal l = new_Literal("a", false);
  Clause_addLiteral(testC, l);

  Literal a = Clause_getLiteral(testC, 0);
  assert(Literal_getName(a) == "a");
  assert(Literal_isTrue(a) == false);


  assert(Clause_getLength(testC) == 1);
}

void addTwoLiterals() {
  Literal l1 = new_Literal("a", false);
  Literal l2 = new_Literal("b", true);

  Clause_addLiteral(testC, l1);
  Clause_addLiteral(testC, l2);

  Literal a = Clause_getLiteral(testC, 0);
  Literal b = Clause_getLiteral(testC, 1);

  assert(Literal_getName(a) == "a");
  assert(Literal_isTrue(a) == false);
  assert(Literal_getName(b) == "b");
  assert(Literal_isTrue(b) == true);

  assert(Clause_getLength(testC) == 2);
}

void addTenLiterals() {
  for(int i = 0; i < 10; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }
  Literal a = Clause_getLiteral(testC, 0);


  assert(Literal_getName(a) == "a");
  assert(Literal_isTrue(a) == false);

  assert(Clause_getLength(testC) == 10);
}

void addElevenLiterals() {
  for(int i = 0; i < 10; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }
  Clause_addLiteral(testC, new_Literal("b", true));
  Literal a = Clause_getLiteral(testC, 0);
  Literal b = Clause_getLiteral(testC, 10);

  assert(Literal_getName(a) == "a");
  assert(Literal_isTrue(a) == false);
  assert(Literal_getName(b) == "b");
  assert(Literal_isTrue(b) == true);

  assert(Clause_getLength(testC) == 11);

}

void addFiveThousandLiterals() {
  for(int i = 0; i < 2500; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }
  Clause_addLiteral(testC, new_Literal("b", true));

  for(int i = 0; i < 2499; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }

  Literal a = Clause_getLiteral(testC, 0);
  Literal b = Clause_getLiteral(testC, 2500);

  assert(Literal_getName(a) == "a");
  assert(Literal_isTrue(a) == false);
  assert(Literal_getName(b) == "b");
  assert(Literal_isTrue(b) == true);

  assert(Clause_getLength(testC) == 5000);
}

int main(void) {
  runTest(createEmptyClause);
  runTest(addOneLiteral);
  runTest(addTwoLiterals);
  runTest(addTenLiterals);
  runTest(addElevenLiterals);
  runTest(addFiveThousandLiterals);
	printf("All %d tests successful\n", successes);
}