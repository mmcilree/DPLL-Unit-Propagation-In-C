#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "formula.h"
#include "clause.h"
#include "literal.h"
#include "parser.h"

#define INITIAL_LINE_LENGTH 100

static Clause parseLine(char* line) {
  bool truth;
  Literal l, nl;
  const char delim[2] = " "; //Literals are space separated.
  int literalIndex;

  Clause clause = new_Clause();

  //Get first token.
  char *token = strtok(line, delim);

   while(token != NULL ) {
      //Ignore '-' on its own.
      if(strcmp(token, "-") != 0) {
        truth = (token[0] != '-');
        if(truth != true) {
          ++token; //Discard first character if it is '-'.
        }

        if(strstr(token, "-") == NULL) { //Ignore token if it contains hyphens.
          l = new_Literal(token, truth);
          literalIndex = Clause_findLiteral(literalSet, l);

          //Find literal in the set, or add it if not already present.
          if(literalIndex != -1 ) {
            l = Clause_getLiteral(literalSet, literalIndex);
          } else {
            Clause_addLiteral(literalSet, l);
          }

          nl = Literal_negate(l);

          literalIndex = Clause_findLiteral(literalSet, nl);
          //Again for negation, find literal in the set, or add if not already present.
          if(literalIndex != -1 ) {
            nl = Clause_getLiteral(literalSet, literalIndex);
          } else {
            Clause_addLiteral(literalSet, nl);
          }

          //Create the mapping between this literal and this clause.
          Literal_associateNegation(l, nl);
          Literal_associateClause(l, clause);

          //Add the literal to the clause.
          Clause_addLiteral(clause, l);
        }
      }
      token = strtok(NULL, delim);
   }

   if(Clause_getLength(clause) == 0) {
     //Contradiction
     printf("-\n");
     exit(0);
   }

   return clause;
}

Formula buildFormula() {
  char c;
  char* line;
  Clause clause;
  int length = 0;
  int capacity = INITIAL_LINE_LENGTH;
  literalSet = new_Clause();

  //Allocate initial line buffer
  line = malloc(sizeof(char)*capacity + 1);

  if(line == NULL) {
    perror("Error parsing stdin");
    exit(1);
  }

  Formula formula = new_Formula();

  while((c = getchar()) != EOF) {
    //Grow line buffer is necessary
    if(length == capacity) {
      capacity *= 2;
      line = realloc(line, sizeof(char)*capacity + 1);
    }

    if(c == '\n') { //Have finished reading one line.
      line[length] = '\0';
      clause = parseLine(line);
      Formula_addClause(formula, clause);
      length = 0;
    } else { //Otherwise, continue reading line.
      line[length++] = c;
    }
  }

  free(line);
  return formula;
}
