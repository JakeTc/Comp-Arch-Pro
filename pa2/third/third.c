#include <stdlib.h>
#include <stdio.h>

//will go to that index and set that bit to be 1 or 0
unsigned short set(unsigned short *x, unsigned short arg1, unsigned short arg2) {
	unsigned short mask = 1;//stores the location of the bit to be converted
	unsigned short tempx = *x;
	unsigned short bit = arg2;//stores the desired bit value
	
	//takes mask and sets it to the appropriate index
	int i = 0;
	for(i = 0; i < arg1; i++) {
		mask = mask << 1;
		
	}
	
	//does a simple or operation if we are setting the bit to 1
	//no matter what the bit at that location is, it will now be
	//set to 1
	if((int)bit) {
		tempx = mask | tempx;
		
	
	//gets the complement of x, then does the or operation, then finds the complement of that
	//this allows us to do an or operation that sets that bit to 0
	} else {
		tempx = ~tempx;
		tempx = mask | tempx;
		tempx = ~tempx;
		
	}
	*x = tempx;
	
	return tempx;
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

//will go to that index and change that bit to its complement
unsigned short comp(unsigned short *x, unsigned short arg1) {
	unsigned short tempx = *x;
	unsigned mask = 1;
		
	//takes mask and sets it to the appropriate index
	int i = 0;
	for(i = 0; i < arg1; i++) {
		mask = mask << 1;
		
	}
	
	//turns the bit at the mask to 0 if it is 1
	if(mask & tempx) {
		tempx = ~tempx;
		tempx = mask | tempx;
		tempx = ~tempx;
	
	//turns the bit at the mask to 1 if it is 0
	} else {
		tempx = mask | tempx;
	}
	
	*x = tempx;
	return tempx;
}


int main(int argc, char*argv[]) {
	

	return 0;
}
