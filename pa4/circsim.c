#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* operators[] = {"NOT", "AND", "NAND", "OR", "NOR", "XOR"};


int variableScan(FILE* fp, int amt, char** list) {
	int i = 0;
	for(i = 0; i < amt; i++) {
		fscanf(fp, "%s", list[i]);
	}

}

//searches a string array and returns the index of the string
//if not found, returns -1.

int searchStrArr(char* str, char* arr[], int length) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(strcmp(str, arr[i]) == 0) {
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
	
	char buffer[512];
	int i = 0;
	int amt = 0;
		
	//ignores directive, and stores the amount of inputs
	fscanf(fp, "%s %d", buffer, &amt);
	
	//take all of the input variable names and stores them in an array
	
	//mallocs all of the inputs
	char** inputs = (char**)malloc(sizeof(char*) * amt);;
	for(i = 0; i < amt; i++) {
		inputs[i] = (char*)malloc(128);
	}

	for(i = 0; i < amt; i++) {
		fscanf(fp, "%s", inputs[i]);
	}
	
	//again ignores directive, and stores the amount of outputs
	fscanf(fp, "%s %d", buffer, &amt);
	
	//mallocs all of the outputs
	char** outputs = (char**)malloc(sizeof(char*) * amt);;
	for(i = 0; i < amt; i++) {
		outputs[i] = (char*)malloc(128);
	}
	
	for(i = 0; i < amt; i++) {
		fscanf(fp, "%s", outputs[i]);
	}
	
	fgets(buffer, 256, fp); //moves to the next line, since fp is still pointing at the previous line
	
	//makes a save point so that we can seek back to this later
	unsigned long savePoint;
	fflush(fp);
	savePoint = ftell(fp);
	
	//find the line length of the file
	int commandAmt = 0;
	while(fgets(buffer, 256, fp) != NULL) {
		printf("%d @ %s", commandAmt, buffer);
		commandAmt++;
	}
	
	//goes back to savePoint
	fseek(fp, savePoint, SEEK_SET);
	
	//Makes a string array of the commands
	char commands[commandAmt][128];
	for(i = 0; i < commandAmt; i++) {
		fgets(buffer, 256, fp);
		snprintf(commands[i], 128, "%s", buffer);
		//checks if fgets does not reach EOF
		if(commands[i] == NULL) {
			printf("Error: End of file unexpectedly reached.\n");
			return 0;
		}
	}	
	
	//Now finds the amount of arguments that each command takes
	char cmds[commandAmt][4][128];
	int argArr[commandAmt];
	char tempVars[commandAmt][16];
	int tVLength = 0;
	char* token;
	char* delims = " \n";
	int j = 0;
	
	//figures out the amount of arguments that each directive has and finds all of the temp values
	for(i = 0; i < commandAmt; i++) {
		token = strtok(commands[i], delims);
		snprintf(cmds[i][0], 128, "%s", token);
		if(strcmp(token, "NOT") == 0) {
			argArr[i] = 2;	
		} else {
			argArr[i] = 3;
		}
		
		//goes to last argument
		for(j = 0; j < argArr[i]; j++) {
			token = strtok(NULL, delims);
			snprintf(cmds[i][j + 1], 128, "%s", token);
		}
		
		
		//checks if that argument is a temp variable or not, and stores it.		
		int result = searchStrArr(token, outputs, amt);
		if(result == -1) {
			snprintf(tempVars[i], 16, "%s", token);
			tVLength++;
		}
	}
	
	//testing stuff	
	for(i = 0; i < tVLength; i++) {
		printf("|%s|\n", tempVars[i]);
		
	}
		
	printf("---------------------------------------------------------------------\n");
	//testing cmds
	for(i = 0; i < commandAmt; i++) {
		int j = 0;
		for(j = 0; j <= argArr[i]; j++) {
			printf("%s", cmds[i][j]);
			if(j != argArr[i]) {
				printf(" ");
			}
		}
		
		printf("\n");
	}
	
	
	//HAVE YET TO TEST OUT THE NEW CMDS ARRAY, AND THE NEW TEMPS ARRAY!!!
	
	return 0;
}
