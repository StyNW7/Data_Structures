#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int SIZE = 25;

int hash[SIZE];


int key (int value) {
	return (value % SIZE);
}


void push (int value){
	
	int index = key (value);
	
	if (hash[index] == NULL){
		hash[index] = value;
	}
	
	else {
		
		while (hash[index] != NULL){
			index++;
			if (index >= SIZE-1){
				index = 0;
			}
		}
		
		hash[index] = value;
		
	}
	
	printf ("\nPress enter to continue...");
	
	getchar();
	
}


void pop(int value){
	
	int index = key (value);
	int temp = index;
	
	bool found = true;
	
	if (hash[index] == value){
		hash[index] = NULL;
		printf ("Pop succeed...");
	}
	
	else {
		
		index++;
		
		while (hash[index] != value){
			index++;
			if (index >= SIZE-1){
				index = 0;
			}
			if (index == temp) {
				found = false;
				break;
			}
		}
		
		if (found) {
			hash[index] = NULL;
			printf ("Pop succeed...");
		}
		else printf ("Value not found in hash table!");
		
	}
	
	getchar();
	
}


int main(){
	
	int menu;
	
	while (true){
		
		system ("cls");
		
		puts ("HASH TABLE LINEAR PROBING");
		puts ("=============================");
		
		for (int i = 0; i < SIZE; i++){
			printf ("%-2d -> %d\n", i, hash[i]);
		}
		
		puts ("=============================\n");
		
		printf ("1. Push\n");
		printf ("2. Pop\n");
		printf ("3. Exit\n");
		
		printf ("\n>> ");
		
		scanf ("%d", &menu);
		getchar();
		
		if (menu == 1) {
			
			int value;
			system ("cls");
			printf ("Input the value: ");
			scanf ("%d", &value);
			getchar();
			bool flag = false;
			
			for (int i = 0; i < SIZE; i++){
				if  (hash[i] == NULL){
					flag = true;
					break;
				}
			}
			
			if (flag) push (value);
			else printf ("\n\nHash Table is Full\n");
			
		}
		
		else if (menu == 2) {
			
			int value;
			system ("cls");
			printf ("Input the value: ");
			scanf ("%d", &value);
			getchar();
			pop (value);
			
			
		}
		
		else if (menu == 3) break;
		
	}
	
	system ("cls");
	
	return 0;
}
