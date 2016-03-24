#include <stdio.h>
#include "Safeexec/safeexec.h"

int main(int argc, char *argv[],char *envp[]){
	RESULTS res;

	res = safeexec(argc, argv, envp);
	
	if(res!=NULL){
		printf("-----\n\n");
		printf("%d\n",res->mem);
		printf("%d\n",res->timer);
		return 0;
	}

	return 1;
}
