#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Parser/cmdline.h"
#include "SafeExec/safeexec.h"

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
  printf("ai.number_orig: %d\n", ai.number_arg);
  
  // printf("ai.verbose_flag: %d\n", ai.verbose_flag);
  // for (i = 0; i < (int)ai.value_given; ++i) {
  //   printf("ai.value_arg[%d]: %d\n", i, ai.value_arg[i]);
  // }

  printf("++++++-------------------------++++++\n");
  printf("+++++++++++++++++++++++++++++++++++++\n\n");

  int numero = ai.number_arg;

  char* filein = ai.filein_arg;
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


  printf("----Arguments to be sent to safeexec---\n");

  printf("|_Argc_:%d|\n",_argc_);
  for (int i = 0; i <= _argc_; ++i) {
    printf("|_Argv_[%d]: |%s|\n", i, _argv_[i]);
  }


  //-----------Getting Args ready to send to Safeexec----------END//


  freopen (filein,"r",stdin);
  printf ("IMPORTANT: STDIN now comes from the file %s\n",filein);

  printf ("IMPORTANT: STDOUT is going to be redirected to lixo\n");
  freopen ("lixo.txt","a",stdout);



  printf("!!!!--------Calling safeexec---------!!!!\n");

  RESULTS res;

  res = safeexec(_argc_, _argv_, envp);

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

  printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&\n");
  if (res->code != OK) {printf("|NOT OK!!!|");}
  printf("RES->CODE=(%d)\n",res->code);
  printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!$$$$$$$$$$$$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&\n");

  if (res->code == OK) {

    fprintf(outputfile_time, "%d\t", numero);
    fprintf(outputfile_time, "%.9f\n", res->cputime);

    fprintf(outputfile_mem, "%d\t", numero);
    fprintf(outputfile_mem, "%d\n", res->mem);

  }

  // fprintf(outputfile, "Time:%d,", res->timer);

  printf("-------CPU Time:%.9f----------\n", res->cputime);

  fclose(outputfile_time);
  fclose(outputfile_mem);
  fclose(stdin);
  fclose(stdout);


  return 0;
}
