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

void getName() {
  assert(strcmp(Literal_getName(testL), "a") == 0);
}

void getTruth() {
  assert(Literal_isTrue(testL) == false);
}

int main(void) {
	runTest(getName);
  runTest(getTruth);
	printf("All %d tests successful\n", successes);
}
