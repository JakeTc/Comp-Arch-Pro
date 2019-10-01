#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//takes in an integer, and returns 1 if its even and 0 if its odd.
int isEven(int num) {
	return !(num % 2);
}

void swap(int *a, int *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
	
}

int* sortDescending(int array[], int size) {
	int i = 0;
	for(i = 0; i < size - 1; i++) {
		int j = 0;
		for(j = 0; j < size - 1; j++) {
			if(array[j] < array[j + 1]) {
				swap((array + j), (array + 1 + j));
			}
		}
	}
	
	return array;
}

int* sortAscending(int array[], int size) {
	int i = 0;
	for(i = 0; i < size - 1; i++) {
		int j = 0;
		for(j = 0; j < size - 1; j++) {
			if(array[j] > array[j + 1]) {
				swap((array + j), (array + 1 + j));
			}
		}
	}
	
	return array;
}

void printArr(int* array, int length) {
	int k = 0;
	for(k = 0; k < length; k++) {
		printf("%d\t", array[k]);
	}
	printf("\n");
	
}

int main(int argc, char *argv[]) {
	//testing!
	
	int length = 0;
	char numbers[100];
	
	//gets the file name
	//throws error if no arguments given
	if(argc == 1) {
		printf("Error: no argument given. Expected: filename\n");
		return 0;
	}
	
	char *fileName = argv[1]; 
	
	//opens the file to read
	FILE *file;
	file = fopen(fileName, "r");
	
	//takes data from the file and stores it
	fscanf(file, "%d", &length);
	fgets(numbers, 100, file);
	fgets(numbers, 100, file);
		
	int array[length];
	int *arr = array;
	char *token;
	const char *dlim = "\t";
	int i = 0;
	
	//stores the items into an array
	token = strtok(numbers, dlim);
	
	while(token != NULL) {
		arr[i] = atoi(token);
		token = strtok(NULL, dlim);
		
		i++;	
	}
	
	length = i;
	
	//determines the size of the evens array
	int evensLength = 0;
	for(i = 0; i < length; i++) {
		if(isEven(arr[i])) {
			evensLength++;
		}
	}
	
	int oddsLength = length - evensLength;
	
	//makes the evens array and the odds array
	int ea[evensLength];
	int *evensArr = ea;
	int oa[oddsLength];
	int *oddsArr = oa;
	
	int e = 0;//keeps track of the current place in evens array
	int o = 0;//keeps track of the current place in odds array
	
	//classify each number as even or odd
	for(i = 0; i < length; i++) {
		//if even, will store the value in the evens array and increment the even counter
		if(isEven(arr[i])) {
			evensArr[e] = arr[i];
			e++;
		//otherwise, store the value in the odds array and increment the odd counter
		} else {
			oddsArr[o] = arr[i];
			o++;
		}	
	}
	
	//sort the evens array
	evensArr = sortAscending(evensArr, evensLength);
	//printArr(evensArr, evensLength);
	
	//sort the odds array
	oddsArr = sortDescending(oddsArr, oddsLength);
	//printArr(oddsArr, oddsLength);
	
	int newArray[length];
	
	for(i = 0; i < evensLength; i++) {
		newArray[i] = evensArr[i];
	}

	
	for(i = 0; i < oddsLength; i++) {
		newArray[i + evensLength] = oddsArr[i];
	}
	
	printArr(newArray, length);
	
	fclose(file);
	
	return 0;
}
