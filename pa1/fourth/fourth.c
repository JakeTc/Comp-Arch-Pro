#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//takes the dot product of two 1D arras
int dotProduct(int arr1[], int arr2[], int size) {
	
	int product = 0;
	int i = 0;
	for(i = 0; i < size; i++) {
		product = product + (arr1[i] * arr2[i]);
	}
		
	return product;
}

//if the matrices cannot be multiplied, returns 1
int badMultiply(int m1r, int m1c, int m2r, int m2c) {
	if(m1c != m2r) {
		return 1;
	}

	return 0;
}


int main(int argc, char* argv[]) {
	int arr1[] = {1, 2, 3};
	int arr2[] = {7, 9, 11};
	int ans = dotProduct(arr1, arr2, 3);
	
	printf("The ans is: %d\n", ans);
	
	return 0;
}
