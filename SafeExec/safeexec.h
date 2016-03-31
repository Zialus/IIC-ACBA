#ifndef SAFEEXEC_H
#define SAFEEXEC_H

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

#define INFINITY 0xFFFFFFFF

struct results
{
  int status;
  int mem;
  int timer;
};

typedef struct results* RESULTS;

struct config
{
  rlim_t cpu;
  rlim_t memory;
  rlim_t core;
  rlim_t stack;
  rlim_t fsize;
  rlim_t nproc;
  rlim_t clock;

  uid_t minuid;
  uid_t maxuid;
};

RESULTS safeexec (int argc, char **argv, char **envp);
void idset (int v, char *section, unsigned int value);
int install (char *section);

#endif
