#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* operators[] = {"NOT", "AND", "NAND", "OR", "NOR", "XOR"};

//power funciton
int powr(int a, int b) {
	int i = 0;
	int result = 1;
	for(i = 0; i < b; i++) {
		result *= a;
	}
	
	return result;
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

//will go to that index and return the bit that is there
unsigned short get(unsigned short *x, unsigned short arg1) {
	unsigned short tempx = *x;
	unsigned short mask = 1;
	
	//shifts the number so that the bit we are looking for is at the last place
	tempx = tempx >> arg1;
	
	//returns whether or not the bit is a 1 or a 0
	return tempx & mask;
}

int gates(int gate, int a, int b) {
	//unsigned short a = (unsigned short)ai;
	//unsigned short b = (unsigned short)bi;
	switch(gate) {
		case 0:
			return ~a + 2;
		case 1:
			return a & b;
		case 2:
			return ~(a & b) + 2;
		case 3:
			return (a | b);
		case 4:
			return ~(a | b) + 2;
		case 5:
			return (a ^ b);
	}
	
	return -1;
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
	int inAmt = 0;
		
	//ignores directive, and stores the amount of inputs
	fscanf(fp, "%s %d", buffer, &amt);
	inAmt = amt;
	
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
		//printf("%d @ %s", commandAmt, buffer);
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
	int tVLength = 0;
	char* token;
	char* delims = " \n";
	int j = 0;
	
	
	char* tempVars[commandAmt];
	//initializing tempVars
	for(i = 0; i < commandAmt; i++) {
		tempVars[i] = (char*)malloc(16);
	}
	
	
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
	
	/*
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
	*/
	
	//creates a new array that combines the input array and the temp array
	int varsLength = inAmt + tVLength;
	char** vars = (char**)malloc(sizeof(char*) * varsLength);

	for(i = 0; i < inAmt; i++) {
		vars[i] = inputs[i];
	}
	
	for(i = inAmt; i < varsLength; i++) {
		vars[i] = tempVars[i - inAmt];
	}
	
	//will prepare to make the truth table
	unsigned short input = 0;
	unsigned short* varsNums = (unsigned short*)malloc(sizeof(unsigned short) * varsLength);
	unsigned short* outputNums = (unsigned short*)malloc(sizeof(unsigned short) * amt);
	int gateNum = -1;
	unsigned short a;
	unsigned short b;
	unsigned short c;
	
	for(i = 0; i < powr(2, inAmt); i++) {
		//prints all of the inputs
		for(j = 0; j < inAmt; j++) {
			//set all of the inputs and prints them
			unsigned short bit = get(&input, (unsigned short)(inAmt - 1 - j));
			varsNums[j] = bit;
			printf("%hu ", varsNums[j]);
		}
		
		j = 0;
		
		//gets the inputs and the outputs as strings
		char* astr;
		char* bstr;
		char* cstr;
		
		for(j = 0; j < commandAmt; j++) {
			astr = (char*)cmds[j][1];
			
			//if directive is NOT
			if(strcmp(cmds[j][0], "NOT") == 0) {
				bstr = astr;
				cstr = (char*)cmds[j][2];
			
			//otherwise, if it is not NOT
			} else {
				bstr = (char*)cmds[j][2];
				cstr = (char*)cmds[j][3];
			}
			
			//now will get the values of the inputs
			//	
			int index = searchStrArr(astr, vars, varsLength);
			a = varsNums[index];
			
			index = searchStrArr(bstr, vars, varsLength);
			b = varsNums[index];
			
			
			
			//Determines which gate to use and computes c
			gateNum = searchStrArr(cmds[j][0], operators, 6);
			c = gates(gateNum, a, b);
			
			//printf("%s(%d, %d) = %d\n", cmds[j][0], a, b, c);
			
			//sets the corresponding variable to the value of c
			index = searchStrArr(cstr, vars, varsLength);
			if(index == -1) {
				index = searchStrArr(cstr, outputs, amt);
				outputNums[index] = c;
			} else {
				varsNums[index] = c;
			}
			
		}
		
		//prints out all of the outputs
		for(j = 0; j < amt; j++) {
			printf("%hu ", outputNums[j]);
		}
		
		printf("\n");
		
		input++;
	}
	
	
	
	
	return 0;
}
