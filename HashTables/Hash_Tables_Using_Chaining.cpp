#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const int SIZE = 10;


struct Person {
	
	int age;
	char name[101];
	Person *next, *prev;
	
} *head[SIZE], *tail[SIZE], *curr;


struct Person* createNewNode (char name[], int age){
	
	Person *newNode = (Person*) malloc(sizeof(Person));
	
	strcpy (newNode->name, name);
	newNode->age = age;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
	
}


int hash (char name[]){
	
	int key = 0;
	
	for (int i = 0; i < strlen(name); i++){
		key += name[i];
	}
	
	return (key % SIZE);
	
}


void push (char name[], int age){
	
	Person *node = createNewNode (name, age);
	int index = hash(name);
	
	// Push Head
	
	if (head[index] == NULL){
		head[index] = tail[index] = node;
	}
	
	// Push Tail
	
	else {
		
		tail[index]->next = node;
		node->prev = tail[index];
		tail[index] = node;
		
		tail[index]->next = NULL;
		
	}
	
}


void pop (char name[]){
	
	int index = hash(name);
	
	if (head[index] == NULL && tail[index] == NULL){
		printf ("There is no such data..."); getchar();
		return;
	}
	
	// Pop 1
	
	else if (head[index] == tail[index] && strcmp (head[index]->name, name) == 0){
		free (head[index]);
		head[index] = tail[index] = NULL;
	}
	
	// Pop Head
	
	else if (strcmp (head[index]->name, name) == 0){
		
		head[index] = head[index]->next;
		free (head[index]->prev);
		head[index]->prev = NULL;
		
	}
	
	// Pop Tail
	
	else if (strcmp (tail[index]->name, name) == 0){
		
		tail[index] = tail[index]->prev;
		free (tail[index]->next);
		tail[index]->next = NULL;
		
	}
	
	// Pop Mid
	
	else {
		
		curr = head[index];
		
		while (curr != NULL && strcmp(curr->name, name) != 0){
			curr = curr->next;
		}
		
		if (curr){
			Person *a = curr->prev;
			Person *del = curr;
			Person *b = curr->next;
			
			a->next = b;
			b->prev = a;
			
			free (del);
		}
		
	}
	
	printf ("Press enter to continue..."); getchar();
	
}


void view (){
	
	for (int i = 0; i < SIZE; i++){
		
		printf("[%d] >> ", i);
		
		Person *curr = head[i];
		
		while (curr) {
			printf("[%d | %s] >> ", curr->age, curr->name);
			curr = curr->next;
		}
		
		printf("\n");
		
	}
	
}


int main(){
	
	int menu;
	
	while (true){
		
		system ("cls");
		
		puts ("HASH TABLE CHAINING");
		puts ("=============================");
		
		view ();
		
		puts ("=============================\n");
		
		printf ("1. Push\n");
		printf ("2. Pop\n");
		printf ("3. Exit\n");
		
		printf ("\n>> ");
		
		scanf ("%d", &menu);
		getchar();
		
		if (menu == 1) {
			
			int age;
			char name[101];
			system ("cls");
			
			printf ("Input name: ");
			scanf ("%s", name); getchar();
			printf ("Input age: ");
			scanf ("%d", &age); getchar();
			
			push (name, age);
			
		}
		
		else if (menu == 2) {
			
			int age;
			char name[101];
			system ("cls");
			
			printf ("Input name: ");
			scanf ("%s", name); getchar();
			
			pop (name);
			
		}
		
		else if (menu == 3) break;
		
	}
	
	system ("cls");
	
	printf ("Thank youu :)\n");
	
	return 0;
  
}
