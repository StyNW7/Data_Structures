#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// I assume the tree is orederd / sorted by title name

// Global Variable

bool notFound = false;
int treeSize = 1;

// Tree Structure

struct Tree {
	
	char title[101];
	char singer[101];
	char type[51];
	
	Tree *left, *right;
	
	int height;
	
} *root = NULL;

// Createnewnode Function

struct Tree* createNewNode (char title[], char singer[], char type[]){
	
	struct Tree* node = (Tree*) malloc (sizeof(Tree));
	
	strcpy (node->title, title);
	strcpy (node->singer, singer);
	strcpy (node->type, type);
	
	node->height = NULL;
	node->left = node->right = NULL;
	
	return node;
	
}


int height (Tree* curr){
	
	if (!curr) return 0;
	
	return curr->height;
	
}

int max (int a, int b){
	
	return (a > b) ? a : b;
	
}


int getBalance (Tree* node){
	
	if (!node) return 0;
	
	return height(node->left) - height(node->right);
	
}


struct Tree* leftRotate(Tree* curr){
	
	Tree *currChild = curr->right;
	Tree *currChildChild = currChild->left;
	
	currChild->left = curr;
	curr->right = currChildChild;
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	currChild->height = max (height(currChild->left), height(currChild->right)) + 1;
	
	return currChild;
	
}


struct Tree* rightRotate(Tree* curr){
	
	Tree *currChild = curr->left;
	Tree *currChildChild = currChild->right;
	
	currChild->right = curr;
	curr->left = currChildChild;
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	currChild->height = max (height(currChild->left), height(currChild->right)) + 1;
	
	return currChild;
	
}


struct Tree* push (Tree* curr, char title[], char singer[], char type[]) {

	if (!curr){
		curr = createNewNode(title, singer, type);
	}
	
	else if (strcmp(curr->title, title) != 0){
		if (strcmp(curr->title, title) > 0) curr->left = push (curr->left, title, singer, type);
		else curr->right = push (curr->right, title, singer, type);
	}
	
	// Update Height
	
	curr->height = max(height(curr->left), height(curr->right)) + 1;
	
	int balance = getBalance(curr);
	
	// Case to Rotate
	
	// LL
	
	if (balance > 1 && strcmp(curr->left->title, title) > 0){
		return rightRotate(curr);
	}
	
	// RR
	
	if (balance < -1 && strcmp(curr->right->title, title) < 0){
		return leftRotate(curr);
	}
	
	// LR
	
