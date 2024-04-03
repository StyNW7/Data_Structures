#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Data {
	
	int id;
	char description[101];
	char employee[101];
	char duedate[101];
	char status[101];
	
	struct Data *next, *prev;
	
} *head = NULL, *tail = NULL;


struct Data* createNewNode (int id, char description[], char employee[], char duedate[], char status[]){
	
	struct Data* node = (Data*) malloc (sizeof(Data));
	
	node->id = id;
	strcpy (node->description, description);
	strcpy (node->employee, employee);
	strcpy (node->duedate, duedate);
	strcpy (node->status, status);
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


void push (int id, char description[], char employee[], char duedate[], char status[]){
	
	struct Data* node = createNewNode(id, description, employee, duedate, status);
	
	if (head == NULL){
		head = tail = node;
	}
	
	else if (strcmp(head->duedate, duedate) > 0){
		node->next = head;
		head->prev = node;
		head = node;
	}
	
	else if (strcmp(tail->duedate, duedate) < 0){
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	
	else {
		
		struct Data *curr = head;
		
		while (curr && strcmp(curr->duedate, duedate) == 0){
			curr = curr->next;
		}
		
		node->next = curr;
		node->prev = curr->prev;
		
		curr->prev->next = node;
		curr->prev = node;
		
	}
	
}


void pop (){
	
	if (head == NULL) return;
	
	else {
		
		head = head->next;
		free (head->prev);
		head->prev = NULL;
		
	}
	
}


void printAll(){
	
	struct Data* curr = head;
	
	printf ("%-5s %-30s %-20s %-10s %-10s\n\n", "ID", "Task Description", "Assigned Employee", "Due Date", "Status");
	
	while (curr){
		
		printf ("%-5d %-30s %-20s %-10s %-10s\n", curr->id, curr->description, curr->employee, curr->duedate, curr->status);
		curr = curr->next;
		
	}
	
}


int main(){
	
	int task;
	printf ("Input number of tasks: ");
	scanf ("%d", &task); getchar();
	
	for (int i = 0; i < task; i++){
		
		char des[101];
		char employee[101];
		char duedate[101];
		
		printf ("\n\nTask Description: ");
		scanf ("%[^\n]", des); getchar();
		
		printf ("\nAssign Employee: ");
		scanf ("%[^\n]", employee); getchar();
		
		printf ("\nDue Date: ");
		scanf ("%[^\n]", duedate); getchar();
		
		push (i+1, des, employee, duedate, "Pending");
		
	}
	
	printAll();
	
	char yes[10];
	printf ("\n\nIs there any task that has reached its due date? ");
	scanf ("%s", yes);
	
	if (strcmp (yes, "Yes") == 0){
		
		int howMany;
		printf ("\n\nHow many? ");
		scanf ("%d", &howMany);
		
		Data* curr = head;
		
		system ("cls");
		
		printf ("Task Details:\n\n");
		
		for (int i = 0; i < howMany; i++){
			printf ("ID: %d\n", curr->id);
			printf ("Description: %s\n", curr->description);
			printf ("Employee: %s\n", curr->employee);
			printf ("Due Date: %s\n", curr->duedate);
			printf ("Status: %s\n\n", "Completed");
			
			curr = curr->next;
		}
		
		for (int i = 0; i < howMany; i++){
			pop();
		}
		
	}
	
	printAll();
	
	return 0;
	
}

