// C++
#include <fstream>
#include <iostream>
#include <string>

// C
#include <math.h>
#include <stdio.h>

// My stuff
#include "applyfunction.h"
#include "pearson.h"

int main(int agrc, char* argv[]) {
  double array_linear[1000];
  double array_resultados[1000];

  int linecount = 0;

  std::string line;
  std::ifstream infile(argv[1]);
  
  if (infile) {
    getline(infile, line);  // ingore the first line
    while (getline(infile, line)) {
      std::size_t pos = line.find("\t");  // position of "\t" in str

      std::string goes_into_array_normal =
          line.substr(0, pos);  // get from " " to the end
      std::string goes_into_array_resultados =
          line.substr(pos + 1, line.length());  // get from " " to the end

      // std::cout << linecount << ": " << line << std::endl;

      // std::cout << "Normal: " << goes_into_array_normal << std::endl;

      // std::cout << "Rresultados: " << goes_into_array_resultados << std::endl;

      double v1 = std::stod(goes_into_array_normal);
      double v2 = std::stod(goes_into_array_resultados);

      array_linear[linecount] = v1;
      array_resultados[linecount] = v2;

      linecount++;
    }
  } else {
    printf("no file found\n");
  }
  infile.close();

  // Signifies the end of the Array
  array_linear[linecount] = -1;
  array_resultados[linecount] = -1;

  // Counts the elements (required!!)
  // And prints them for debug purposes

  // printf("\n-----nSquare-----START----\n");

  int count = 0;
  while (array_linear[count] != -1) {
    // printf("Index|%d|--> Value |%f| \n", count, array_linear[count]);
    count++;
  }

  // printf("\n");

  double* resSquare = applyFunction(array_linear, count, nSquare);

  resSquare[count] = -1;

  int i = 0;
  while (resSquare[i] != -1) {
    // printf("Index|%d|--> Value |%f| \n", i, resSquare[i]);
    i++;
  }

  // printf("\n-----nSquare-----END----\n");

  // printf("\n-----nCube-----START----\n");

  int count2 = 0;
  while (array_linear[count2] != -1) {
    // printf("Index|%d|--> Value |%f| \n", count2, array_linear[count2]);
    count2++;
  }

  // printf("\n");

  double* resCube = applyFunction(array_linear, count, nCube);

  resCube[count2] = -1;

  int i2 = 0;
  while (resCube[i2] != -1) {
    // printf("Index|%d|--> Value |%f| \n", i2, resCube[i2]);
    i2++;
  }

  // printf("\n-----nCube-----END-----\n");

  // printf("\n-----nLogN-----START-----\n");

  int count3 = 0;
  while (array_linear[count3] != -1) {
    // printf("Index|%d|--> Value |%f| \n", count3, array_linear[count3]);
    count3++;
  }

  // printf("\n");

  double* resNLogN = applyFunction(array_linear, count, nLogN);

  resNLogN[count3] = -1;

  int i3 = 0;
  while (resNLogN[i3] != -1) {
    // printf("Index|%d|--> Value |%f| \n", i3, resNLogN[i3]);
    i3++;
  }

  // printf("\n-----nLogN-----END-----\n");

  // printf("\n-----ActualArray-----START-----\n");

  int i9 = 0;
  while (array_resultados[i9] != -1) {
    // printf("Index|%d|--> Value |%f| \n", i9, array_resultados[i9]);
    i9++;
  }

  // printf("\n-----ActualArray-----END-----\n");

  int size = count;

  double res;

  res = pearson(array_resultados, array_linear, size);
  printf("Linear pearson  ---> %f\n", res);

  res = pearson(array_resultados, resSquare, size);
  printf("Square pearson  ---> %f\n", res);

  res = pearson(array_resultados, resNLogN, size);
  printf("NlogN pearson  ---> %f\n", res);

  res = pearson(array_resultados, resCube, size);
  printf("Cube pearson  ---> %f\n", res);
}
