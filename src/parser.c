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
  const char delim[2] = " ";

  Clause clause = new_Clause();

  char *token = strtok(line, delim);

   while(token != NULL ) {

      if(strcmp(token, "-") != 0) {
        truth = (token[0] != '-');
        if(truth != true) {
          ++token;
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

  line = malloc(sizeof(char)*capacity + 1);

  if(line == NULL) {
    perror("Error parsing stdin");
    exit(1);
  }

  Formula formula = new_Formula();

  while((c = getchar()) != EOF) {
    if(length == capacity) {
      capacity *= 2;
      line = realloc(line, sizeof(char)*capacity + 1);
    }

    if(c == '\n') {
      line[length] = '\0';
      clause = parseLine(line);
      Formula_addClause(formula, clause);
      length = 0;
    } else {
      line[length++] = c;
    }
  }

  free(line);
  return formula;
}
