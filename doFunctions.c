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
  double array[1000];

  int linecount = 0;

  std::string line;
  std::ifstream infile("ficheiro.in");
  if (infile) {
    while (getline(infile, line)) {
      std::size_t pos = line.find(" ");  // position of " " in str

      std::string put_in_the_array =
          line.substr(0, pos);  // get from " " to the end

      double v = std::stoi(line);
      array[linecount] = v;

      std::cout << "LOOOOOL HERE IT IS: " << put_in_the_array << std::endl;

      std::cout << linecount << ": " << line
                << std::endl;  // supposing '\n' to be line end
      linecount++;
    }
  } else {
    printf("no file found\n");
  }
  infile.close();

  // Signifies the end of the Array
  array[linecount] = -1;

  // Counts the elements (required!!)
  // And prints them for debug purposes

  printf("-----n^2-----START\n");

  int count = 0;
  while (array[count] != -1) {
    printf("COUNTING THIS STUFF |%d| ----- LOOK AT THE RESULT |%f| \n", count,
           array[count]);
    count++;
  }

  printf("\n");

  double* resSquare = applyFunction(array, count, nSquare);

  resSquare[count] = -1;

  int i = 0;
  while (resSquare[i] != -1) {
    printf("COUNTING THIS AGAIN |%d| ----- LOOK AT THE RESULT |%f| \n", i,
           resSquare[i]);
    i++;
  }

  printf("-----n^2-----END\n");

  printf("-----n^3-----START\n");

  int count2 = 0;
  while (array[count2] != -1) {
    printf("COUNTING THIS STUFF |%d| ----- LOOK AT THE RESULT |%f| \n", count2,
           array[count2]);
    count2++;
  }

  printf("\n");

  double* resCube = applyFunction(array, count, nCube);

  resCube[count2] = -1;

  int i2 = 0;
  while (resCube[i2] != -1) {
    printf("COUNTING THIS AGAIN |%d| ----- LOOK AT THE RESULT |%f| \n", i2,
           resCube[i2]);
    i2++;
  }

  printf("-----n^3-----END\n");

  printf("-----nlogn-----START\n");

  int count3 = 0;
  while (array[count3] != -1) {
    printf("COUNTING THIS STUFF |%d| ----- LOOK AT THE RESULT |%f| \n", count3,
           array[count3]);
    count3++;
  }

  printf("\n");

  double* resNLogN = applyFunction(array, count, nLogN);

  resNLogN[count3] = -1;

  int i3 = 0;
  while (resNLogN[i3] != -1) {
    printf("COUNTING THIS AGAIN |%d| ----- LOOK AT THE RESULT |%f| \n", i3,
           resNLogN[i3]);
    i3++;
  }

  printf("-----nlogn-----END\n");

  int size = count;

  double res;
  res = pearson(array, resSquare, size);
  printf("Square pearson  ---> %f\n", res);
  res = pearson(array, resNLogN, size);
  printf("NlogN pearson  ---> %f\n", res);

  res = pearson(array, resCube, size);
  printf("Cube pearson  ---> %f\n", res);
}
