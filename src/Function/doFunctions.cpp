#include <fstream>
#include <iostream>
#include <string>

#include <cmath>
#include <cstdio>
#include <cstring>

#include "applyfunction.h"
#include "pearson.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Wrong number of arguments\n");
    return EXIT_FAILURE;
  }

  int size = 0;

  std::string line;
  std::ifstream infile(argv[1]);

  // Calculate the size necessary for the the array
  if (infile.good()) {
    // ignore the first line
    getline(infile, line);
    // Calculate the number of relevant lines
    while (getline(infile, line)) {
      size++;
    }
  } else {
    printf("Error Opening File\n");
    return EXIT_FAILURE;
  }
  infile.close();

  double array_linear[size];
  double array_resultados[size];

  int linecount = 0;

  std::ifstream infile2(argv[1]);

  if (infile2.good()) {
    // ignore the first line
    getline(infile2, line);

    while (getline(infile2, line)) {
      // position of "\t" in str
      std::size_t pos = line.find('\t');
      // get string from the beginning to '\t'
      std::string goes_into_array_normal = line.substr(0, pos);
      // get string from '\t' to the end
      std::string goes_into_array_resultados = line.substr(pos + 1, line.length());

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
    return EXIT_FAILURE;
  }
  infile2.close();

  int counter = linecount;
  double (*funcArray[5])(double i) = {&linear, &nSquare, &nCube, &nLogN, &logN};
  char* funcNames[] = {"linear", "nSquare", "nCube", "nLogN", "logN"};

  double maxRes = 0;
  char maxFunctionName[256];
  for (size_t i = 0; i < 5; i++) {
    double* various_arrays = applyFunction(array_linear, counter, funcArray[i]);

    printf("--------------------------\n");

    for (int j = 0; j < counter; ++j) {
      printf("Index|%d|--> Array_Linear |%f|  Various_Arrays |%f|\n", j, array_linear[j], various_arrays[j]);
    }

    double res = pearson(array_resultados, various_arrays, counter);

    printf("\nResultado of %s: %f\n", funcNames[i], res);

    printf("--------------------------\n");

    if (res > maxRes) {
      maxRes = res;
      strncpy(maxFunctionName, funcNames[i], sizeof(maxFunctionName));
    }
  }

  std::ofstream gradefile(argv[2], std::fstream::app);

  if (gradefile.good()) {
    gradefile << std::endl << "Closest function is: " << maxFunctionName << " and has value: " << maxRes << std::endl;
  } else {
    printf("Error Opening File\n");
    return EXIT_FAILURE;
  }

  printf("\n\n\n----------------------------------> FINAL RESULT <----------------------------------\n");
  printf("Best Function is: %s and has value: %f\n", maxFunctionName, maxRes);

  gradefile.close();

}
