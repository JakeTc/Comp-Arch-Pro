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
int badMultiply(int m1c, int m2r) {
	if(m1c != m2r) {
		return 1;
	}

	return 0;
}

//for debugging
void printArr(int *arr, int length) {
	int i = 0;

	for(i = 0; i < length; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

//for MORE debugging
void print2DArr(int **arr, int width, int length) {
	int i = 0;
	for(i = 0; i < width; i++) {
		printArr(arr[i], length);
	
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	/*//testing!
	int arr1[] = {1, 2, 3};
	int arr2[] = {7, 9, 11};
	int ans = dotProduct(arr1, arr2, 3);
	
	printf("The ans is: %d\n", ans);
	*/
	//Make the file
	if(argc == 1) {
		printf("Error: no arguments given\n");
		return 0;
	}
	
	FILE *fp = fopen(argv[1], "r");
	
	if(fp == NULL) {
		printf("Error: File could not be opened\n");
		return 0;
	}
	
//makes matrix 1
	//reads the rows and columns of the array
	int m1r;
	int m1c;
	fscanf(fp, "%d\t%d", &m1r, &m1c);
	
	//mallocs matrix 1
	//NOTE: the array of pointers' size is determined by the rows!
	int **matrix1 = (int**)malloc(m1r * sizeof(int*));
	int i = 0;
	for(i = 0; i < m1r; i++) {
		matrix1[i] = malloc(m1c * sizeof(int));
	}	
	
	//assigns integers to appropriate places
	int j = 0;
	for(i = 0; i < m1r; i++) {
		for(j = 0; j < m1c; j++) {
			//do not need to check for edge cases
			fscanf(fp, "%d", &matrix1[i][j]);
		}	
	}
	
	//for testing
	//print2DArr(matrix1, m1r, m1c);
	
//makes matrix 2
	//reads the rows and columns of the array
	int m2c;
	int m2r;
	fscanf(fp, "%d\t%d", &m2r, &m2c);
	
	if(badMultiply(m1c, m2r)) {
		printf("bad-matrices\n");
		
		return 0;
	}
	
	//mallocs matrix 2
	//NOTE: the array of pointers' size is determined by the columns!
	int **matrix2 = (int**)malloc(m2c * sizeof(int*));
	for(i = 0; i < m2c; i++) {
		matrix2[i] = malloc(m2r * sizeof(int));
	}
	
	//assigns the integers to appropriate places
	for(i = 0; i < m2r; i++) {
		for(j = 0; j < m2c; j++) {
			//do not need to check for edge cases
			fscanf(fp, "%d", &matrix2[j][i]);
		}
	}
	
	//for testing
	//print2DArr(matrix2, m2c, m2r);
	
	//creates the multiply matrix. amount of rows = m1r, columns = m2c
	int **matrixProduct = (int**)malloc(m1r * sizeof(int*));
	for(i = 0; i < m1r; i++) {
		matrixProduct[i] = malloc(m2c * sizeof(int));
	}
	
	//multiply the matrices together and store it in the multiply matrix
	for(i = 0; i < m1r; i++) {
		for(j = 0; j < m2c; j++) {
			matrixProduct[i][j] = dotProduct(matrix1[i], matrix2[j], m1c);
		}
		
		
	}
	
	
	
	print2DArr(matrixProduct, m1r, m2c);
	
	
	//free matrix1
	for(i = 0; i < m1r; i++) {
		free(matrix1[i]);
	}
	free(matrix1);
	
	//free matrix2
	for(i = 0; i < m2c; i++) {
		free(matrix2[i]);
	}
	free(matrix2);
	
	//free matrixProduct
	for(i = 0; i < m1r; i++) {
		free(matrixProduct[i]);
	}
	free(matrixProduct);
	
	return 0;
}




























