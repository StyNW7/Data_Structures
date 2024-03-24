#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Tree {
	
	int value;
	Tree *left, *right;
	
} *root = NULL;


int treeSize = 0;


struct Tree* createNewNode (int value){
	
	Tree* node = (Tree*) malloc (sizeof(Tree));
	
	node->value = value;
	node->left = node->right = NULL;
	
	return node;
	
}


struct Tree* search (Tree* curr, int value){
	
	if (curr == NULL) return NULL;
	
	if (value == curr->value) return curr;
	
	if (value < curr->value) return search (curr->left, value);
	
	return search (curr->right, value);
	
}


// InOrder

void view (Tree* curr){
	
	if (curr->left != NULL) view (curr->left);
	printf ("%d ", curr->value);
	
	if (curr->right != NULL) view (curr->right);
	
}


void preOrder (Tree* curr){
	
	printf ("%d ", curr->value);
	if (curr->left != NULL) preOrder (curr->left);
	
	if (curr->right != NULL) preOrder (curr->right);
	
}


void postOrder (Tree* curr){
	
	if (curr->left != NULL) postOrder (curr->left);
	
	if (curr->right != NULL) postOrder (curr->right);
	
	printf ("%d ", curr->value);
	
}


struct Tree* push(Tree *curr, int value){
	
	// Base Case
	
	if (curr == NULL){
		curr = createNewNode(value);
	}
	
	// Recursive Case
	
	else if (curr->value != value){
		
		if (value < curr->value){
			curr->left = push (curr->left, value);
		}
		
		else {
			curr->right = push (curr->right, value);
		}
		
	}
	
	return curr;
	
}


struct Tree* findMax (Tree* curr){
	
	// Base Case
	
	if (curr == NULL) return NULL;
	if (curr->right == NULL) return curr;
	
	return findMax (curr->right);
	
}


struct Tree* pop (Tree *curr, int value){
	
	// Base Case
	
	if (curr == NULL){
		return NULL;
	}
	
	else if (value > curr->value){
		curr->right = pop (curr->right, value);
	}
	
	else if (value < curr->value){
		curr->left = pop (curr->left, value);
	}
	
	else {
		
		// No Child
		
		if (curr->left == NULL && curr->right == NULL){
			free (curr);
			return NULL;
		}
		
		// 1 Child
		
		else if (curr->left == NULL || curr->right == NULL){
			
			Tree *temp;
			
			if (curr->left){
				temp = curr->left;
			}
			
			else {
				temp = curr->right;
			}
			
			free (curr);
			
			return temp;
			
		}
		
		// 2 Children
		
		else if (curr->left && curr->right) {
			
			// Search predecessor
			
			Tree* temp = findMax (curr->left);
			curr->value = temp->value;
			curr->left = pop (curr->left, temp->value);
			
		}
		
	}
	
	return curr;
	
}


int main(){
	
	char cmd[10];
	
	while (true){
		
		system ("cls");
		
		printf ("There is %d data right now!\n", treeSize);
		printf ("Input action: ");
		scanf ("%s", cmd); getchar();
		
		if (strcmpi (cmd, "push") == 0){
			
			system ("cls");
			
			int size;
			int value;
			
			printf ("Input how many number you want to input: ");
			scanf ("%d", &size); getchar();
			
			treeSize += size;
			
			for (int i = 0; i < size; i++){
				
				printf ("Input the %d value: ", i+1);
				scanf ("%d", &value);
				getchar();
				
				root = push (root, value);
				
			}
			
		}
		
		else if (strcmpi (cmd, "pop") == 0){
			
			system ("cls");
			
			printf ("Current Data:\n");
			view (root);
			
			int size;
			
			do {
				printf ("\nInput how many data you want to delete: ");
				scanf ("%d", &size);
			}
			
			while (size > treeSize);
			
			for (int i = 0; i < size; i++){
				
				system ("cls");
			
				printf ("Current Data:\n");
				view (root);
				
				int value;
				
				printf ("\nInput the value that you want to delete: ");
				scanf ("%d", &value);
				
				root = pop (root, value);
				
			}
			
			treeSize -= size;
			
		}
		
		else if (strcmpi (cmd, "view") == 0){
			
			system ("cls");
			
			if (treeSize == 0) printf ("There is no data yet!");
			
			else view (root);
			
			printf ("\n\nPress enter to continue..."); getchar();
			
		}
		
		else if (strcmpi (cmd, "search") == 0){
			
			int value;
			printf ("Input what value do you want to search: ");
			scanf ("%d", &value); getchar();
			
			root = search (root, value);
			
			if (root) printf ("Data  found!\n");
			else printf ("Data not found!\n");
			
			printf ("Press enter to continue..."); getchar();
			
		}
		
		else if (strcmpi (cmd, "exit") == 0){
			break;
		}
		
		else {
			printf ("Input undefined by the system!\n\n");
			printf ("Press enter to continue..."); getchar();
		}
		
	}
	
	return 0;
	
}
