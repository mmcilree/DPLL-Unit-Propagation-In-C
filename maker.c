#include <stdio.h>

int main() {
  char c;
  char token[20];
  int length = 0;
  while((c = getchar()) != EOF) {
    if(c == '\n') {
      token[length] = '\0';
      printf("-%s\n%s ", token, token);
      length = 0;
    } else {
      token[length++] = c;
    }
  }
}
