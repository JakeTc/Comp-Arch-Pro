#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//takes the dot product of two 1D arras
int dotProduct(int *arr1, int *arr2) {
	int length1 = sizeof(*arr1)/sizeof(int);
	int length2 = sizeof(*arr2)/sizeof(int);
}

//if the matrices cannot be multiplied, returns 1
int badMultiply(int m1r, int m1c, int m2r, int m2c) {
	if(m1c != m2r) {
		return 1;
	}
}


int main(int argc, char* argv[]) {
	int arr1[] = {1, 2, 3};
	int arr2[] = {7, 9, 11};
	dotProduct(arr1, arr2);
	
	return 0;
}
