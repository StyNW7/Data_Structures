#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Queue Structure

struct Queue {
	
	char patientName[101];
	char condition[101];
	
	int priority;
	
	struct Queue *next, *prev;
	
} *head = NULL, *tail = NULL;

// CreateNewNode Function

struct Queue* createNewNode (char patientName[], char condition[], int priority){
	
	struct Queue* node = (Queue*) malloc (sizeof(Queue));
	
	strcpy (node->patientName, patientName);
	strcpy (node->condition, condition);
	node->priority = priority;
	
	node->next = node->prev = NULL;
	
	return node;
	
}

// Push Function

void push (char name[], char condition[], int priority){
	
	struct Queue* node = createNewNode(name, condition, priority);
	
	// Push 1
	
	if (head == NULL){
		head = tail = node;
	}
	
	// Push Head
	
	else if (head->priority < node->priority){
		node->next = head;
		head->prev = node;
		head = node;
	}
	
	// Push Tail
	
	else if (tail->priority > node->priority){
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	
	// Push Mid
	
	else {
		
		struct Queue* curr = head;
		
		while (curr && curr->priority >= node->priority){
			curr = curr->next;
		}
		
		if (!curr) {
			node->prev = tail;
			tail->next = node;
			tail = node;
			return;
		}
		
		node->prev = curr->prev;
		node->next = curr;
		
		curr->prev->next = node;
		curr->prev = node;
		
	}
	
}

// View or print function

void view (){
	
	struct Queue* curr = head;
	
	if (curr != NULL) {
		if (curr->priority == 4) printf ("%s is in the Emergency Room\n", curr->patientName);
		else if (curr->priority == 3) printf ("%s is in the Examination Room\n", curr->patientName);
		else printf ("%s is in the Consultation Room\n", curr->patientName);
	}
	
	printf ("Waiting Room: ");
	
	if (curr->next != NULL) curr = curr->next;
	else {
		printf ("None\n");
		return;
	}
	
	while (curr){
		
		if (curr->next == NULL) printf ("%s\n\n", curr->patientName);
		else printf ("%s, ", curr->patientName);
		
		curr = curr->next;
		
	}
	
}

// Pop Function

void pop(){
	
	// There is no data
	
	if (head == NULL) return;
	
	// Only 1 data
	
	else if (head == tail){
		free (head);
		head = tail = NULL;
	}
	
	// Pop Head
	
	else {
		
		head = head->next;
		free (head->prev);
		head->prev = NULL;
		
	}
	
}


int main(){
	
	int size;
	printf ("Input Size: ");
	scanf ("%d", &size);
	getchar();
	
	for (int i = 0; i < size; i++){
		
		char c1[101], c2[101], c3[101];
		int priority;
		
		printf ("Input %d action: ", i+1);
		scanf ("%s", c1);
		getchar();
		
		if (strcmp (c1, "ADD") == 0) {
			
			scanf ("%s %s", c2, c3); getchar();
			
			if (strcmp (c3, "Critical") == 0) priority = 4;
			else if (strcmp (c3, "Serious") == 0) priority = 3;
			else if (strcmp (c3, "Fair") == 0) priority = 2;
			else if (strcmp (c3, "Good") == 0) priority = 1;
			
			push (c2, c3, priority);
			
		}
		
		else if (strcmp (c1, "CALL") == 0){
			
			view();
			pop();
			
		}
		
		else {
			printf ("\nInput invalid!\n\n");
		}
		
	}
	
	return 0;
	
}

