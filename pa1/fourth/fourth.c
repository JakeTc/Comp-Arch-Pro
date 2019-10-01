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
	//testing!
	int arr1[] = {1, 2, 3};
	int arr2[] = {7, 9, 11};
	int ans = dotProduct(arr1, arr2, 3);
	
	printf("The ans is: %d\n", ans);
	
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
	
	//reads the rows and columns of the array
	int m1r;
	int m1c;
	fscanf(fp, "%d\t%d", &m1r, &m1c);
	
	printf("this gai %d\n", m1r);
	int **matrix1 = (int**)malloc(m1r * sizeof(int*));
	int i = 0;
	for(i = 0; i < m1c; i++) {
		matrix1[i] = malloc(m1c * sizeof(int));
	}
//ERROR LIES BEFORE THIS!	
	
	printf("this works\n");
	
	int j = 0;
	for(i = 0; i < m1r; i++) {
		for(j = 0; j < m1c; j++) {
			//do not need to check for edge cases
			fscanf(fp, "%d", &matrix1[i][j]);
		}
		
		
		
	}
	print2DArr(matrix1, m1r, m1c);
	
	
	//free matrix1
	for(i = 0; i < m1r; i++) {
		free(matrix1[i]);
	}
	free(matrix1);
	
	//free matrix2
	
	return 0;
}




























