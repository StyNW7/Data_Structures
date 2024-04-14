#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int treeSize = 0;

struct Node {
	
	int value;
	
	Node *left, *right;
	
} *root = NULL;


struct Node* createNewNode (int value){
	
	struct Node* node = (Node*) malloc (sizeof(Node));
	
	node->value = value;
	
	node->left = node->right = NULL;
	
	return node;
	
}


struct Node* insert (struct Node* curr, int value){
	
	// Base Case
	
	if (curr == NULL){
		curr = createNewNode(value);
	}
	
	else if (curr->value != value){
		
		if (curr->value > value){
			curr->left = insert (curr->left, value);
		}
		
		else curr->right = insert (curr->right, value);
		
	}
	
	treeSize++;
	
	return curr;
	
}


void printInfix (struct Node* curr) {
	
	if (curr == NULL) return;
	
	printInfix (curr->left);
	printf ("%d ", curr->value);
	printInfix (curr->right);
	
}


void printPrefix (struct Node* curr) {
	
	if (curr == NULL) return;
	
	printf ("%d ", curr->value);
	printPrefix (curr->left);
	printPrefix (curr->right);
	
}


void printPostfix (struct Node* curr){
	
	if (!curr) return;
	
	printPostfix (curr->left);
	printPostfix (curr->right);
	printf ("%d ", curr->value);
	
}


struct Node* findPredecessor (Node* curr){
	
	// Base Case
	
	if (curr == NULL) return NULL;
	if (curr->right == NULL) return curr;
	
	return findPredecessor (curr->right);
	
}


struct Node* findSuccessor (Node* curr){
	
	if (!curr) return NULL;
	
	if (curr->left == NULL) return curr;
	
	return findSuccessor (curr->left);
	
}


struct Node* pop (Node *curr, int value){
	
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
			treeSize--;
			free (curr);
			return NULL;
		}
		
		// 1 Child
		
		else if (curr->left == NULL || curr->right == NULL){
			
//			Node *temp = (curr->left == NULL) ? curr->right : curr->left;
			
			Node *temp;
			
			if (curr->left){
				temp = curr->left;
			}
			
			else {
				temp = curr->right;
			}
			
			free (curr);
			
			treeSize--;
			return temp;
			
		}
		
		// 2 Children
		
		else if (curr->left && curr->right) {
			
			// Search predecessor
			
			Node* temp = findPredecessor (curr->left);
			curr->value = temp->value;
			curr->left = pop (curr->left, temp->value);
			
		}
		
		// 2 Children using Successor
		
		else if (curr->left && curr->right) {
			
			// Search Successor
			
			Node* temp = findSuccessor (curr->right);
			curr->value = temp->value;
			curr->right = pop (curr->right, temp->value);
			
		}
		
	}
	
	treeSize--;
	return curr;
	
}


void search (struct Node* curr, int value){
	
	if (!curr) {
		printf ("%d is not found in the Tree\n\n");
		return;
	}
	
	if (curr->value == value){
		printf ("%d is found in the Tree\n\n");
		return;
	}
	
	if (curr->value > value) return search (curr->left, value);
	
	return search  (curr->right, value);
	
}


int findMin (struct Node* curr){
	
	if (curr == NULL) return 0;
	
	if (curr->left == NULL) return curr->value;
	
	return findMin (curr->left);
	
}


int findMax (struct Node* curr){
	
	if (curr == NULL) return 0;
	
	if (curr->right == NULL) return curr->value;
	
	return findMax (curr->right);
	
}


int count (struct Node* curr){
	
	if (curr == NULL) return 0;
	
	return (1 + count(curr->left) + count(curr->right));
	
}


int maxHeight(struct Node* curr){
	
	if (curr == NULL) return 0;
	
	int leftHeight = maxHeight (curr->left);
	int rightHeight = maxHeight (curr->right);
	
	return (1 + (leftHeight > rightHeight ? leftHeight : rightHeight));
	
}


// Print as Tree Structure


void printIndented(Node* curr, int level) {
	
    if (curr == NULL) {
        return;
    }

    level++;

    printIndented(curr->right, level);

    for (int i = 0; i < level - 1; i++) {
        printf("    ");
    }
    
    printf("%d\n", curr->value);

    printIndented(curr->left, level);
    
}


void viewTree(Node* root) {
	
	system ("cls");
	
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    printf("Binary Search Tree (in tree structure):\n\n");
    printIndented(root, 0);
    
    printf ("\n\nPress enter to continue...");
    getchar();
    
}


void printDetails (){
	
	system ("cls");
	
	printf ("Binary Search Tree Program\n\n");
	
	printf ("Infix Order\n");
	printInfix(root);
	
	puts("\n");
	
	printf ("Prefix Order\n");
	printPrefix(root);
	
	puts("\n");
	
	printf ("Postfix Order\n");
	printPostfix(root);
	
	puts("\n");
	
	printf ("Height: %d\n", maxHeight(root));
	printf ("Count: %d\n", count(root));
	
	printf ("\nMax Value: %d\n", findMax(root));
	printf ("Min Value: %d\n", findMin(root));
	
	printf ("\nPress enter to continue...");
	getchar();
	
}


int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		puts ("Binary Search Tree");
		puts ("---------------------------\n");
		
		printf ("Current Tree (Infix Order):\n");
		if (treeSize <= 0) printf ("There is no node yet...");
		else printInfix(root);
		
		puts ("\n");
		
		puts ("1. Insert");
		puts ("2. Delete");
		puts ("3. View Prefix");
		puts ("4. View Postfix");
		puts ("5. Search");
		puts ("6. View Tree");
		puts ("7. View Details");
		puts ("8. Exit");
		
		printf ("\n>> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) {
			system ("cls");
			int temp;
			printf ("Input a value to insert a new node: ");
			scanf ("%d", &temp); getchar();
			root = insert(root, temp);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 2){
			system ("cls");
			int temp;
			printf ("Input a value to delete: ");
			scanf ("%d", &temp); getchar();
			root = pop (root, temp);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 3){
			system ("cls");
			printf ("Prefix Order:\n\n");
			printPrefix(root);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 4){
			system ("cls");
			printf ("Postfix Order:\n\n");
			printPostfix(root);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 5){
			
			system ("cls");
			
			printf ("Current Tree:\n");
			if (treeSize == 0) printf ("There is no node yet...");
			else printInfix(root);
			
			puts("\n");
			
			int temp;
			printf ("Input a value to search: ");
			scanf ("%d", &temp); getchar();
			search (root, temp);
			
			printf ("\n\nPress enter to continue...");
			getchar();
			
		}
		
		else if (action == 6){
			viewTree(root);
		}
		
		else if (action == 7){
			printDetails();
		}
		
		else if (action == 8){
			break;
		}
		
	}
	
	while (true);
	
	system ("cls");
	printf ("Thank youu...\n");
	
	return 0;
	
}

