#include <stdlib.h>
#include <stdio.h>



unsigned short add(unsigned short a, unsigned short b) {
	if(b == 0) {
		return a;
	} else {
		return add(a ^ b, (a & b) << 1);
	}
	
}
//goes through each digit and determines if it is a one.
//if it is, adds one to num and determines if the amount 
//of ones was odd or even
unsigned short parity(unsigned short *x) {
	unsigned short mask = 1;
	unsigned short num = 0;
	unsigned short tempx = *x;
	
	
	int i = 0;
	for(i = 0; i < 16; i++) {
		if(tempx & mask) {
			num = add(num, 1);
		}
		tempx = tempx >> 1;
	}
	
	return num & mask;
}

//goes through each digit and determines if it is a one. if two
//ones are seen, adds to num and resets the boolean value
unsigned short pairs(unsigned short *x) {
	unsigned short num = 0;
	unsigned short tempx = *x;
	unsigned short mask = 1;
	unsigned short boolean = 0;
	
	int i = 0;
	for(i = 0; i < 16; i++) {
		if(boolean & (tempx & mask)) {
			num = add(num, 1);
			boolean = 0;
		}else if(tempx & mask) {
			boolean = 1;
		} else {
			boolean = 0;
		}
		tempx = tempx >> 1;
	}
	
	return num;
}

int main(int argc, char *argv[]) {
	//checks if there was an argument
	if(argc == 1) {
		printf("Insufficient amount of arguments!\n");
		return 0;
	}
	
	//x for storing and using the number
	unsigned short _x = atoi(argv[1]);
	unsigned short *x = &_x;
	
	//prints out even or odd parity in the amt of ones
	if(parity(x)) {
		printf("Odd-Parity\t");
	} else {
		printf("Even-Parity\t");
	}
	
	//prints out the number of pairs
	printf("%u\n", pairs(x));
	
	return 0;
}