	if (balance > 1 && strcmp(curr->left->title, title) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	
	// RL
	
	if (balance < -1 && strcmp(curr->right->title, title) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr;

}


struct Tree* findMax (Tree* curr){
	
	// Base Case
	
	if (curr == NULL) return NULL;
	if (curr->right == NULL) return curr;
	
	return findMax (curr->right);
	
}


struct Tree* pop (Tree *curr, char title[]){
	
	// Base Case
	
	if (curr == NULL){
		notFound = true;
		return NULL;
	}
	
	else if (strcmp(curr->title, title) < 0){
		curr->right = pop (curr->right, title);
	}
	
	else if (strcmp(curr->title, title) > 0){
		curr->left = pop (curr->left, title);
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
			
			strcpy (curr->title, temp->title);
			strcpy (curr->singer, temp->singer);
			strcpy (curr->type, temp->type);
			
			curr->left = pop (curr->left, temp->title);
			
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

// In Order

void view (Tree* curr){
	
	if (!curr) return;
	
	if (curr->left != NULL) view (curr->left);
	printf ("| %-5d | %-20s | %-15s | %-12s |\n", treeSize++, curr->title, curr->singer, curr->type);
	
	if (curr->right != NULL) view (curr->right);
	
}

// Pre Order

void preOrder (Tree* curr){
	
	if (!curr) return;
	
	printf ("| %-5d | %-20s | %-15s | %-12s |\n", treeSize++, curr->title, curr->singer, curr->type);
	
	if (curr->left != NULL) preOrder (curr->left);
	
	if (curr->right != NULL) preOrder (curr->right);
	
}

// Post Order

void postOrder (Tree* curr){
	
	if (!curr) return;
	
	if (curr->left != NULL) postOrder (curr->left);
	
	if (curr->right != NULL) postOrder (curr->right);
	
	printf ("| %-5d | %-20s | %-15s | %-12s |\n", treeSize++, curr->title, curr->singer, curr->type);
	
}


// Print as Tree Structure


void printIndented(Tree* curr, int level) {
	
    if (curr == NULL) {
        return;
    }

    level++;

    printIndented(curr->right, level);

    for (int i = 0; i < level - 1; i++) {
        printf("    ");
    }
	
	printf ("%s\n", curr->title);
	
    printIndented(curr->left, level);
    
}


void viewAVLTree(Tree* root) {
	
    if (root == NULL) {
        printf("AVL Tree is empty.\n");
        return;
    }

    printf("AVL Tree (in tree structure):\n\n");
    printIndented(root, 0);
    
}


void addMusic(){
	
	system ("cls");
	
	char title[101];
	char singer[101];
	char type[51];
	
	do {
		
		printf ("Input music title [3 - 30 characters]: ");
		scanf ("%[^\n]", title); getchar();
		
		if (strlen(title) >= 3 && strlen(title) <= 30) break;
		else {
			printf ("Input invalid!\n");
		}
		
	}
	
	while (true);
	
	do {
		
		printf ("Input singer's name [3 - 30 characters]: ");
		scanf ("%[^\n]", singer); getchar();
		
		if (strlen(singer) >= 3 && strlen(singer) <= 30) break;
		else {
			printf ("Input invalid!\n");
		}
		
	}
	
	while (true);
	
	do {
		
		printf ("Input music type [pop, jazz, rock]: ");
		scanf ("%[^\n]", type); getchar();
		
		if (strcmp(type, "pop") == 0 || strcmp(type, "jazz") == 0 || strcmp(type, "rock") == 0) break;
		else {
			printf ("Input invalid!\n");
		}
		
	}
	
	while (true);
	
	root = push (root, title, singer, type);
	
	printf ("\nAdded music succedd!\n");
	printf ("Press enter to continue...");
	getchar();
	
}


void deleteMusic(){
	
	system ("cls");
	
	char title[101];
	
	do {
		
		printf ("Input music title [3 - 30 characters]: ");
		scanf ("%[^\n]", title); getchar();
		
		if (strlen(title) >= 3 && strlen(title) <= 30) break;
		else {
			printf ("Input invalid!\n");
		}
		
	}
	
	while (true);
	
	root = pop(root, title);
	
	if (notFound){
		printf ("\nMusic title not found!\n");
		printf ("Press enter to continue...");
		getchar();
		return;
	}
	
	printf ("\nDelete music succedd!\n");
	printf ("Press enter to continue...");
	getchar();
	
}


int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		printf ("Music List (printed in preorder)\n\n");
		for (int i = 0; i < 65; i++) printf ("=");
		puts ("");
		
		printf ("| %-5s | %-20s | %-15s | %-12s |\n", "No.", "Title", "Singer", "Type");
		for (int i = 0; i < 65; i++) printf ("=");
		puts ("");
		
		treeSize = 1;
		
		if (root == NULL) printf ("| %-61s |\n", "AVL Tree is Empty!");
		else preOrder(root);
		
		for (int i = 0; i < 65; i++) printf ("=");
		puts ("\n");
		
		printf ("\Menu\n");
		puts("------------------");
		printf ("1. Add Data\n");
		printf ("2. Delete Data\n");
		printf ("3. View Tree\n");
		printf ("4. Exit\n");
		printf (">> ");
		
		scanf ("%d", &action);
		getchar();
		
		if (action == 1){
			
			addMusic();
			
		}
		
		else if (action == 2){
			
			notFound = false;
			if (root == NULL) {
				system ("cls");
				printf ("AVL Tree is Empty\n\n");
				printf ("Press enter to continue...");
				getchar();
			}
			else deleteMusic();
			
		}
		
		else if (action == 3){
			system ("cls");
			viewAVLTree(root);
			printf ("\n\nPress enter to continue...");
			getchar();
		}
		
		else if (action == 4){
			break;
		}
		
		else {
			printf ("Input Invalid\n");
			printf ("Press enter to continue...");
			getchar();
		}
		
	}
	
	while (true);
	
	system ("cls");
	
	printf ("Thank youu :)\n");
	printf ("\nMade by: Stanley Nathanael Wijaya - 2702217125\n");
	
	return 0;
	
}

