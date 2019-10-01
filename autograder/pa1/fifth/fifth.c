#include <stdlib.h>
#include <stdio.h>



int isVowel(char letter) {
	if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u') {
		return 1;
	} else {
		return 0;
	}
	
	
	
}

int main(int argc, char* argv[]) {
	
	int i = 1;
	for(i = 1; i < argc; i++) {
		int j = 0;
		
		//goes through each argument and prints volwels of the string
		while(argv[i][j] != '\0') {
			if(isVowel(argv[i][j])) {
				printf("%c", argv[i][j]); 
				
				
			}
			
			//increment j
			j++;
		}
		
		
		
	}
	
	
	//starts a new line
	printf("\n");
	
	return 0;
}
