#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global Variable to check how many tasks remain

int queueSize = 0;

// Queue Structure

struct Queue {
	
	char id[11];
	char condition[11];
	
	int priority;
	
	Queue *next, *prev;
	
} *head = NULL, *tail = NULL;

// CreateNewNode Function

struct Queue* createNewNode (char id[], char condition[], int priority){
	
	Queue* node = (Queue*) malloc (sizeof(Queue));
	
	strcpy (node->id, id);
	strcpy (node->condition, condition);
	
	node->priority = priority;
	
	node->next = node->prev = NULL;
	
	return node;
	
}

// Push Function

void push (char id[], char condition[], int priority){
	
	struct Queue* node = createNewNode (id, condition, priority);
	
	// Push One
	
	if (head == NULL) {
		head = tail = node;
	}
	
	// Push Head
	
	else if (head->priority < node->priority){
		head->prev = node;
		node->next = head;
		head = node;
	}
	
	// Push Tail
	
	else if (tail->priority > node->priority){
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
	
	// Push Mid
	
	else {
		
		struct Queue* curr = head;
		
		while (curr && curr->priority >= node->priority){
			curr = curr->next;
		}
		
		if (curr == NULL){
			tail->next = node;
			node->prev = tail;
			tail = node;
			return;
		}
		
		node->prev = curr->prev;
		node->next = curr;
		
		curr->prev->next = node;
		curr->prev = node;
		
	}
	
}

// View or Print Function

void view (){
	
	printf ("Task List: \n\n");
	
	struct Queue *curr = head;
	int num = 1;
	
	while (curr){
		printf ("%d %s %s\n", num, curr->id, curr->condition);
		curr = curr->next;
		num++;
	}
	
	puts("");
	
}

// doOne Function

void doOne(){
	
	struct Queue* curr = head;
	
	if (head == NULL) return;
	
	queueSize--;
	
	printf ("%s is DONE\n", curr->id);
	printf ("%d tasks remaining...\n\n", queueSize);
	
	// Pop head
	
	if (head == tail){
		free (head);
		head = tail = NULL;
	}
	
	else {
		head = head->next;
		free (head->prev);
		head->prev = NULL;
	}
	
}

// doAll Function

void doAll(){
	
	struct Queue* curr = head;
	
	if (head == NULL) return;
	
	while (curr){
		
		printf ("%s is DONE\n", curr->id);
	
		// Pop one
		
		if (head == tail){
			free (head);
			head = tail = NULL;
		}
		
		// Pop Head
		
		else {
			head = head->next;
			free (head->prev);
			head->prev = NULL;
		}
		
		curr = curr->next;
		queueSize--;
		
	}
	
	printf ("%d tasks remaining...\n\n", queueSize);
	
}


int main(){
	
	do {
		
		char action[11];
		char id[11];
		char condition[11];
		int priority;
		
		printf ("Input Action: ");
		scanf ("%s", action); getchar();
		
		if (strcmp(action, "INSERT") == 0) {
			
			scanf ("%s %s", id, condition); getchar();
			
			if (strcmp (condition, "HIGH") == 0) priority = 1;
			else priority = 0;
			
			queueSize++;
			push (id, condition, priority);
			
		}
		
		else if (strcmp(action, "VIEW") == 0) {
			view ();
		}
		
		else if (strcmp(action, "DO") == 0) {
			doOne();
		}
		
		else if (strcmp(action, "DOALL") == 0) {
			doAll();
		}
		
		else if (strcmp(action, "EXIT") == 0) {
			break;
		}
		
		else {
			printf ("\n\nInvalid Input!\n");
		}
		
	}
	
	while (true);
	
	return 0;
	
}

