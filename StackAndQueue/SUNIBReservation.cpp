#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Customer {
	
	char name[101];
	int priority;
	
	Customer *next, *prev;
	
} *head = NULL, *tail = NULL, *curr = NULL;


struct Customer *createNewNode (char name[], int priority){
	
	struct Customer* temp = (struct Customer*) malloc (sizeof(struct Customer));
	
    strcpy (temp->name, name);
    temp->priority = priority;
    
    temp->next = NULL;
    temp->prev = NULL;
  
    return temp;
    
}


void push (Customer *node){
	
	// Push One
	
	if (head == NULL){
		head = tail = node;
		head->prev = NULL;
		tail->next = NULL;
	}
	
	// Push Head
	
	else if (node->priority < head->priority){
		node->next = head;
		head->prev = node;
		head = node;
		head->prev = NULL;
	}
	
	// Push Tail
	
	else if (node->priority >= tail->priority){
		node->prev = tail;
		tail->next = node;
		tail = node;
		tail->next = NULL;
	}
	
	// Push Mid
	
	else {
		
		curr = head;
		
		while (curr->next->priority <= node->priority){
			curr = curr->next;
		}
		
		Customer *a = curr;
		Customer *b = curr->next;
		
		a->next = node;
		node->prev = a;
		
		node->next = b;
		b->prev = node;
		
	}
	
}


void pop (Customer *node){
	
	// Pop One
	
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


void popAll (){
	while (head != NULL){
		pop(head);
	}
}


int main(){
	
	int menu = 0;
	
	do {
		
		system ("cls");
		
		// Title
		
		puts ("==============================");
		puts ("|SUNIB Restaurant Reservation|");
		puts ("==============================");
		
		puts ("\nWaiting Line:");
		
		// Print Queue
		
		int num = 1;
		curr = head;
		
		if (curr == NULL){
			printf ("Queue is empty!\n");
		}
		
		else {
			while (curr != NULL){
				printf ("%d. %s\n", num, curr->name);
				curr = curr->next;
				num++;
			}
		}
		
		// Menu
		
		puts ("\n1. Add Customer to Queue");
		puts ("2. Serve One");
		puts ("3. Serve All");
		puts ("4. Dismiss Queue");
		puts ("0. Exit\n");
		
		do {
			printf (">> ");
			scanf ("%d", &menu); getchar();
		}
		
		while (menu < 0 || menu > 4);
		
		if (menu == 1){
			
			int priority;
			char checker[21];
			bool flag = false;
			char name[101];
			
			do {
				
				system ("cls");
				printf ("Input your Membership and Name (Membership [space] Name formatted): ");
				scanf ("%s %s", checker, name); getchar();
				
				if (strcmp (checker, "VVIP") == 0 || strcmp (checker, "VIP") == 0 || strcmp (checker, "Member") == 0 || strcmp (checker, "Guest") == 0){
					flag = true;
				}
				
			}
			
			while (!flag);
			
			if (strcmp (checker, "VVIP") == 0){
				priority = 0;
			}
			
			else if (strcmp (checker, "VIP") == 0){
				priority = 1;
			}
			
			else if (strcmp (checker, "Member") == 0){
				priority = 2;
			}
			
			else {
				priority = 3;
			}
			
			Customer *node = createNewNode (name, priority);
			push (node);
			
		}
		
		else if (menu == 2){
			
			curr = head;
			
			if (curr == NULL){
				printf ("\nThe queue is empty!");
				getchar();
			}
			
			else {
				if (curr->priority == 0){
					printf ("\nAttention! %s is being served at VVIP Table.", curr->name);
				}
				
				else if (curr->priority == 1) {
					printf ("\nAttention! %s is being served at VIP Table.", curr->name);
				}
				
				else if (curr->priority == 2) {
					printf ("\nAttention! Member %s is being served at Regular Table.", curr->name);
				}
				
				else if (curr->priority == 3) {
					printf ("\nAttention! Guest %s is being served at Regular Table.", curr->name);
				}
				
				getchar();
				
				pop (curr);
			}
			
		}
		
		else if (menu == 3){
			
			curr = head;
			
			if (curr == NULL){
				printf ("\nThe queue is empty!");
				getchar();
			}
			
			else {
				while (curr != NULL){
				
					if (curr->priority == 0){
						printf ("\nAttention! %s is being served at VVIP Table.", curr->name);
					}
					
					else if (curr->priority == 1) {
						printf ("\nAttention! %s is being served at VIP Table.", curr->name);
					}
					
					else if (curr->priority == 2) {
						printf ("\nAttention! Member %s is being served at Regular Table.", curr->name);
					}
					
					else if (curr->priority == 3) {
						printf ("\nAttention! Guest %s is being served at Regular Table.", curr->name);
					}
					
					curr = curr->next;
					
				}
				
				getchar();
				
				popAll();
			}
			
		}
		
		else if (menu == 4){
			
			printf ("\nEnd of the day :)");
			getchar();
			
			popAll();
			
		}
		
	}
	
	while (menu != 0);
	
	system ("cls");
	
	printf ("Thank youu :)\n");
	
	return 0;
}
