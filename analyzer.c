#include <stdio.h>
#include "Safeexec/safeexec.h"
#include <sys/resource.h>

/* typedef struct Results{
 	int memory;
 	int elapsed_time;
 } Results ;*/



int main(int argc, char *argv[],char *envp[])
{
	printf("WTF\n");
	RESULTS res;
	res = safeexec(argc, argv, envp);
	printf("%d",res->mem);
	return 0;
}
