// All Library needed

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// If any global variable needed

int treeSize = 0;

// Structure of AVL Tree (variable depends on the case)

struct Tree {
	
	int value;
	Tree *left, *right;
	int height;
	
} *root = NULL;

// Create New Node Function

struct Tree* createNewNode (int value){
	
	struct Tree* node = (Tree*) malloc (sizeof(Tree));
	
	node->value = value;
	node->height = NULL;
	node->left = node->right = NULL;
	
	return node;
	
}

// 3 Function helper in AVL Tree

// Function to give the height of a node

int height (Tree* curr){
	
	if (!curr) return 0;
	
	return curr->height;
	
}

// Function to check maximum

int max (int a, int b){
	
	return (a > b) ? a : b;
	
}

// Function to check the balance of the Tree

int getBalance (Tree* node){
	
	if (!node) return 0;
	
	return height(node->left) - height(node->right);
	
}

// Rotation Function (2 rotate type: Left Rotate and Right Rotate)

// Left Rotate Function

struct Tree* leftRotate(Tree* curr){
	
	Tree *currChild = curr->right;
	Tree *currChildChild = currChild->left;
	
	currChild->left = curr;
	curr->right = currChildChild;
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	currChild->height = max (height(currChild->left), height(currChild->right)) + 1;
	
	return currChild;
	
}

// Right Rotate Function

struct Tree* rightRotate(Tree* curr){
	
	Tree *currChild = curr->left;
	Tree *currChildChild = currChild->right;
	
	currChild->right = curr;
	curr->left = currChildChild;
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	currChild->height = max (height(currChild->left), height(currChild->right)) + 1;
	
	return currChild;
	
}

// Core Function in all of data structures

// Push Function in AVL Tree

struct Tree* push (Tree* curr, int value) {

	if (!curr){
		curr = createNewNode(value);
	}
	
	else if (value != curr->value){
		if (value < curr->value) curr->left = push (curr->left, value);
		else curr->right = push (curr->right, value);
	}
	
	// Update Height
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	
	int balance = getBalance(curr);
	
	// Case to Rotate
	
	// LL
	
	if (balance > 1 && value < curr->left->value){
		return rightRotate(curr);
	}
	
	// RR
	
	if (balance < -1 && value > curr->right->value){
		return leftRotate(curr);
	}
	
	// LR
	
	if (balance > 1 && value > curr->left->value){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	
	// RL
	
	if (balance < -1 && value < curr->right->value){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;

}

// Function to check the maximum and minimum

// Recursively

//struct Tree* findMax (Tree* curr){
//	
//	if (curr == NULL) return NULL;
//	if (curr->right == NULL) return curr;
//	
//	return findMax (curr->right);
//	
//}
//
//struct Tree* findMin (Tree* curr){
//	
//	if (curr == NULL) return NULL;
//	if (curr->left == NULL) return curr;
//	
//	return findMin (curr->left);
//	
//}


// I prefer to use while loop :D


struct Tree* findMax (Tree* curr){
	
	while (curr->right != NULL) curr = curr->right;
	return curr;
	
}

struct Tree* findMin (Tree* curr){
	
	while (curr->left != NULL) curr = curr->left;
	return curr;
	
}

// Pop Function

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
	
	// Update Height
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	
	int balance = getBalance(curr);
	
	// Case to Rotate
	
	// LL
	
	if (balance > 1 && getBalance(curr->left) >= 0){
		return rightRotate(curr);
	}
	
	// RR
	
	if (balance < -1 && getBalance(curr->right) < 0){
		return leftRotate(curr);
	}
	
	// LR
	
	if (balance > 1 && getBalance(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	
	// RL
	
	if (balance < -1 && getBalance(curr->right) >= 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;
	
}


// Search Function


struct Tree* search (Tree *curr, int value){
	
	// Not Found
	
	if (curr == NULL){
		printf ("Value NOT found in the AVL Tree!\n\n");
		return NULL;
	}
	
	// Searching to the right
	
	else if (value > curr->value){
		curr->right = search (curr->right, value);
	}
	
	// Seaeching to the left
	
	else if (value < curr->value){
		curr->left = search (curr->left, value);
	}
	
	// Found case
	
	else if (value == curr->value){
		printf ("Value found in the AVL Tree!\n\n");
		return curr;
	}
	
	return curr;
	
}


// Print Function

// In Order Print

void view (Tree* curr){
	
	if (!curr) return;
	
	if (curr->left != NULL) view (curr->left);
	printf ("%d ", curr->value);
	
	if (curr->right != NULL) view (curr->right);
	
}

// Pre Order Print (AVL Tree using this type of printing)

void preOrder (Tree* curr){
	
	if (!curr) return;
	
	printf ("%d ", curr->value);
	if (curr->left != NULL) preOrder (curr->left);
	
	if (curr->right != NULL) preOrder (curr->right);
	
}

// Post Order Print

void postOrder (Tree* curr){
	
	if (!curr) return;
	
	if (curr->left != NULL) postOrder (curr->left);
	
	if (curr->right != NULL) postOrder (curr->right);
	
	printf ("%d ", curr->value);
	
}


// Print as Tree Structure (just additional)


void printIndented(Tree* curr, int level) {
    if (curr == NULL) {
        return;
    }

    level++;

    printIndented(curr->right, level);

    for (int i = 0; i < level - 1; i++) {
        printf("    ");
    }
    
//    printf("%d (%d)\n", curr->value, getBalance(curr));
	
	printf("%d\n", curr->value, getBalance(curr));
	
    printIndented(curr->left, level);
}


// Additional


void viewAVLTree(Tree* root) {
	
    if (root == NULL) {
        printf("AVL Tree is empty.\n");
        return;
    }

    printf("AVL Tree (in tree structure):\n\n");
    printIndented(root, 0);
    
}


int totalLeft = 0;
int totalRight = 0;


void counting(struct Tree* curr, bool left, bool right){
	
	if (!curr) return;
	
	if (left) {
		totalLeft += curr->value;
		if (curr->left != NULL) {
			counting(curr->left, left, right);
		}
		if (curr->right != NULL) {
			counting(curr->right, left, right);
		}
	}
	
	if (right) {
		totalRight += curr->value;
		if (curr->right != NULL) {
			counting(curr->right, left, right);
		}
		if (curr->left != NULL) {
			counting(curr->left, left, right);
		}
	}
	
}


int main(){
	
	int input;
	int del;
	
	scanf ("%d %d", &input, &del);
	getchar();
	
	for (int i = 0; i < input; i++){
		int value;
		scanf ("%d", &value);
		getchar();
		root = push (root, value);
	}
	
	for (int i = 0; i < del; i++){
		int value;
		scanf ("%d", &value);
		getchar();
		root = pop (root, value);
	}
	
	if (root){
		if (root->right) counting(root->right, false, true);
		if (root->left) counting(root->left, true, false);
	}
	
	printf ("%d\n", totalRight - totalLeft);
	
	return 0;
	
}
