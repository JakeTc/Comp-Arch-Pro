#include <stdio.h>
#include <stdlib.h>


typedef struct _Node {
	int data;
	struct _Node *next;
} Node;

//makes a node and returns a pointer to it
Node *mkNode(int data) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = NULL;

	return nwNode;
}

//deletes the entirety of a linked list!
void deleteLL(Node *head) {
	Node *current = head;
	Node *next;
	
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	return;
}

//inserts at the end of the list
//ASSUMES HEAD IS NOT NULL
void insertEnd(Node *head, int data) {
	Node *ptr = head;
	while(ptr->next != NULL) {
		ptr = ptr->next;
	}
	
	ptr->next = mkNode(data);
	return;
}

//searches through LL for data
//returns 1 if successful
int searchLL(Node *head, int data) {
	Node *ptr = head;
	
	//searches through list for data
	while(ptr != NULL) {
		if(ptr->data = data) {
			return 1;
		}
	}
	
	//returns 0 if unsuccessful
	return 0;
}

//coutns the amount of nodes that are in the Linked List
void countLL(Node *head) {
	Node *ptr = head;
	int counter = 0;
	while(ptr != NULL) {
		counter++;
		ptr = ptr->next;
	}
	
	printf("%d\n", counter);
}

//for testing
void pLL(Node *head) {
	Node *ptr = head;
	
	while(ptr != NULL) {
		printf("%d\t", ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
	
}

int getKey(int data) {
	int key = data % 10000;
	
	if(key < 0) {
		key = key + 10000;
	}
	
	return key;
}

//returns 1 if it finds a node at that key
int searchHash(Node **hashtable, int data) {
	int key = getKey(data);
	
	if(hashtable[key] != NULL) {
		return 1;
	}
	
	return 0;
}

//for inserting into the hastable
int insertHash(Node *hashtable[], int data) {
	
	//gets the key and sees if the key is in the array
	int key = getKey(data);
	if(hashtable[key] == NULL) {
		hashtable[key] = mkNode(data);
		
	} else {
		insertEnd(hashtable[key], data);
		return 1;
	}
	
	
	
	return 0;
}

int main(int argc, char *argv[]) {
	Node **hashtable = calloc(10000, sizeof(Node*));
	int i = 0;
	if(argc == 1) {
		printf("error\n");
		return 0;
	}
	
	FILE *fp = fopen(argv[1], "r");

	if(fp == NULL) {
		printf("error\n");
		return 0;
	}
	
	//variables for file reading
	char action[100];
	int data = 0;
	
	//variables for storing the amount of collisions and successful searches
	int collisions = 0;
	int finds = 0;

	while(fscanf(fp, "%s\t%d", action, &data) != EOF) {
		if(action[0] == 'i') {
			collisions += insertHash(hashtable, data);
		} else if(action[0] == 's') {
			finds += searchHash(hashtable, data);
		}
	}
	
	printf("%d\n", collisions);
	printf("%d\n", finds);
	
	//free used elements of hashtable
	for(i = 0; i < 10000; i++) {
		if(hashtable[i] != NULL) {
			deleteLL(hashtable[i]);
		}
	}
	
	
	//free the hashtable
	free(hashtable);
	
	fclose(fp);
	
	return 0;
}
























