#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

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

/**
 * createEmptyClause: Checks that an empty clause has length 0.
 */
void createEmptyClause() {
  assert(testC != NULL);
  assert(Clause_getLength(testC) == 0);
}

/**
 * addOneLiteral: Checks that a single literal can be added to a clause.
 */
void addOneLiteral() {
  Literal l = new_Literal("a", false);
  Clause_addLiteral(testC, l);

  Literal a = Clause_getLiteral(testC, 0);
  assert(strcmp(Literal_getName(a), "a") == 0);
  assert(Literal_isTrue(a) == false);

  assert(Clause_getLength(testC) == 1);
}

/**
 * getOutOfBounds: Checks that indexing out of the clause bounds returns null.
 */
void getOutOfBounds() {
	Literal l = new_Literal("a", false);
  Clause_addLiteral(testC, l);
  assert(Clause_getLength(testC) == 1);

	assert(Clause_getLiteral(testC, -1) == NULL);
	assert(Clause_getLiteral(testC, 2) == NULL);
}

void removeOutOfBounds() {
	Clause_addLiteral(testC, new_Literal("a", false));
	Clause_removeLiteral(testC, 1);
	Clause_removeLiteral(testC, -1);

	assert(Clause_getLength(testC) == 1);
}

/**
 * addTwoLiterals: Checks that two literals can be added to a clause.
 */
void addTwoLiterals() {
  Literal l1 = new_Literal("a", false);
  Literal l2 = new_Literal("b", true);

  Clause_addLiteral(testC, l1);
  Clause_addLiteral(testC, l2);

  Literal a = Clause_getLiteral(testC, 0);
  Literal b = Clause_getLiteral(testC, 1);

  assert(strcmp(Literal_getName(a), "a") == 0);
  assert(Literal_isTrue(a) == false);
  assert(strcmp(Literal_getName(b), "b") == 0);
  assert(Literal_isTrue(b) == true);

  assert(Clause_getLength(testC) == 2);
}

/**
 * addTenLiterals: Checks that a clause can be filled to initial capacity.
 */
void addTenLiterals() {
  for(int i = 0; i < 10; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }
  Literal a = Clause_getLiteral(testC, 0);


  assert(strcmp(Literal_getName(a), "a") == 0);
  assert(Literal_isTrue(a) == false);

  assert(Clause_getLength(testC) == 10);
}

/**
 * addElevenLiterals: Checks that a clause can be filled beyond its initial
 *                     capacity.
 */
void addElevenLiterals() {
  for(int i = 0; i < 10; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }
  Clause_addLiteral(testC, new_Literal("b", true));
  Literal a = Clause_getLiteral(testC, 0);
  Literal b = Clause_getLiteral(testC, 10);

  assert(strcmp(Literal_getName(a), "a") == 0);
  assert(Literal_isTrue(a) == false);
  assert(strcmp(Literal_getName(b), "b") == 0);
  assert(Literal_isTrue(b) == true);

  assert(Clause_getLength(testC) == 11);

}

/**
 * addFiveThousandLiterals: Checks that a very large number of literals can be
 *                          added to a clause.
 */
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

  assert(strcmp(Literal_getName(a), "a") == 0);
  assert(Literal_isTrue(a) == false);
  assert(strcmp(Literal_getName(b), "b") == 0);
  assert(Literal_isTrue(b) == true);

  assert(Clause_getLength(testC) == 5000);
}

/**
 * addTwoLiteralsAndRemoveOne: Checks that removing the first literal shifts the
 *                             second one back to position 0.
 */
void addTwoLiteralsAndRemoveOne() {
	Literal l1 = new_Literal("a", false);
	Literal l2 = new_Literal("b", true);

	Clause_addLiteral(testC, l1);
	Clause_addLiteral(testC, l2);
	Clause_removeLiteral(testC, 0);


	 Literal b = Clause_getLiteral(testC, 0);
	 assert(strcmp(Literal_getName(b), "b") == 0);
	 assert(Literal_isTrue(b) == true);

	 assert(Clause_getLength(testC) == 1);
}

/**
 * addTenLiteralsAndRemoveTwo: Checks that removing two literals results in two
 *                             shifts back.
 */
void addTenLiteralsAndRemoveTwo() {
	char num[2];

	num[0] = '0';
	num[1] = '\0';

	for(int i = 0; i < 10; i++) {
		Clause_addLiteral(testC, new_Literal(num, false));
		num[0]++;
	}

	Clause_removeLiteral(testC, 3);
	Clause_removeLiteral(testC, 7);

	Literal l3 = Clause_getLiteral(testC, 3);

	assert(strcmp(Literal_getName(l3), "4") == 0);

	Literal l7 = Clause_getLiteral(testC, 7);
	assert(strcmp(Literal_getName(l7), "9") == 0);
	assert(Clause_getLength(testC) == 8);
}

/**
 * findLiteralInMiddle: Search the list for a literal somewhere in the middle.
 */
void findLiteralInMiddle() {
	for(int i = 0; i < 5; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }

	Clause_addLiteral(testC, new_Literal("b", true));

	for(int i = 0; i < 5; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }

	Literal toFind = new_Literal("b", true);
	int index = Clause_findLiteral(testC, toFind);

	assert(index == 5);
}

/**
 * findLiteralAtStart: Find a literal in position 0.
 */
