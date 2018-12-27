// C++
#include <fstream>
#include <iostream>
#include <string>

// C
#include <math.h>
#include <stdio.h>
#include <string.h>

// My stuff
#include "applyfunction.h"
#include "pearson.h"

int main(int agrc, char* argv[]) {
  int size = 0;

  std::string line;
  std::ifstream infile(argv[1]);

  // Calculate the size necessary for the the array
  if (infile.good()) {
    // ingore the first line
    getline(infile, line);
    // Calculate the number of relevant lines
    while (getline(infile, line)) {
      size++;
    }
  } else {
    printf("Error Opening File\n");
    exit(1);
  }
  infile.close();

  double array_linear[size];
  double array_resultados[size];

  int linecount = 0;

  std::ifstream infile2(argv[1]);

  if (infile2.good()) {
    // ingore the first line
    getline(infile2, line);

    while (getline(infile2, line)) {
      // position of "\t" in str
      std::size_t pos = line.find("\t");
      // get string from the begining to "\t"
      std::string goes_into_array_normal = line.substr(0, pos);
      // get string from "\t" to the end
      std::string goes_into_array_resultados =
          line.substr(pos + 1, line.length());

      // std::cout << size << ": " << line << std::endl;
      // std::cout << "Normal: " << goes_into_array_normal << std::endl;
      // std::cout << "Resultados: " << goes_into_array_resultados << std::endl;

      double x = std::stod(goes_into_array_normal);
      double y = std::stod(goes_into_array_resultados);

      array_linear[linecount] = x;
      array_resultados[linecount] = y;

      linecount++;
    }
  } else {
    printf("Error Opening File\n");
    exit(1);
  }
  infile2.close();

  int counter = linecount;
  double (*funcArray[5])(double i) = {&linear, &nSquare, &nCube, &nLogN, &logN};
  char* funcNames[] = {"linear", "nSquare", "nCube", "nLogN", "logN"};

  double maxRes = 0;
  char maxFunction[256];
  for (size_t i = 0; i < 5; i++) {
    double* various_arrays = applyFunction(array_linear, counter, funcArray[i]);

    printf("--------------------------\n");

    for (int i = 0; i < counter; ++i) {
      printf("Index|%d|--> Array_Linear |%f|  Various_Arrays |%f|\n", i,
             array_linear[i], various_arrays[i]);
    }

    double res = pearson(array_resultados, various_arrays, counter);

    printf("\nResultado of %s: %f\n", funcNames[i], res);

    printf("--------------------------\n");

    if (res > maxRes) {
      maxRes = res;
      strcpy(maxFunction, funcNames[i]);
    }
  }

  std::ofstream gradefile(argv[2],std::fstream::app);

  if (gradefile.good()) {
      gradefile << std::endl << "Closest function is: " << maxFunction << " and has value: " << maxRes << std::endl;
  } else {
    printf("Error Opening File\n");
    exit(1);
  }

  printf("\n\n\n----------------------------------> FINAL RESULT <----------------------------------\n");
  printf("Best Function is: %s and has value: %f\n", maxFunction, maxRes);

  gradefile.close();
  
}
