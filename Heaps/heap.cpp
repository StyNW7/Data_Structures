#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define P(i) (i-1)/2
#define L(i) i*2+1
#define R(i) i*2+2


int heap[999];
int size = 0;


void swap (int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}


int peak(){
	return heap[0];
}


void push (int value){
	
	heap[size] = value;
	int i = size;
	size++;
	
	// UpHeap
	
	while (i > 0 && heap[P(i)] < heap[i]){
		swap(&heap[P(i)], &heap[i]);
		i = P(i);
	}
	
}


void downHeap(int i){
	
	int largest = i;
	
	int left = L(i);
	int right = R(i);
	
	if (left < size && heap[largest] < heap[left]){
		largest = left;
	}
	
	if (right < size && heap[largest] < heap[right]){
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


int extract(){
	
	int maximum = peak();
	
	heap[0] = heap[size-1];
	size--;
	
	downHeap(0);
	
	return maximum;
	
}


int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		printf ("1. Push\n");
		puts ("2. Pop");
		puts ("3. Find Max");
		puts ("4. Print Heap");
		puts ("5. Exit");
		
		printf ("\nInput Action: ");
		scanf ("%d", &action);
		getchar();
		
		if (action == 1){
			system ("cls");
			int value;
			printf ("Input value: ");
			scanf ("%d", &value);
			getchar();
			
			push (value);
		}
		
		else if (action == 2){
			system ("cls");
			
			if (size == 0) {
				printf ("There is no value in the heap array\n");
			}
			
			else {
				printf ("Pop succedd\n");
				extract();
			}
			
			printf ("Press enter to continue...");
			getchar();
			
		}
		
		else if (action == 3){
			system ("cls");
			int maximum = peak();
			printf ("Maximum = %d\n", maximum);
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 4){
			system ("cls");
			printHeap();
			printf ("\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 5) break;
		
	}
	
	while (true);
	
	system ("cls");
	printf ("Thank youu :)");
	
	return 0;
	
}


