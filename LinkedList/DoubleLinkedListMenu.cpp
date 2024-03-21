#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Person {
	
	int score;
	char id[10];
	char name[101];
	
	struct Person *next, *prev;
	
} *head = NULL, *tail = NULL;


void generateID (char id[]){
	
	for (int i = 0; i < 3; i++){
		id[i] = rand() % 10 + '0';
	}
	
}


struct Person* createNewNode (char name[], char id[], int score){
	
	struct Person* node = (struct Person*) malloc (sizeof (struct Person));
	
	node->score = score;
	strcpy(node->name, name);
	strcpy(node->id, id);
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


void display (){
	
	Person* curr = head;
	
	if (head == NULL){
		int num = 1;
		
		for (int i = 0; i < 47; i++) printf ("=");
		printf ("\n");
		
		printf ("| %-4s | %-5s | %-20s | %-5s |\n", "No", "ID", "Name", "Score");
		
		printf ("|");
		for (int i = 0; i < 45; i++) printf ("=");
		printf ("|\n");
			
		printf ("| There's no data yet!                        |\n");
		
		for (int i = 0; i < 47; i++) printf ("=");
	}
	
	else {
		
		int num = 1;
		
		for (int i = 0; i < 47; i++) printf ("=");
		printf ("\n");
		
		printf ("| %-4s | %-5s | %-20s | %-5s |\n", "No", "ID", "Name", "Score");
		
		printf ("|");
		for (int i = 0; i < 45; i++) printf ("=");
		printf ("|\n");
		
		while (curr){
			
			printf ("| %-4d | %-5s | %-20s | %-5d |\n", num, curr->id, curr->name, curr->score);
			
			curr = curr->next;
			num++;
			
		}
		
		for (int i = 0; i < 47; i++) printf ("=");
		
	}
	
}


void pushAll (char name[], char id[], int score){
	
	Person *node = createNewNode (name, id, score);
	
	if (head == NULL) {
		head = tail = node;
		node->next = node->prev = NULL;
	}
	
	// Push Head
	
	else if (strcmp (node->id, head->id) < 0){
		node->next = head;
		head->prev = node;
		head = node;
		head->prev = NULL;
	}
	
	// Push Tail
	
	else if (strcmp(node->id, tail->id) > 0){
		node->prev = tail;
		tail->next = node;
		tail = node;
		tail->next = NULL;
	}
	
	// Push Mid
	
	else {
		
		Person *curr = head;
		
		while (strcmp (node->id, curr->next->id) > 0){
			curr = curr->next;
		}
		
		node->prev = curr;
		node->next = curr->next;
		
		curr->next = node;
		
	}
	
}



void pop (char id[]){
	
//	Only 1 Data
	
	if (head == tail){
		free (head);
		head = tail = NULL;
		return;
	}
	
//	Pop Head
	
	if (strcmp(head->id, id) == 0){
		
		head = head->next;
		free (head->prev);
		head->prev = NULL;
		
	}
	
//	Pop Tail
	
	else if (strcmp(tail->id, id) == 0){
		
		tail = tail->prev;
		free (tail->next);
		tail->next = NULL;
		
	}
	
//	Pop Mid
	
	else {
		
		Person *curr = head;
		
		while (curr && strcmp (curr->id, id) != 0){
			
			curr = curr->next;
			
		}
		
		if (!curr){
			printf ("ID not found!\n");
			getchar();
		}
		
		else {
			Person *a = curr->prev;
			Person *del = curr;
			Person *b = del->next;
			
			a->next = b;
			b->prev = a;
			
			free (del);
		}

	}
	
}


int main(){
	
	srand (time(0));
	
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
			
			char name[101];
			printf ("Input name: ");
			scanf ("%s", name); getchar();
			
			int score;
			printf ("Input score: ");
			scanf ("%d", &score); getchar();
			
			char id[11];
			
			generateID(id);

			pushAll (name, id, score);
			
		}
		
		else if (menu == 2){
			
			if (!head) {
				printf ("There is no data!");
				getchar();
			}
			
			else {
				char id[11];
				printf ("Input ID to POP: ");
				scanf ("%s", id); getchar();
				
				pop (id);
			}
			
		}
		
		else if (menu == 3){
			
			if (!head) {
				printf ("There is no data!");
				getchar();
			}
			
			else {
//				popAll();
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
