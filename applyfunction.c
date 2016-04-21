#include <math.h>
#include <stdio.h>
#include "applyFunction.h"

int main() {
  int a[3];

  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  int* r = applyFunction(a, 3, nSquare);

  for (int i = 0; i < 3; ++i) {
    printf("ok: %d\n", r[i]);
  }
}
