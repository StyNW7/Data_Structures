#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Queue {
	
	char projectName[101];
	int difficulty;
	
	Queue *next, *prev;
	
} *head = NULL, *tail = NULL;


struct Queue* createNewNode (char projectName[], int difficulty){
	
	Queue* node = (Queue*) malloc (sizeof(Queue));
	
	strcpy (node->projectName, projectName);
	node->difficulty = difficulty;
	
	node->next = node->prev = NULL;
	
	return node;
	
}


void push (char projectName[], int difficulty){
	
	struct Queue* node = createNewNode (projectName, difficulty);
	
	if (head == NULL){
		head = tail = node;
	}
	
	else if (head->difficulty < node->difficulty){
		node->next = head;
		head->prev = node;
		head = node;
	}
	
	else if (tail->difficulty > node->difficulty){
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
	
	else {
		
		struct Queue* curr = head;
		
		while (curr && curr->difficulty >= node->difficulty){
			curr = curr->next;
		}
		
		if (!curr){
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


void pop(){
	
	if (head == NULL) return;
	
	else if (head == tail){
		free (head);
		head = tail = NULL;
	}
	
	else {
		
		head = head->next;
		free (head->prev);
		head->prev = NULL;
		
	}
	
}


void printProject (){
	
	system ("cls");
	
	if (head == NULL) {
		printf ("There is no project yet..\n\n");
		printf ("Press enter to continue...");
		getchar();
		return;
	}
	
	int num = 1;

	printf ("View Project List\n");
	printf ("------------------------------\n\n");
	
	for (int i = 0; i < 60; i++) printf ("=");
	puts ("");
	
	printf ("| %-3s | %-35s | %-12s |\n", "No", "Project Name", "Difficulty");
	for (int i = 0; i < 60; i++) printf ("=");
	puts ("");
	
	struct Queue* curr = head;
	
	while (curr){
		
		printf ("| %-3d | %-35s | %-12d |\n", num, curr->projectName, curr->difficulty);
		
		curr = curr->next;
		num++;
		
	}
	
	for (int i = 0; i < 60; i++) printf ("=");
	
	puts("\n");
	
	printf ("Press enter to continue...");
	getchar();
	
}


void registerProject (){
	
	char name[101];
	int diff;
	
	system ("cls");
	
	printf ("Register New Project\n");
	printf ("==============================\n\n");
	
	do {
		printf ("Input Project Name [8 - 35 Characters]: ");
		scanf ("%[^\n]", name); getchar();
		
		if (strlen(name) >= 8 && strlen (name) <= 35) break;
		else printf ("\nInput Invalid!\n\n");
	}
	
	while (true);
	
	do {
		printf ("Input Project Difficulty [1 - 10]: ");
		scanf ("%d", &diff); getchar();
		
		if (diff >= 1 && diff <= 10) break;
		else printf ("\nInput Invalid!\n\n");
	}
	
	while (true);
	
	push (name, diff);
	
	printf ("\n\nSucess Registered New Project!\n\n");
	printf ("Press enter to continue...");
	getchar();
	
}


void assignProject(){
	
	system ("cls");
	
	if (head == NULL){
		printf ("There is no project yet..\n\n");
		printf ("Press enter to continue...");
		getchar();
		return;
	}
	
	printProject();
	
	system ("cls");
	
	printf ("Assign Programmer to Project\n");
	printf ("--------------------------------------\n\n");
	
	if  (head != NULL){
		printf ("Success assign Programmer to this Project\n");
		printf ("Project Name: %s\n", head->projectName);
		printf ("Difficulty: %d\n\n", head->difficulty);
	}
	
	else {
		printf ("There is no project yet...");
		getchar();
		return;
	}
	
	printf ("Press enter to continue...");
	getchar();
	
	pop();
	
	system ("cls");
	
	printProject();
	
}


void deleteAll(){
	
	while (head){
		pop();
	}
	
	system ("cls");
	printf ("Project Cleared\n\n");
	printf ("Press enter to continue...");
	getchar();
	
}


int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		printf ("Shiruma Project Manager\n");
		printf ("======================================\n\n");
		
		printf ("1. Register New Project\n");
		printf ("2. Assign Programmer to Project\n");
		printf ("3. View Project List\n");
		printf  ("4. Exit\n\n");
		
		printf (">> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) registerProject();
		else if (action == 2) assignProject();
		else if (action == 3) printProject();
		else if  (action == 4) deleteAll();
		
		else {
			printf ("\n\nInput Invalid\n\n");
		}
		
	}
	
	while (action != 4);
	
	system ("cls");
	printf ("Thank youu :)\n");
	
	return 0;
	
}
