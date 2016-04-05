#include "SafeExec/safeexec.h"
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "Parser/cmdline.h"

// #include <fstream>
// #include <iostream>
// #include <string>

// int main(int argc, char **argv) {



 //    bool isCaseInsensitive = false;
 //    int opt;
 //    enum { CHARACTER_MODE, WORD_MODE, LINE_MODE } mode = CHARACTER_MODE;

	// while ((opt = getopt(argc, argv, "ilw")) != -1) {
 //        switch (opt) {
 //        case 'i': isCaseInsensitive = true; break;
 //        case 'l': mode = LINE_MODE; break;
 //        case 'w': mode = WORD_MODE; break;
 //        default:
 //            fprintf(stderr, "Usage: %s [-ilw] [file...]\n", argv[0]);
 //            exit(EXIT_FAILURE);
 //        }
 //    }


//   int linecount = 0;
//   std::string line;
//   std::ifstream infile(argv[1]);
//   if (infile) {
//     while (getline(infile, line)) {
//       std::cout << linecount << ": " << line
//                 << std::endl; // supposing '\n' to be line end
//       linecount++;
//     }
//   }
//   else { printf("no file found\n");}
//   infile.close();
//   return 0;
// }

int main(int argc, char *argv[],char *envp[]){

  // cmdline parser burocracy
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

  char *filename = argv[1];
  // open the file for reading
  FILE *file = fopen(filename, "r");

  // make sure the file opened properly
  if (NULL == file) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return 1;
    }

	// set up the buffer to read the line into. Don't worry too much
    // if some of the lines are longer than 80 characters - the buffer
    // will be made bigger if need be.
    size_t buffer_size = 80;
    char *buffer = (char*) malloc(buffer_size * sizeof(char));

    // read each line and print it to the screen
    int line_number = 0;
    while(-1 != getline(&buffer, &buffer_size, file))
    {
        printf("%d: %s", ++line_number, buffer);
    }
    fflush(stdout);

    // make sure we close the file and clean up the buffer when we're
    // finished
    fclose(file);
    free(buffer);

    return 0;




	// char buf[256];
	// while (fgets (buf, sizeof(buf), stdin)) {
	// 	printf("line: %s", buf);
	// }
	// if (ferror(stdin)) {
	// 	fprintf(stderr,"Oops, error reading stdin\n");
	// 	abort();
	// }
	// return 0;









	// RESULTS res;


	// res = safeexec(argc, argv, envp);
	
	// if(res!=NULL){
	// 	printf("-----\n\n");
	// 	printf("%d\n",res->mem);
	// 	printf("%d\n",res->timer);
	// 	return 0;
	// }

	// return 1;
}
