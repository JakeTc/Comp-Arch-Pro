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

	//creates a new array that combines the input array and the temp array
	char** vars = (char**)malloc(sizeof(char*) * (inAmt + tVLength));
	for(i - 0; i < inAmt; i++) {
		vars[i] = inputs[i];
	}
	
	for(i = inAmt; i < (inAmt + tVLength); i++) {
		vars[i] = tempVars[i - inAmt];
	}
	
	/*
	int a = 0;
	int b = 0;
	int testc = gates(2, a, b);
	printf("%d\n", testc);
	
	return 0;
	*/
	//end of testing
	
	//will prepare to make the truth table
	unsigned short input = 0;
	int varsNum = inAmt + tV
	unsigned short* inputNums = (unsigned short*)malloc(sizeof(unsigned short) * varsNum);
	unsigned short* outputNums = (unsigned short*)malloc(sizeof(unsigned short) * amt);
	
	//prints out every single line
	for(i = 0; i < powr(2, inAmt); i++) {
		int j = 0;
		
		//prints all of the inputs
		for(j = inAmt - 1; j >= 0; j--) {
			//set all of the inputs and prints them
			unsigned short bit = get(&input, (unsigned short)j);
			inputNums[inAmt - j] = bit;
			printf("%hu ", inputNums[inAmt - j]);
		}
		
		printf("\n");	
		
		
		//finds the result
		//search for index of inputs/temps, get those nums, and store the result in the correct
		//index of the outputsNum/tempNums
		//this should be within another loop
		
		
		
		for(j = 0; j < commandAmt; j++) {
			unsigned short a = 0;
			
			
			char* astr = (char*)cmds[j][1];
			printf("%s\t", astr);
			
			//Checks whether the string is a temp var or an input
			//and depending on what it is, will get its corresponding value
			//from the inputNums array or the tempNums array
			if(searchStrArr(astr, (char**)inputs, inAmt) != -1) {
				
				a = inputNums[searchStrArr(astr, (char**)inputs, inAmt)];
				printf("%d\t", searchStrArr(astr, (char**)inputs, inAmt));
				
			} else {
				a = tempNums[searchStrArr(astr, (char**)tempVars, tVLength)];
				printf("%d\t", searchStrArr(astr, (char**)tempVars, tVLength));
			}
			
			
			unsigned short b;
			char* bstr = cmds[j][2];
			printf("%s\t", bstr);
			
			//if the directive is NOT, second argument is the output, doesnt matter
			if(strcmp("NOT", cmds[j][0]) == 0) {
				b = a;
			
			//otherwise, do the same thing for b as we did for a
			} else if(searchStrArr(bstr, inputs, inAmt) != -1) {
				b = inputNums[searchStrArr(bstr, (char**)inputs, inAmt)];
				printf("%d\t", searchStrArr(astr, (char**)inputs, inAmt));
			} else {
				
				b = tempNums[searchStrArr(bstr, (char**)tempVars, tVLength)];
				printf("%d\t", searchStrArr(astr, (char**)tempVars, tVLength));
			}
			
			
			//Finds the correct gate, and the correct location for the result, and stores
			//the result there.
			char* ostr = cmds[j][argArr[j]];
			int index = searchStrArr(ostr, (char**)outputs, amt);
			//if the index is -1, then it is an output
			if(index != -1) {
				outputNums[index] = gates(searchStrArr(cmds[j][0], operators, 6), a, b);
				printf("%s: %d\t", cmds[j][argArr[j]], outputNums[index]);
				
			
			//otherwise, it is a temp variable
			} else {
				index = searchStrArr(ostr, (char**)tempVars, tVLength);
				tempNums[index] = gates(searchStrArr(cmds[j][0], operators, 6), a, b);
				printf("%s: %d\t", cmds[j][argArr[j]], tempNums[index]);
			}
			
			//testing
			unsigned short c = gates(searchStrArr(cmds[j][0], operators, 6), a, b);
			
			printf("%s(%d %d) = %d @ %s\n", cmds[j][0],  a, b, c, ostr);
			
		}
		
		
		//print out all of the outputs
		for(j = 0; j < amt; j++) {
			printf("%s ", outputNums[j]);
		}
		
		
		input++;
		printf("\b\n-----------------------------------------------------------------------\n");
	}
	
	
	return 0;
}
