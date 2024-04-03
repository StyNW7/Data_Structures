#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct queue1{
	
	int onlineID;
	
	struct queue1 *next, *prev;
	
} *head1 = NULL, *tail1 = NULL;


struct queue2{
	
	int onsiteID;
	
	struct queue2 *next, *prev;
	
} *head2 = NULL, *tail2 = NULL;


struct queue1* createQueue1 (int id){
	
	struct queue1* node = (queue1*) malloc (sizeof(queue1));
	
	node->onlineID = id;
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


struct queue2* createQueue2 (int id){
	
	struct queue2* node = (queue2*) malloc (sizeof(queue2));
	
	node->onsiteID = id;
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


void push (int id, int category){
	
	if (category == 1){
		
		struct queue1* node = createQueue1 (id);
		
		if (head1 == NULL){
			head1 = tail1 = node;
		}
		
		else {
			tail1->next = node;
			node->prev = tail1;
			tail1 = node;
		}
		
	}
	
	else {
		
		struct queue2* node = createQueue2 (id);
		
		if (head2 == NULL){
			head2 = tail2 = node;
		}
		
		else {
			tail2->next = node;
			node->prev = tail2;
			tail2 = node;
		}
		
	}
	
}


void pop (int id, int category){
	
	if (category == 1){
		
		if (head1 == NULL){
			return;
		}
		
		else if (head1->onlineID == id){
			head1 = head1->next;
			free (head1->prev);
			head1->prev = NULL;
		}
		
		else if (tail1->onlineID == id) {
			tail1 = tail1->prev;
			free (tail1->next);
			tail1->next = NULL;
		}
		
		else {
			
			struct queue1* curr = head1;
			
			while (curr && curr->onlineID != id){
				curr = curr->next;
			}
			
			if (!curr) return;
			else {
				
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				
				free (curr);
				curr = NULL;
				
			}
			
		}
		
	}
	
	else {
		
		if (head2 == NULL){
			return;
		}
		
		else if (head2->onsiteID == id){
			head2 = head2->next;
			free (head2->prev);
			head2->prev = NULL;
		}
		
		else if (tail2->onsiteID == id) {
			tail2 = tail2->prev;
			free (tail2->next);
			tail2->next = NULL;
		}
		
		else {
			
			struct queue2* curr = head2;
			
			while (curr && curr->onsiteID != id){
				curr = curr->next;
			}
			
			if (!curr) return;
			else {
				
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				
				free (curr);
				curr = NULL;
				
			}
			
		}
		
	}
	
}


void printAll (){
	
	struct queue1* curr1 = head1;
	struct queue2* curr2 = head2;
	
	while (curr1 || curr2){
		
		if (curr1){
			printf ("%d ", curr1->onlineID);
			curr1 = curr1->next;
		}
		
		if (curr2){
			printf ("%d ", curr2->onsiteID);
			curr2 = curr2->next;
		}
		
	}
	
}


int main(){
	
	int onlineSize, onsiteSize, delSize;
	scanf ("%d %d", &onlineSize, &onsiteSize);
	
	for (int i = 0; i < onlineSize; i++){
		int temp;
		scanf ("%d", &temp);
		push (temp, 1);
	}
	
	
	for (int i = 0; i < onsiteSize; i++){
		int temp;
		scanf ("%d", &temp);
		push (temp, 2);
	}
	
	scanf ("%d", &delSize);
	
	for (int i = 0; i < delSize; i++){
		
		// Id is unique
		
		int temp;
		scanf ("%d", &temp);
		pop (temp, 1);
		pop (temp, 2);
		
	}
	
	printAll();
	
	return 0;
}

