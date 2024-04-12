#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

struct Node{
	char name[20];
}*Array[SIZE];

int count = 0;

struct Node* newNode(char name[]){
	
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	strcpy(newNode->name,name);
	
	return newNode;
	
}

int hashFunction(char *name) {
    
    int sum = 0;
    
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    
    return sum % SIZE;
}

void insert(char name[]){  
 	
    int hashkey = hashFunction(name);
    int point = hashkey;
    
    if (count >= SIZE){   
        printf("The Array is Full");
        return;
    } 
	
	else {
    	while(Array[point] != NULL){
			point++;
			if (point >= SIZE) point = 0;
		}
    }

	count++;
    Array[point] = newNode(name);
    
}

void deleteNode (char name[]){
	
	int hashkey = hashFunction(name);
	int point = hashkey;
	
	do {
		
		if(Array[point] && strcmp(Array[point]->name,name) == 0){
			free (Array[point]);
			Array[point] = NULL;
			count--;
			return;
		}
		
		point++;
		if (point >= SIZE) point = 0;
		
	}
	
	while(point != hashkey);
	
	return;
}


int main(){
	
	// Just an example
	
    insert("John");
    insert("Alice");
    insert("Bob");
    insert("David");
    insert("Eve");

    deleteNode("Bob");

    printf("Array contents:\n");
    
    for (int i = 0; i < SIZE; i++) {
        if (Array[i] != NULL) {
            printf("[%d] %s\n", i, Array[i]->name);
        } else {
            printf("[%d] NULL\n", i);
        }
    }
	
	return 0;
	
}

