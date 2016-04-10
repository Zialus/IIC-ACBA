#include <stdio.h>
#include "safeexec.h"
#include <sys/resource.h>


int main(int argc, char *argv[],char *envp[])
{
  printf("bomdia\n");
  RESULTS res;
  printf("%d\n",argc);

  int i;
  for (i = 0; i < argc; ++i)
  {
    printf("%d|%s|\n",i,argv[i]);
  }
  strcpy(argv[0],"");
  argv[0] = NULL;


      char* _argv_[3];
      int _argc_ = 3;
      char* exec_string = (char*)"--exec";

  

      char* arg_for_safeexec1 = exec_string;
      char* arg_for_safeexec2 = (char*) "FICHEIRO1" ;



      _argv_[0] = strdup("./safeexec");
      _argv_[1] = arg_for_safeexec1;
      _argv_[2] = arg_for_safeexec2;



  res = safeexec(_argc_,_argv_, envp);
  printf("%d",res->mem);
  return 0;
}