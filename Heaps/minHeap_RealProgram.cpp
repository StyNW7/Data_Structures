#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Heap Data Structure using Min Heap Concept

#define P(i) (i-1)/2
#define L(i) i*2+1
#define R(i) i*2+2


struct heapStructure {
	int taskStatus;
	char taskName[101];
};


struct heapStructure heap[999];
int size = 0;


void swap (struct heapStructure *a, struct heapStructure *b){
	struct heapStructure temp = *a;
	*a = *b;
	*b = temp;
}


struct heapStructure peak(){
	return heap[0];
}


void push (int status, char name[]){
	
	heap[size].taskStatus = status;
	strcpy (heap[size].taskName, name);
	
	int i = size;
	size++;
	
	// UpHeap
	
	while (i > 0 && heap[P(i)].taskStatus > heap[i].taskStatus){
		swap(&heap[P(i)], &heap[i]);
		i = P(i);
	}
	
}


void downHeap(int i){
	
	int largest = i;
	
	int left = L(i);
	int right = R(i);
	
	if (left < size && heap[largest].taskStatus > heap[left].taskStatus){
		largest = left;
	}
	
	if (right < size && heap[largest].taskStatus > heap[right].taskStatus){
		largest = right;
	}
	
	if (i != largest){
		swap(&heap[i], &heap[largest]);
		downHeap(largest);
	}
	
	else return;
	
}


void printHeap(){
	for (int i = 0; i < size; i++){
		printf ("%d ", heap[i]);
	}
	puts("");
}


struct heapStructure extract(){
	
	struct heapStructure maximum = peak();
	
	heap[0] = heap[size-1];
	size--;
	
	downHeap(0);
	
	return maximum;
	
}


int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		for (int i = 0; i < 35; i++) printf ("=");
		puts("");
		printf ("SUNIB Restaurant Task List\n");
		for (int i = 0; i < 35; i++) printf ("=");
		puts("\n");
		
		if (size == 0) printf ("Next Task: Nothing to be done...\n\n");
		else printf ("Next Task: %s\n\n", heap[0].taskName);
		
		printf ("1. Add Task to Task List\n");
		puts ("2. Do Taks");
		puts ("3. Dismiss All Task");
		puts ("0. Exit");
		
		printf ("\nInput Menu Number: ");
		scanf ("%d", &action);
		getchar();
		
		if (action == 1){
			
			system ("cls");
			
			char status[101];
			char name[101];
			int priority = 0;
			
			do {
				
				printf ("Input Task Status [Urgent | Important | Standard]: ");
				scanf ("%[^\n]", status);
				getchar();
				
				if (strcmp(status, "Urgent") == 0) {
					priority = 1;
					break;
				}
				
				else if (strcmp(status, "Important") == 0) {
					priority = 2;
					break;
				}
				
				else if (strcmp(status, "Standard") == 0) {
					priority = 3;
					break;
				}
				
				else printf ("Input invalid!\n");
				
			}
			
			while (true);
			
			do {
				
				printf ("Input Task Name [1 - 100 Characters]: ");
				scanf ("%[^\n]", name);
				getchar();
				
				if (strlen(name) >= 1) break;
				else printf ("Input invalid!\n");
				
			}
			
			while (true);
			
			push (priority, name);
			
			printf ("Input succedd!");
			getchar();
			
		}
		
		else if (action == 2){
			
			system ("cls");
			
			if (size == 0) {
				printf ("There is no value in the heap array\n\n");
			}
			
			else {
				
				struct heapStructure temp = extract();
				char status[101];
				if (temp.taskStatus == 3) strcpy (status, "Standard");
				else if (temp.taskStatus == 2) strcpy (status, "Important");
				else if (temp.taskStatus == 1) strcpy (status, "Urgent");
				
				printf ("%s with status %s has been done\n\n", temp.taskName, status);
				
			}
			
			printf ("Press enter to continue...");
			getchar();
			
		}
		
		else if (action == 3){
			system ("cls");
			if (size > 0) printf ("List of status has been done:\n\n");
			else printf ("No task to be done\n\n");
			while (size > 0){
				struct heapStructure temp = extract();
				char status[101];
				if (temp.taskStatus == 3) strcpy (status, "Standard");
				else if (temp.taskStatus == 2) strcpy (status, "Important");
				else if (temp.taskStatus == 1) strcpy (status, "Urgent");
				
				printf ("%s with status %s has been done\n\n", temp.taskName, status);
			}
			printf ("End of the day!");
			getchar();
		}
		
		else if (action == 0) break;
		
	}
	
	while (true);
	
	system ("cls");
	printf ("Thank youu :)\n");
	
	return 0;
	
}


