#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/select.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <stdarg.h>
#include <time.h>

void setlimit (int resource)
{
  struct rlimit limit;

}

int main(int argc, char const *argv[])
{

    setlimit (RLIMIT_NPROC);

	pid_t a;
	int *b;
	int c;
	struct rusage *d;
	wait4(a,b,c,d);
	return 0;
}
