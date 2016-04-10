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
  int i;
  //-----------ARG PARSING STUF-----------START//

  // printf("+++++++++++++++++++\n");
  // printf("++++++-------++++++\n");

  // printf("Argc: %d\n", argc);
  // printf("\n");

  // for (int i = 0; i <= argc; ++i) {
  //   printf("Argv[%d]: %s\n", i, argv[i]);
  // }

  // printf("\n");

  struct gengetopt_args_info ai;
  if (cmdline_parser(argc, argv, &ai) != 0) {
    exit(1);
  }

  // printf("ai.filein_arg: %s\n", ai.filein_arg);
  // printf("ai.verbose_flag: %d\n", ai.verbose_flag);
  // printf("ai.number_orig: %d\n", ai.number_arg);
  // for (i = 0; i < (int)ai.value_given; ++i) {
  //   printf("ai.value_arg[%d]: %d\n", i, ai.value_arg[i]);
  // }

  // printf("+++++++------++++++\n");
  // printf("+++++++++++++++++++\n");

  int numero = ai.number_arg;

  //-----------ARG PARSING STUF-----------END//

  //-----------FILE READING STUF----------START//
  char* filein = ai.filein_arg;
  char* fileout = ai.fileout_arg;
  // open the file for reading
  FILE* file = fopen(filein, "r");
  // make sure the file opened properly
  if (NULL == file) {
    fprintf(stderr, "Cannot open file: %s\n", filein);
    return 1;
  }
  //-----------FILE READING STUF----------END//

  // printf("-------------------\n");
  // char* aaaa = (char*)"bla bla bla ";
  // char* bbbb = (char*)"not bla";
  // char* trololol = concat(aaaa, bbbb);
  // printf("%s\n", trololol);
  // printf("-------------------\n");

  // char x[1024];  // assumes no word exceeds length of 1023
  // while (fscanf(file, " %1023s", x) == 1) {
  //   printf("Reading file...%s\n",filein);
  //   int n = atoi(x);

  //   printf("Suposto numero de argumentos: %d\n", n);

  //   char x[1024];  // assumes no word exceeds length of 1023
  //   char y[1024];

  //   while (fscanf(file, " %1023s", x) == 1 && fscanf(file, " %1023s", y)) {

  //     printf("|%s|%s|\n", x, y);

  //     RESULTS res = safeexec(_argc_, _argv_, envp);

  //     if (res != NULL) {
  //       printf("---Inicio da Info:---\n");
  //       printf("Quantidade de memoria: %d\n", res->mem);
  //       printf("Quantidade de tempo: %d\n", res->timer);
  //       printf("---Fim da Info:---\n");
  //     } else {
  //       printf("OOOOPS-----\n");
  //       return 1;
  //     }

  //    printf("---fim do while---\n");
  //   }
  // }

  printf("Getting ready for safeexec\n");
  printf("|Argc:%d|\n", argc);

  for (i = 0; i <= argc; ++i) {
    printf("|Argv[%d]|%s|\n", i, argv[i]);
  }

  strcpy(argv[0], "");
  argv[0] = NULL;

  char* _argv_[4];
  int _argc_ = 3;

  _argv_[0] = strdup("./safeexec");
  _argv_[1] = strdup("--exec");
  _argv_[2] = strdup(filein);
  _argv_[3] = NULL;

  printf("----Arguments sent to safeexec---\n");

  for (int i = 0; i <= _argc_; ++i) {
    printf("argv[%d]: %s\n", i, _argv_[i]);
  }

  printf("!!!!--------Calling safeexec---------!!!!\n");

  RESULTS res;
  res = safeexec(_argc_, _argv_, envp);

  FILE* outputfile = fopen(fileout, "a");
  if (outputfile == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }


  fprintf(outputfile, "N:%d,", numero);

  fprintf(outputfile, "Mem:%d,", res->mem);

  fprintf(outputfile, "Time:%d\n", res->timer);

  fclose(outputfile);

  return 0;
}
