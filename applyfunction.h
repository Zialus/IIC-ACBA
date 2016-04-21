#include <math.h>
#include <stdlib.h>

int nSquare(int n){
	return n*n;
}

int nCube(int n){
	return n*n*n;
}

int nLogN(int n){
	return n*log(n);

}

int* applyFunction(int* array,int size, int function(int i)){

	int* results = (int*) malloc(sizeof(int));

	for (int i = 0; i < size; i++)
	{
		results[i] = function(array[i]);
	}

	return (int*) results;
}

