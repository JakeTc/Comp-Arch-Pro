#include <stdlib.h>
#include <stdio.h>

typedef struct _Leaf {
	struct _Leaf *left;
	struct _Leaf *right;
	int key;
	
} Leaf;

//makes a new Leaf and returns a pointer to it
Leaf *mkLeaf(int nwkey) {
	Leaf *nwLeaf = malloc(sizeof(Leaf));
	nwLeaf->key = nwkey;
	nwLeaf->left = NULL;
	nwLeaf->right = NULL;
	
	return nwLeaf;
}

//recursively look for a space to put the leaf
Leaf *addLeaf(Leaf *stem, int nwkey) {
	if(stem == NULL) {
		Leaf *nwLeaf = mkLeaf(nwkey);
		return nwLeaf;
	} else {
		
		//if current key is more than nwkey, stores it to the left
		//if current key is less than nwkey, stores it to the right
		//else, does nothing (if equal)
		if(stem->key > nwkey) {
			stem->left = addLeaf(stem->left, nwkey);
		} else if(stem->key < nwkey) {
			stem->right = addLeaf(stem->right, nwkey);
		}
	}
	
	return stem;
}

//recursively print tree
void printTree(Leaf *stem) {
	if(stem == NULL) {
		return;
	}
	
	printTree(stem->left);
	printf("%d\t", stem->key);
	printTree(stem->right);
}

int main(int argc, char *argv[]) {
	Leaf *head = NULL;
	/*
	//testing!
	head = addLeaf(head, 5);
	head = addLeaf(head, 4);
	head = addLeaf(head, 7);
	head = addLeaf(head, 6);
	head = addLeaf(head, 10);
	head = addLeaf(head, 2);
	head = addLeaf(head, 3);
	*/
	
	if(argc == 1) {
		printf("error\n");
		return 0;
	}
	
	FILE *fp = fopen(argv[1], "r");

	if(fp == NULL) {
		printf("error\n");
		return 0;
	}
	
	char temp[100];
	int data;
	
	while(fscanf(fp, "%s\t%d", temp, &data) != EOF) {
		head = addLeaf(head, data);
	}
	
	//prints out tree
	printTree(head);
	printf("\n");
	//if file doesnt exist, just print error
	
	//closes file
	fclose(fp);
	
	return 0;
}
