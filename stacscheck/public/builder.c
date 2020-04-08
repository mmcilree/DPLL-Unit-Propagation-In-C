#include "stdio.h"

int main(void) {
  for(int i = 0; i < 1000; i++) {
    printf("%d -%d\n", i, (i+1));
  }
  printf("%d", 1000);
}
