#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Game {
	
	char name[101];
	int rating;
	
	Game *left, *right;
	
} *root = NULL;


struct Game* createNewNode (char name[], int rate){
	
	struct Game* node = (Game*) malloc (sizeof(Game));
	
	strcpy(node->name, name);
	node->rating = rate;
	
	node->left = node->right = NULL;
	
	return node;
	
}


struct Game* insert (struct Game* curr, char name[], int rate){
	
	if (curr == NULL){
		return createNewNode(name, rate);
	}
	
	if (curr && strcmp(curr->name, name) == 0){
		curr->rating = rate;
		return curr;
	}
	
	else if (strcmp(curr->name, name) != 0){
		
		if (strcmp(curr->name, name) > 0){
			curr->left = insert (curr->left, name, rate);
		}
		
		else curr->right = insert (curr->right, name, rate);
		
	}
	
	return curr;
	
}


struct Game* predecessor (struct Game* curr){
	
	if (!curr) return NULL;
	
	if (curr->right == NULL) return curr;
	return predecessor (curr->right);
	
}


struct Game* pop (struct Game* curr, char name[], bool *found){
	
	if (curr == NULL) {
		printf ("\n%s not found!\n", name);
		*found = 0;
		getchar();
		return NULL;
	}
	
	else if (strcmp(curr->name, name) > 0){
		curr->left = pop (curr->left, name, found);
	}
	
	else if (strcmp(curr->name, name) < 0){
		curr->right = pop (curr->right, name, found);
	}
	
	else {
		
		// No child
		
		if (curr->left == NULL && curr->right == NULL){
			free (curr);
			return NULL;
		}
		
		// 1 chilld
		
		else if (curr->left == NULL || curr->right == NULL){
			struct Game* child = (curr->left != NULL) ? curr->left : curr->right;
			
			free (curr);
			return child;
		}
		
		// 2 child with predecessor
		
		else {
			
			struct Game* temp = predecessor(curr->left);
			strcpy (curr->name, temp->name);
			curr->rating = temp->rating;
			
			curr->left = pop (curr->left, temp->name, found);
			
		}
		
	}
	
}


void printInorder(struct Game* curr){
	
	if (!curr) return;
	
	printInorder(curr->right);
	printf ("[%s --> %d]\n", curr->name, curr->rating);
	printInorder(curr->left);
	
}


void printPreorder(struct Game* curr){
	
	if (!curr) return;
	
	printf ("[%s --> %d]\n", curr->name, curr->rating);
	printPreorder(curr->right);
	printPreorder(curr->left);
	
}


void printPostorder(struct Game* curr){
	
	if (!curr) return;
	
	printPostorder(curr->right);
	printPostorder(curr->left);
	printf ("[%s --> %d]\n", curr->name, curr->rating);
	
}


void viewAll(){
	
	system ("cls");
	
	printf ("Inorder:\n\n");
	printInorder(root);
	puts("\n");
	
	printf ("Preorder:\n\n");
	printPreorder(root);
	puts("\n");
	
	printf ("Postorder:\n\n");
	printPostorder(root);
	puts("\n");
	
	printf ("Press enter to continue...");
	getchar();
	
}


struct Game* popAll(struct Game* curr){
	
	if (curr == NULL) return NULL;
	
	popAll(curr->left);
	popAll(curr->right);
	free (curr);
	return NULL;
	
}


void addGame(){
	
	system ("cls");
	
	char name[101];
	int rate;
	
	do {
		
		printf ("Input game name: ");
		scanf ("%[^\n]", name); getchar();
		
		if (strlen(name) >= 1 && strlen(name) <= 100) break;
		else printf ("Input invalid\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input game rate: ");
		scanf ("%d", &rate); getchar();
		
		if (rate >= 1 && rate <= 10) break;
		else printf ("Input invalid\n\n");
		
	}
	
	while (true);
	
	root = insert (root, name, rate);
	
	printf ("\n\nAdd new game succedd...");
	getchar();
	
}


void deleteGame(){
	
	system ("cls");
	
	char name[101];
	int rate;
	
	do {
		
		printf ("Input game name: ");
		scanf ("%[^\n]", name); getchar();
		
		if (strlen(name) >= 1 && strlen(name) <= 100) break;
		else printf ("Input invalid\n\n");
		
	}
	
	while (true);
	
	bool found = 1;
	
	root = pop(root, name, &found);
	
	if (found){
		printf ("\n\nDelete game succedd...");
		getchar();
	}
	
}


int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		printf ("xStyNWx's Game'\n");
		printf  ("-------------------------\n\n");
		
		puts ("1. View All");
		puts ("2. Add a New Game");
		puts ("3. Delete a Game");
		puts ("4. Exit and Popall\n");
		
		printf (">> ");
		scanf ("%d", &action);
		getchar();
		
		if (action == 1) viewAll();
		else if (action == 2) addGame();
		else if (action == 3) deleteGame();
		else if (action == 4) {
			root = popAll(root);
			break;
		}
		
	}
	
	while (true);
	
	system ("cls");
//	viewAll();
	printf ("Thank youu :)\n");
	
	
	return 0;
	
}
