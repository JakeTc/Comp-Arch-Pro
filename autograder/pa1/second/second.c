#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	int data;
	struct _Node *next;
} Node;

Node *mkNode(int data) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = NULL;

	return nwNode;
}

Node *push(int data, Node* head) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = head;

	return nwNode;
}

//deletes the first occurrence of target (INTEGER VERSION)
//returns 0 if it finds the target, 1 if it doesnt
int deleteTarget(Node **head, int target) {
	Node *ptr = *head;
	
	//checks if the head is null
	if(ptr == NULL) {
		return 1;
	}
	
	Node *next = (*head)->next;
	Node *temp = NULL;
	
	//edge case if the head of the linked list is the target
	if(ptr->data == target) {
		free(ptr);
		ptr = next;
		next = next->next;
		*head = ptr;
	} else {
		//searches linked list for target
		//if found, takes node out of the list and frees it.
		//reconnects the linklist afterward
		while(next != NULL) {
			if(next->data == target) {
				temp = next;
				ptr->next = next->next;
				next = ptr->next;
				free(temp);
				break;
			}
			
			//iterates both pointers
			ptr = ptr->next;
			next = ptr->next;
		}
	}
	
	return 0;
}

//inserts a node in ascending order based on the data
int insertNodeASort(Node **head, int nwData) {
	//edge case for if the list is empty
	Node *ptr = *head;
	if(*head == NULL) {
		*head = mkNode(nwData);
		return 0;	
	
	//edge case for if the data belongs before the head
	} else if((*head)->data > nwData) {
		Node *temp = *head;
		*head = mkNode(nwData);
		(*head)->next = temp;
		return 0;
	}
		
	//iterates ptr and next
	Node *next = ptr->next;
	
	//iterates pointers until it finds the correct spot
	while(next != NULL && (next->data) <= nwData) {
		ptr = ptr->next;
		next = ptr->next;
	}
	
	if(next == NULL) {
		ptr->next = mkNode(nwData);
		return 0;
	} else {
		ptr->next = mkNode(nwData);
		ptr->next->next = next;
		return 0;
	}
	
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

void countLL(Node *head) {
	Node *ptr = head;
	int counter = 0;
	while(ptr != NULL) {
		counter++;
		ptr = ptr->next;
	}
	
	printf("%d\n", counter);
}

void printLL(Node *head) {
	Node *ptr = head;
	int dupe = ptr->data;
	
	//prints head first
	printf("%d\t", ptr->data);
	ptr = ptr->next;
	
	while(ptr != NULL) {
		if(ptr->data != dupe) {
			printf("%d\t", ptr->data);
			dupe = ptr->data;
		}
		ptr = ptr->next;
	}
	printf("\n");
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

int main(int argc, char* argv[]) {
	/*
	//test linkedlist
	Node *head = mkNode(1);
	head->next = mkNode(3);
	Node *ptr = head->next;
	ptr->next = mkNode(4);
	ptr = ptr->next;
	
	ptr->next = mkNode(4);
	ptr = ptr->next;
	ptr->next = mkNode(7);

	ptr = ptr->next;
	ptr->next = mkNode(10);
	ptr = ptr->next;
	
	Node **h = &head;
	
	pLL(head);
	//deleteTarget(h, 4);
	insertNodeASort(h, 7);
	p(head);
	*/
	
	//checks for arguments
	if(argc == 1) {
		printf("insufficient amount of arguments!\n");
		return 0;
	}
	
	//opens file
	FILE *file = fopen(argv[1], "r");
	
	if(file == NULL) {
		printf("File could not be opened!\n");
		return 0;
	}
	
	//variables for linked list
	Node *head = NULL;
	Node **h = &head;

	//variables for file reading
	char action[100];
	int data = 0;
	while(fscanf(file, "%s\t%d", action, &data) != EOF) {
		if(action[0] == 'i') {
			insertNodeASort(h, data);
		} else if(action[0] == 'd') {
			deleteTarget(h, data);
		} else {
			
		}	

	}
	countLL(head);
	printLL(head);

	deleteLL(head);
		
	fclose(file);
	return 0;
}























