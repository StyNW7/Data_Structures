#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	
	int age;
	char name[20];
	
	struct Person *next;
	
} *head = NULL, *curr = NULL;


struct Person* createNewNode (char name[], int age){
	
	struct Person* node = (struct Person*) malloc (sizeof (struct Person));
	
	node->age = age;
	strcpy(node->name, name);
	
	node->next = NULL;
	
	return node;
	
}


void display (){
	
	printf ("Current Linked List:\n\n");
	curr = head;
	
	while (curr){
		
		printf ("%d | %s\n", curr->age, curr->name);
		
		curr = curr->next;
		
	}
	
}


void pushAll (char name[], int age){
	
	struct Person* node = createNewNode(name, age);
	
	if (head == NULL){
		head = node;
	}
	
	else if (node->age < head->age){
		
		node->next = head;
		head = node;
		
	}
	
	else {
		
		curr = head;
		
		while (curr->next && node->age > curr->next->age){
			curr = curr->next;
		}
		
		if (curr->next == NULL){
			curr->next = node;
			node->next = NULL;
		}
		
		else {
			
//			Person *a = curr;
//			Person *b = curr->next;
//			
//			a->next = node;
//			node->next = b;
			
			node->next = curr->next;
			curr->next = node;

		}
		
	}
	
}


void pop(int target){
	
	curr = head;
	
	if (head->age == target){
		head = head->next;
		free (curr);
	}
	
	else {
		
		while (curr->next && curr->next->age != target){
			curr = curr->next;
		}
		
		if (!curr->next){
			printf ("Value not found!");
			getchar();
		}
		
		else {
			
			Person *a = curr;
			Person *del = curr->next;
			Person *b = del->next;
			
			a->next = b;
			
			free (del);
			
		}
		
	}
	
}


void popAll(){
	
	while (head != NULL){
		
		curr = head;
		
		head = head->next;
		free (curr);
		
	}
	
}


int main(){
	
	int menu = 0;
	
	do {
		
		system ("cls");
		
		puts ("Menu");
		puts ("==================");
		puts ("1. Push");
		puts ("2. Pop");
		puts ("3. Pop All");
		puts ("4. Print");
		puts ("5. Exit\n");
		
		do {
			printf (">> ");
			scanf ("%d", &menu); getchar();
		}
		
		while (menu < 1 || menu > 5);
		
		if (menu == 1){
			
			int age;
			printf ("Input age: ");
			scanf ("%d", &age); getchar();
			
			char name[101];
			printf ("Input name: ");
			scanf ("%s", name); getchar();
			
			pushAll (name, age);
			
		}
		
		else if (menu == 2){
			
			if (!head) {
				printf ("There is no data!");
				getchar();
			}
			
			else {
				int age;
				printf ("Input age: ");
				scanf ("%d", &age); getchar();
				
				pop (age);
			}
			
		}
		
		else if (menu == 3){
			
			if (!head) {
				printf ("There is no data!");
				getchar();
			}
			
			else {
				popAll();
			}
			
		}
		
		else if (menu == 4){
			system ("cls");
			display();
			printf ("\n\n>> ");
			getchar();
		}
		
	}
	
	while (menu != 5);
	
	return 0;
  
}
