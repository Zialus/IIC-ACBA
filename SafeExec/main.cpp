#include <stdio.h>
#include "safeexec.h"
#include <sys/resource.h>

int main(int argc, char* argv[], char* envp[]) {

  RESULTS res;
  /*
  printf("%d\n", argc);
  int i;
  for (i = 0; i < argc; ++i) {
    printf("%d|%s|\n", i, argv[i]);
  }
  */

  res = safeexec(argc, argv, envp);
  printf("%d", res->mem);
  return 0;
}