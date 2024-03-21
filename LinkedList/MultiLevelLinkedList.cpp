#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Original code based on the input and output from the task given

// Structure of the Data Struct

struct Node {
    char name[50];
    struct Node* next;
    struct Node* subordinate;
};

// creteNode Function

struct Node* createNode(const char* name) {
	
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    if (newNode != NULL) {
        strcpy(newNode->name, name);
        newNode->next = NULL;
        newNode->subordinate = NULL;
    }
    
    return newNode;
    
}

// addSubordinate Function

void addSubordinate(struct Node* manager, const char* subordinateName) {
	
    struct Node* subordinate = createNode(subordinateName);
    if (subordinate != NULL) {
        subordinate->next = manager->subordinate;
        manager->subordinate = subordinate;
    }
    
}

// printSubordinates function for the recursion

void printSubordinates(struct Node* subordinate) {
	
    if (subordinate == NULL) {
    	printf ("NULL");
        return;
    }
    
    printf("%s -> ", subordinate->name);
    printSubordinates(subordinate->next);
    
}

// The printList function which call the recursion function

void printList(struct Node* manager) {
	
    if (manager == NULL) {
        return;
    }
    printf("Subordinate of %s: ", manager->name);
    printSubordinates(manager->subordinate);
    printf("\n");
    
    struct Node* subordinate = manager->subordinate;
    while (subordinate != NULL) {
        printList(subordinate);
        subordinate = subordinate->next;
    }
    
}

// The fireAll function that free all of the organizational hierachy

void fireAll(struct Node** ceoPtr) {
	
    struct Node* current = *ceoPtr;
    if (current == NULL) {
        return;
    }

    fireAll(&(current->subordinate));
    
    fireAll(&(current->next));
    
    free(current);
    
	//	Make all of the value equal to NULL
    *ceoPtr = NULL;
    
}

// main function

int main() {

	struct Node* ceo = createNode ("Frieren");
	
	addSubordinate (ceo, "Eisen");
	addSubordinate (ceo, "Heiter");
	
	struct Node* manager1 = ceo->subordinate;
	addSubordinate (manager1, "Stark");
	
	struct Node* manager2 = ceo->subordinate->next;
	addSubordinate (manager2, "Fern");

    printf("Organizational Hierarchy:\n\n");
    printList(ceo);
    
	//  Need the address to make it NULL
    fireAll(&ceo);
    
	//  Check whether the linked list is empty after calling fireAll function
    printList(ceo);

    return 0;
    
}
