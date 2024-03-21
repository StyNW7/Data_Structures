#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	
	int age;
	char name[20];
	
	struct Person *next, *prev;
	
} *head = NULL, *tail = NULL;


//struct Person *head = NULL, *tail = NULL;


struct Person* createNewNode (char name[], int age){
	
	struct Person* node = (struct Person*) malloc (sizeof (struct Person));
	
	node->age = age;
	strcpy(node->name, name);
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


void pushHead(char name[], int age){
	
	struct Person* node = createNewNode(name, age);
	
	if (head == NULL){
		head = tail = node;
	}
	
	else {
		node->next = head;
		head->prev = node;
		head = node;
	}
	
}


void pushTail(char name[], int age){
	
	struct Person* node = createNewNode(name, age);
	
	if (head == NULL){
		head = tail = node;
	}
	
	else {
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	
}


void printAll (){
	
	if (head == NULL){
		printf("There's no data\n");
	}
	
	else {
		
		struct Person* current = head;
		
		while (current){
			
			printf("Name: %s\nAge: %d\n", current->name, current->age);
			
			current = current->next;
			
		}
		
	}
	
}


void reversePrint (){
	
	if (head == NULL){
		printf("There's no data\n");
	}
	
	else {
		
		struct Person* current = tail;
		
		while (current){
			
			printf("Name: %s\nAge: %d\n", current->name, current->age);
			
			current = current->prev;
			
		}
		
	}
	
}


void pushMid(char name[], int age){
	
	struct Person* node = createNewNode(name, age);
	
	if (head == NULL){
		head = tail = node;
	}
	
	else if (head->age > age){
		pushHead(name, age);
	}
	
	else if (tail->age < age){
		pushTail (name, age);
	}
	
	else {
		
		struct Person* current = head;
		
		while (current){
			
			if (current->age > age){
				break;
			}
			
			current = current->next;
			
		}
		
		node->next = current;
		node->prev = current->prev;
		
		current->prev = node;
		current->prev->next = node;
		
	}
	
}


void popHead (){
	
	if (head == NULL){
		printf("There's no data\n");
	}
	
	else if (head == tail){
		free (head);
		head = tail = NULL;
	}
	
	else {
		
		struct Person* temp = head;
		
		head = head->next;
		head->prev = NULL;
		
		free (temp);
		
	}
	
}


void popTail(){
	
	if (head == NULL){
		printf("There's no data\n");
	}
	
	else if (head == tail){
		free (head);
		head = tail = NULL;
	}
	
	else {
		
		struct Person* temp = tail;
		
		tail = tail->prev;
		tail->next = NULL;
		
		free (temp);
		
	}
	
}


void popMid(int age){
	
	if (head == NULL){
		printf("There's no data\n");
	}
	
	else if (head == tail){
		free (head);
		head = tail = NULL;
	}
	
	else if (age == head->age){
		popHead();
	}
	
	else if (age == tail->age){
		popTail();
	}
	
	else {
		
		struct Person* current = head;
		
		while (current){
			if (current->age == age){
				break;
			}
			current = current->next;
		}
		
		if (!current){
			printf("There's no such data\n");
		}
		
		else {
			
			struct Person* temp = current;
			
			current->prev = current->prev->next;
			current->prev->next = current;
			
			free (temp);
			
		}
		
	}
	
}


int main(){
	
	pushMid ("Stanley", 17);
	pushMid ("Angel", 15);
	pushMid ("Andika", 18);
	
	popMid(18);
	
	printAll();
	
	return 0;
}

