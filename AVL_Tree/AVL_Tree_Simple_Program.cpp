#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Tree {
	
	int value;
	Tree *left, *right;
	int height;
	
} *root = NULL;


struct Tree* createNewNode (int value){
	
	struct Tree* node = (Tree*) malloc (sizeof(Tree));
	
	node->value = value;
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
	printf ("%d ", curr->value);
	
	if (curr->right != NULL) view (curr->right);
	
}

// Pre Order

void preOrder (Tree* curr){
	
	if (!curr) return;
	
	printf ("%d ", curr->value);
	if (curr->left != NULL) preOrder (curr->left);
	
	if (curr->right != NULL) preOrder (curr->right);
	
}

// Post Order

void postOrder (Tree* curr){
	
	if (!curr) return;
	
	if (curr->left != NULL) postOrder (curr->left);
	
	if (curr->right != NULL) postOrder (curr->right);
	
	printf ("%d ", curr->value);
	
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
    
//    printf("%d (%d)\n", curr->value, getBalance(curr));
	
	printf("%d\n", curr->value, getBalance(curr));
	
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


int treeSize = 0;


int main(){
	
	char cmd[10];
	
	while (true){
		
		system ("cls");
		
		printf ("There is %d data right now!\n", treeSize);
		
		printf ("Current Tree: "); preOrder (root); puts("");
		
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
			preOrder (root);
			
			int size;
			
			do {
				printf ("\nInput how many data you want to delete: ");
				scanf ("%d", &size);
			}
			
			while (size > treeSize);
			
			for (int i = 0; i < size; i++){
				
				system ("cls");
			
				printf ("Current Data:\n");
				preOrder (root);
				
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
			
			else viewAVLTree (root);
			
			printf ("\n\nPress enter to continue..."); getchar();
			
		}
		
		else if (strcmpi (cmd, "search") == 0){
			
			int value;
			printf ("Input what value do you want to search: ");
			scanf ("%d", &value); getchar();
			
//			root = search (root, value);
			
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

