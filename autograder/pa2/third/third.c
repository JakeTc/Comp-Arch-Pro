#include <stdlib.h>
#include <stdio.h>

//will go to that index and return the bit that is there
unsigned short get(unsigned short *x, unsigned short arg1) {
	unsigned short tempx = *x;
	unsigned short mask = 1;
	
	//shifts the number so that the bit we are looking for is at the last place
	tempx = tempx >> arg1;
	
	//returns whether or not the bit is a 1 or a 0
	return tempx & mask;
}

//gets the front of the panindrome (more significant digits)
unsigned short getFront(unsigned short *x) {
	
	unsigned short tempx = *x;
	return tempx >> 8;
}

//gets the back of the palindrome (less significant digits)
unsigned short getBack(unsigned short *x) {
	
	unsigned short tempx = *x;
	unsigned short back = 0;
	
	int i = 7;
	for(i = 0; i < 8; i++) {
		back = back | get(&tempx, i);
		back = back << 1;
	}
	
	back = back >> 1;
	
	return back;
}

int main(int argc, char*argv[]) {
	//number to be pushed around
	unsigned short _x = 0;
	unsigned short *x = &_x;
	
	//determines if there is an argument given
	if(argc == 1) {
		printf("Insufficient amount of arguments!\n");
	}
	
	*x = atoi(argv[1]);
	
	//printf("%hu\t	%hu\n", getFront(x), getBack(x));
	
	//prints if it is a palindrome or not
	if(!(getFront(x) ^ getBack(x))) {
		printf("Is-Palindrome\n");
	} else {
		printf("Not-Palindrome\n");
	}

	return 0;
}
