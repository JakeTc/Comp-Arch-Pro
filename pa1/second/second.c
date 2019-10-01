

typedef struct _Node {
	int *data;
	struct _Node *next;
} Node;

Node *mkNode(int *data) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = NULL;

	return nwNode;
}

Node *push(int *data, Node* head) {
	Node *nwNode = malloc(sizeof(Node));
	nwNode->data = data;
	nwNode->next = head;

	return nwNode;
}

//deletes the first occurrence of target (INTEGER VERSION)
//returns 0 if it finds the target, 1 if it doesnt
int deleteTarget(Node *head, int target) {
	Node *ptr = head;
	
	//checks if the head is null
	if(ptr == NULL) {
		return 1;
	}
	
	Node *next = head->next;
	Node *temp = NULL;
	
	//edge case if the head of the linked list is the target
	if(*(int)(ptr->data) == target) {
		free(ptr);
		ptr = next;
		next = next->next;
	} else {
		//searches linked list for target
		//if found, takes node out of the list and frees it.
		//reconnects the linklist afterward
		while(*next != NULL) {
			if(*(int*)(next->data) == target) {
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

//deletes the entirety of a linked list!
void deleteLL(Node *head) {
	Node *current = head;
	Node *next;
	
	while(current != NULL) {
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
}


int main(int argc, char* argv[]) {
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
	
	return 0;
}