void findLiteralAtStart() {
	Clause_addLiteral(testC, new_Literal("b", true));
	for(int i = 0; i < 10; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }
	Literal toFind = new_Literal("b", true);
	int index = Clause_findLiteral(testC, toFind);

	assert(index == 0);
}

/**
 * findLiteralAtEnd: Find a literal in the end position.
 */
void findLiteralAtEnd() {
	for(int i = 0; i < 10; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }
	Clause_addLiteral(testC, new_Literal("b", true));

	Literal toFind = new_Literal("b", true);
	int index = Clause_findLiteral(testC, toFind);

	assert(index == 10);
}

/**
 * findMissing: Checks that a search for a literal that is not present in the
 *              clause yields -1.
 */
void findMissing() {
	for(int i = 0; i < 11; i++) {
    Clause_addLiteral(testC, new_Literal("a", false));
  }

	Literal toFind = new_Literal("b", true);
	int index = Clause_findLiteral(testC, toFind);

	assert(index == -1);
}

void checkSortLetters() {
	char* scramble = "jocknymphswaqfdrugvexblitz";
	char* alphabet = "abcdefghijklmnopqrstuvwxyz";
	char name[2];
	for(int i = 0; i < 26; i++) {
		name[0] = scramble[i];
		name[1] = '\0';
		Clause_addLiteral(testC, new_Literal(name, i%2));
	}

	Clause_sortLiterals(testC);

	for(int i = 0; i < 26; i++) {
		name[0] = alphabet[i];
		name[1] = '\0';
		assert(strcmp(Literal_getName(Clause_getLiteral(testC, i)), name) == 0);
	}
}

void checkSortNumbers() {
	char* scramble[9] = { "8", "1", "3", "9", "2", "7", "5", "6", "4"};
	char name[2];
	for(int i = 0; i < 9; i++) {
		Clause_addLiteral(testC, new_Literal(scramble[i], i%2));
	}

	Clause_sortLiterals(testC);

	for(int i = 0; i < 9; i++) {
		name[0] = ('1' + i);
		name[1] = '\0';

		assert(strcmp(Literal_getName(Clause_getLiteral(testC, i)), name) == 0);
	}
}

void checkSortLonger() {

	char* scramble[20] = {"OYNQ3GS5NKze2NQstIXU","0RwKyV7hB4AKj7A6Kc8k","5suVbKAvLdvoBi3N33ei","vdVpGikBLax7S8JguuhT","D18i48pqudPCHTWbACDp","UWzLgRK4pVZ6Wrfl6rqT","RF2O3iVy1EuhFeRb8X4y","ag2v2yjOQRKKTdOulWj7","J6OZ5NEwGKCv6Y8b8Tfg","x5LXxEy4ZGt6PWYE4m5i","OdcLoqp2sWZtZH7b3AbP","0Duko64Hiag0Ci3FPg8P","SfBflIOIvOFS70pHorFV","hcLWaYPvLxxH6cXEOIUg","mXd336oH0eeuCk6ae11s","4IP2GXr4VKJ2GJL829J0","mMTphICFfCd04GLach8U","jUJVdjC7ins58LKO4bHP","tHYutCdrrncNPx4gF87T","2fqD6rMixbnt2obJhlvu"};
	char* sorted[20] = {"0Duko64Hiag0Ci3FPg8P","0RwKyV7hB4AKj7A6Kc8k","2fqD6rMixbnt2obJhlvu","4IP2GXr4VKJ2GJL829J0","5suVbKAvLdvoBi3N33ei","D18i48pqudPCHTWbACDp","J6OZ5NEwGKCv6Y8b8Tfg","OYNQ3GS5NKze2NQstIXU","OdcLoqp2sWZtZH7b3AbP","RF2O3iVy1EuhFeRb8X4y","SfBflIOIvOFS70pHorFV","UWzLgRK4pVZ6Wrfl6rqT","ag2v2yjOQRKKTdOulWj7","hcLWaYPvLxxH6cXEOIUg","jUJVdjC7ins58LKO4bHP","mMTphICFfCd04GLach8U","mXd336oH0eeuCk6ae11s","tHYutCdrrncNPx4gF87T","vdVpGikBLax7S8JguuhT","x5LXxEy4ZGt6PWYE4m5i"};

	for(int i = 0; i < 20; i++) {
		Clause_addLiteral(testC, new_Literal(scramble[i], i%2));
	}

	Clause_sortLiterals(testC);

	for(int i = 0; i < 20; i++) {
		assert(strcmp(Literal_getName(Clause_getLiteral(testC, i)), sorted[i]) == 0);
	}
}

int main(void) {
  runTest(createEmptyClause);
  runTest(addOneLiteral);
	runTest(getOutOfBounds);
	runTest(removeOutOfBounds);
  runTest(addTwoLiterals);
  runTest(addTenLiterals);
  runTest(addElevenLiterals);
  runTest(addFiveThousandLiterals);
	runTest(addTwoLiteralsAndRemoveOne);
	runTest(addTenLiteralsAndRemoveTwo);
	runTest(findLiteralInMiddle);
	runTest(findLiteralAtStart);
	runTest(findLiteralAtEnd);
	runTest(findMissing);
	runTest(checkSortLetters);
	runTest(checkSortNumbers);
	runTest(checkSortLonger);
	printf("All %d tests successful\n", successes);
}
