#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "literal.h"

static Literal testL;
static int successes = 0;


void setup() {
	testL = new_Literal("a", false);
}

void teardown() {
	Literal_free(testL);
	successes++;
}

void runTest(void (*testFunction)()) {
	setup();
	testFunction();
	teardown();
}

/**
 * getName: Check that the correct identifier is obtained from the literal.
 */
void getName() {
  assert(strcmp(Literal_getName(testL), "a") == 0);
}

void longName() {
	Literal otherL = new_Literal("thisisaverylongstringandaverylongnameforaliteralbutitshouldstillbevaliddespitehowmanycharactersitcontainswithinitselfthatistosayaverygreatnumberofcharactersthataremorethanyouwouldnormallyexpectforaunitbutneverthelessitisimportantnottomakeanyassumptionsaboutthelengthsothisshouldstilltechnicallybefine",
	true);
	assert(strcmp(Literal_getName(otherL), "thisisaverylongstringandaverylongnameforaliteralbutitshouldstillbevaliddespitehowmanycharactersitcontainswithinitselfthatistosayaverygreatnumberofcharactersthataremorethanyouwouldnormallyexpectforaunitbutneverthelessitisimportantnottomakeanyassumptionsaboutthelengthsothisshouldstilltechnicallybefine")
	== 0);
}

/**
 * checkNameCopy: Ensure that the name stored in the literal is a copy of the
 *                passed and is unaffected by changes to the original.
 */
void checkNameCopy() {
	char* string = "astring";
	Literal otherL = new_Literal(string, false);

	string = "adifferentstring";

	assert(strcmp(Literal_getName(otherL), "astring") == 0);
}

/**
 * getTruth: Check that the corrent truth value is obtained from the literal.
 */
void getTruth() {
  assert(Literal_isTrue(testL) == false);
}

/**
 * checkNegate: Check that a literal can be properly negated.
 */
void checkNegate() {
	Literal ntestL = Literal_negate(testL);
	assert(strcmp(Literal_getName(ntestL), "a") == 0);
	assert(Literal_isTrue(ntestL) == true);
}

/**
 * checkEqual: Check that two literals with the same attributes are considered
 *             to be equal.
 */
void checkEqual() {
	Literal otherL = new_Literal("a", false);
	assert(testL != otherL);
	assert(Literal_isEqual(testL, otherL));
	assert(Literal_isEqual(otherL, testL));
}

/**
 * checkNotEqual: Check that two literals with the same name but different
 *                attributes are not considered to be equal.
 */
void checkNotEqual() {
	Literal otherL = new_Literal("a", true);
	assert(testL != otherL);
	assert(!Literal_isEqual(testL, otherL));
	assert(!Literal_isEqual(otherL, testL));
}

/**
 * checkCompare: Check that the qsort comparator function compares on the name
 *               only.
 */
void checkCompare() {
	Literal otherL = new_Literal("b", false);
	assert(Literal_compare((void *)&otherL, (void *)&testL) == 1);
}

int main(void) {
	runTest(getName);
	runTest(longName);
	runTest(checkNameCopy);
  runTest(getTruth);
	runTest(checkNegate);
	runTest(checkEqual);
	runTest(checkNotEqual);
	runTest(checkCompare);
	printf("All %d tests successful\n", successes);
}
