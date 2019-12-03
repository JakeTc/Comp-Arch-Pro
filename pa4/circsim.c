#include <stdlib.h>
#include <stdio.h>
//#include <string.h>

char* operators[] = {"NOT", "AND", "NAND", "OR", "NOR", "XOR"};


int variableScan(FILE* fp, int amt, char** list) {
	int i = 0;
	for(i = 0; i < amt; i++) {
		fscanf(fp, "%s", list[i]);
	}

}

//searches a string array and returns the index of the string
//if not found, returns -1.

int searchStrArr(char* str, char** arr, int length) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(strcmp(str, arr[i])) {
			return i;
		}
	}
	return -1;
}

int gate(char* line) {

}

//NOT
int not(int a) {
	return !a;
}

//AND
int and(int a, int b) {
	return a & b;
}

//NAND
int nand(int a, int b) {
	return !(a & b);
}

//OR
int or(int a, int b) {
	return a | b;
}

//NOR
int nor(int a, int b) {
	return !(a | b);
}

//XOR
int xor(int a, int b) {
	return a ^ b;
}

int main(int argc, char* argv[]) {
	//if no file name is given
	if(argc == 1) {
		printf("Error: No arguments given.\n");
		return 0;
	}
	
	//makes a file stream
	FILE* fp = fopen(argv[1], "r");
	
	//if file could not be found
	if(fp == NULL) {
		printf("Error: File could not be found.\n");
		return 0;
	}
	
	char buffer[500];
	int i = 0;
	int amt = 0;
	int amt2 = 100;
		
	//ignores directive, and stores the amount of inputs
	fscanf(fp, "%s %d", buffer, &amt);
	
	//take all of the input variable names and stores them in an array
	
	char inputs[amt][100];
	
	for(i = 0; i < amt; i++) {
		fscanf(fp, "%s", inputs[i]);
	}
	
	//again ignores directive, and stores the amount of outputs
	fscanf(fp, "%s %d", buffer, &amt);
	
	char outputs[amt][100];
	
	for(i = 0; i < amt; i++) {
		fscanf(fp, "%s", outputs[i]);
	}
	
	
	
	//find the line length of the file
	FILE* savePoint = fp;
	int commandAmt = 0;
	
	
	
	fgets(buffer, 400, fp); //moves to the next line, since fp is still pointing at the previous line
	while(fgets(buffer, 400, fp) != NULL) {
		printf("%d @ %s", commandAmt, buffer);
		commandAmt++;
	}
	commandAmt--;//for whatever reason, code above adds one extra to this var
	
	
	//reset fp to the save point
	fp = savePoint;
	//printf("%d: %s", commandAmt, fgets(buffer, 400, fp));
	
	return 0;
	
	//Makes a string array of the commands
	char* commands[commandAmt][3];
	for(i = 0; i < commandAmt; i++) {
		
	}
	
	while(fgets(buffer, 400, fp) != NULL) {
		
	}
	
 	
	return 0;
}
