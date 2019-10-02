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

//for inserting into the hastable
int insertHash(Node *hashtable[], int data) {
	
	//gets the key and sees if the key is in the array
	int key = getKey(data);
	if(hashtable[key] == NULL) {
		hashtable[key] = mkNode(key);
		
	} else {
		
	}
	
	
	
	return 0;
}

int main(int argc, char *argv[]) {
	Node **hashtable = calloc(10000, sizeof(Node*));
	int i = 0;
	
	
	//free used elements of hashtable
	
	//free the hashtable
	free(hashtable);
	
	return 0;
}
























