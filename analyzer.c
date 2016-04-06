#include "Parser/cmdline.h"
#include "SafeExec/safeexec.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* concat(char* s1, char* s2) {
  char* result =
      (char*)malloc(strlen(s1) + strlen(s2) + 1);  //+1 for the zero-terminator
  // in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

int main(int argc, char* argv[], char* envp[]) {
  //-----------ARG PARSING STUF-----------START//


    for (int i = 0; i < argc; ++i)
    {
        printf("%s\n",argv[i]);
    }



  struct gengetopt_args_info ai;
  if (cmdline_parser(argc, argv, &ai) != 0) {
    exit(1);
  }

  printf("ai.filename_arg: %s\n", ai.filename_arg);
  printf("ai.verbose_flag: %d\n", ai.verbose_flag);
  printf("ai.id_arg: %d\n", ai.id_arg);
  int i;
  for (i = 0; i < ai.value_given; ++i) {
    printf("ai.value_arg[%d]: %d\n", i, ai.value_arg[i]);
  }
  //-----------ARG PARSING STUF-----------END//

  //-----------FILE READING STUF----------START//

  char* filename = ai.filename_arg;
  // open the file for reading
  FILE* file = fopen(filename, "r");
  // make sure the file opened properly
  if (NULL == file) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return 1;
  }

  //-----------FILE READING STUF----------END//

  printf("-------------------\n");

  char* aaaa = (char*)"bla bla bla ";
  char* bbbb = (char*)"not bla";

  char* trololol = concat(aaaa, bbbb);

  printf("%s\n", trololol);

  printf("-------------------\n");

  char x[1024];
  /* assumes no word exceeds length of 1023 */
  while (fscanf(file, " %1023s", x) == 1) {
    printf("ESTOU NO WHILE\n");
    puts(x);
    int n = atoi(x);

    printf("antes    %s\n", x);

    printf("Number of args %d\n", n);

    printf("depois    %s\n", x);

    char x[1024]; /* assumes no word exceeds length of 1023 */
    char y[1024];
    while (fscanf(file, " %1023s", x) == 1 && fscanf(file, " %1023s", y)) {
      puts(x);
      puts(y);

      char* _argv_[3];
      int _argc_ = 2;
      char* exec_string = (char*)"--exec";

      // char* arg_for_safeexec_mofo = concat(exec_string, y);
      // _argv_[1] = arg_for_safeexec_mofo;

      char* arg_for_safeexec1 = exec_string;
      char* arg_for_safeexec2 = y;

      _argv_[1] = arg_for_safeexec1;
      _argv_[2] = arg_for_safeexec2;

      printf("\nSTART--------\n");

    for (int i = 1; i <= _argc_; ++i)
    {
        printf("arg %d: %s\n",i,_argv_[i]);
    }

    printf("---manda para o safeexec---\n\n");

      RESULTS res;
      res = safeexec(_argc_, _argv_, envp);

      if (res != NULL) {
        printf("-----\n\n");
        printf("%d\n", res->mem);
        printf("%d\n", res->timer);

        printf("END--------\n");
      } else {
        printf("OOOOPS--------\n");
        return 1;
      }
    }
  }
  return 0;
}
