// C++
#include <fstream>
#include <iostream>
#include <string>

// C
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Other
#include "Parser/cmdline.h"
#include "SafeExec/safeexec.h"

int main(int argc, char* argv[], char* envp[]) {
  int i;
  //-----------ARG PARSING STUF-----------START//

  printf("\n$$$$$$$$$$I'M ON ANALYZE!!!$$$$$$$$$\n\n");

  printf("+++++++++++++++++++++++++++++++++++++\n");
  printf("++++++-------------------------++++++\n");

  struct gengetopt_args_info ai;
  if (cmdline_parser(argc, argv, &ai) != 0) {
    exit(1);
  }

  printf("ai.filout_time_arg: %s\n", ai.filein_arg);
  printf("ai.filout_mem_arg: %s\n", ai.filein_arg);
  printf("ai.filein_arg: %s\n", ai.filein_arg);
  printf("ai.fileout_arg: %s\n", ai.fileout_arg);
  printf("ai.number_orig: %d\n", ai.number_arg);
  printf("ai.answers_arg: %s\n", ai.answers_arg);

  // printf("ai.verbose_flag: %d\n", ai.verbose_flag);
  // for (i = 0; i < (int)ai.value_given; ++i) {
  //   printf("ai.value_arg[%d]: %d\n", i, ai.value_arg[i]);
  // }

  printf("++++++-------------------------++++++\n");
  printf("+++++++++++++++++++++++++++++++++++++\n\n");

  int numero = ai.number_arg;

  char* answerfile = ai.answers_arg;
  char* filein = ai.filein_arg;
  char* fileout = ai.fileout_arg;
  char* program = ai.program_arg;
  char* fileout_time = ai.fileout_time_arg;
  char* fileout_mem = ai.fileout_mem_arg;
  //-----------ARG PARSING STUF-----------END//

  //-----------Getting Args ready to send to Safeexec----------START//
  printf("Getting ready for safeexec\n");
  printf("|Argc:%d|\n", argc);

  for (i = 0; i <= argc; ++i) {
    printf("|Argv[%d]: |%s|\n", i, argv[i]);
  }

  int _argc_ = 5;
  char* _argv_[6];
  _argv_[0] = strdup("./safeexec");
  _argv_[1] = strdup("--mem");
  _argv_[2] = strdup("100000");
  _argv_[3] = strdup("--exec");
  _argv_[4] = strdup(program);
  _argv_[5] = NULL;

  printf("------Arguments to be sent to safeexec------\n");

  printf("|_Argc_:%d|\n", _argc_);
  for (int i = 0; i <= _argc_; ++i) {
    printf("|_Argv_[%d]: |%s|\n", i, _argv_[i]);
  }
  //-----------Getting Args ready to send to Safeexec----------END//

  //----------------OTHER STUFF---------------START//
  freopen(filein, "r", stdin);
  printf("IMPORTANT: STDIN now comes from the file %s\n", filein);

  printf("!!!!--------Calling safeexec---------!!!!\n");

  printf("IMPORTANT: STDOUT is going to be temporarily redirected\n");
  // freopen (answerfile,"w+",stdout);

  // FROM STACKOVERFLOW
  int bak, newish;
  fflush(stdout);
  bak = dup(1);
  newish = open(answerfile, O_WRONLY | O_CREAT);
  dup2(newish, 1);
  close(newish);

  // !!!SAFEEXEC!!!
  RESULTS res;
  res = safeexec(_argc_, _argv_, envp);

  // FROM STACKOVERFLOW
  fflush(stdout);
  dup2(bak, 1);
  close(bak);

  FILE* outputfile_time = fopen(fileout_time, "a");
  if (outputfile_time == NULL) {
    printf("Error opening file that stores time info!\n");
    exit(1);
  }

  FILE* outputfile_mem = fopen(fileout_mem, "a");
  if (outputfile_mem == NULL) {
    printf("Error opening file that stores mem info!\n");
    exit(1);
  }
  //----------------OTHER STUFF---------------END//

  printf(
      "!!!!!!!!!!!!!!!!!!!!!!!!!!!$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&"
      "\n");
  if (res->code != OK) {
    printf("|NOT OK!!!|");
  }
  printf("RES->CODE=(%d)\n", res->code);
  printf(
      "!!!!!!!!!!!!!!!!!!!!!!!!!!!$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&"
      "\n");

  if (res->code == OK) {
    fprintf(outputfile_time, "%d\t", numero);
    fprintf(outputfile_time, "%.9f\n", res->cputime);

    fprintf(outputfile_mem, "%d\t", numero);
    fprintf(outputfile_mem, "%d\n", res->mem);
  }

  // fprintf(outputfile, "Time:%d,", res->timer);
  // printf("-------CPU Time:%.9f----------\n", res->cputime);

  fclose(outputfile_time);
  fclose(outputfile_mem);
  fclose(stdin);

  // COMPARAR FICHEIROS!!!!!!!!!!
  int ch1, ch2;

  std::ifstream first_file(answerfile);
  std::ifstream second_file(fileout);

  if (answerfile){printf("WTFIISADASDASDAJSHFDJAGSDF7687t234y2g424uy23f42fgfgh234fgh2fgh234fgh423fgh4fgh2fg234fgh\n");}

  FILE* fp1 = fopen(answerfile, "r");
  if (fp1 == NULL) {
    printf("Cannot open %s for reading\n ", answerfile);
    exit(1);
  }
  FILE* fp2 = fopen(fileout, "r");
  if (fp2 == NULL) {
    printf("Cannot open %s for reading\n", fileout);
    exit(1);
  }
  ch1 = getc(fp1);
  ch2 = getc(fp2);

  while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
    ch1 = getc(fp1);
    ch2 = getc(fp2);
  }

  if (ch1 == ch2)
    printf("Files are identical\n");
  else if (ch1 != ch2)
    printf("Files are Not identical\n");

  fclose(fp1);
  fclose(fp2);


////ASUGDYUASGYDA&/R%TUDFYGSAJR%ADSTFUGI/R%&TSUDAFGJKT&UADGSJTUYGSDA

// fclose(stdout);

return 0;
}
