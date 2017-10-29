#include <stdio.h>
#include "safeexec.h"

int main(int argc, char* argv[], char* envp[]) {

  printf("Arg number: %d\n", argc);

  for (int i = 0; i < argc; i++) {
    printf("|%d|%s|\n", i, argv[i]);
  }

  RESULTS res = safeexec(argc, argv, envp);
  if (res != NULL ) {printf("%d", res->mem);}
  else {printf("Res is null\n");}
  return 0;
}
