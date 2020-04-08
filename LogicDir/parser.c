#include "formula.h"
#include "clause.h"
#include "literal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_LINE_LENGTH 100

static Clause parseLine(char* line) {
  bool truth;
  Literal l;
  const char delim[2] = " "; //Literals are space separated.

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
        l = new_Literal(token, truth);
        Clause_addLiteral(clause, l);
      }
      token = strtok(NULL, delim);
   }

   return clause;
}

Formula buildFormula() {
  char c;
  char* line;
  Clause clause;
  int length = 0;
  int capacity = INITIAL_LINE_LENGTH;

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
