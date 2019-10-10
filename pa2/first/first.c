#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short set(int arg1, int arg2) {
	
	
	return 0;
}

unsigned short get(int arg1) {
	
	
	return 0;
}

//will go to that index and change that bit to its complement
unsigned short comp(int arg1) {
	
	
	return 0;
}

int main(int argc, char *argv[]) {
	
	//variables for x
	unsigned short _x = 0;
	unsigned short *x = &_x;

	FILE *fp;
	
	if(argc == 1) {
		printf("No argument was given!\n");
		return 0;
	}
	
	fopen(fp, argv[1]);
	
	if(fp == NULL) {
		printf("Unable to open file!\n");
		return 0;
	}
	//scans x and stores it
	fscanf(fp, "%hu", *x);
	
	char *fx = NULL;
	int arg1 = 0;
	int arg2 = 0;
	
	
	//functions are: get, comp, set
	while(fscanf(fp, "%s\t%d\t%d\t", fx, &arg1, &arg2) != EOF) {
		
		if(strcomp(fx, "get")) {
			*x = get(arg1);
			
		} else if(strcomp(fx, "comp")) {
			*x = comp(arg1);
			
		} else if(strcomp(fx, "set")) {
			*x = comp(arg1, arg2)
			
		}
		
	}
	
	return 0;
}























