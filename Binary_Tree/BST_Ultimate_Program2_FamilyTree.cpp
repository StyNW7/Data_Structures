#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct Tree {
	
	char name[101];
	char gender[11];
	char hobby[101];
	
	int height;
	int weight;
	
	int age;
	
	Tree *left, *right;
	
} *root = NULL;


struct Tree* createNewNode (char name[], char gender[], char hobby[], int height, int weight, int age) {
	
	struct Tree* node = (Tree*) malloc (sizeof(Tree));
	
	strcpy (node->name, name);
	strcpy (node->gender, gender);
	strcpy (node->hobby, hobby);
	
	node->age = age;
	node->height = height;
	node->weight = weight;
	
	node->left = node->right = NULL;
	
	return node;
	
}


struct Tree* insert (struct Tree* curr, char name[], char gender[], char hobby[], int height, int weight, int age){
	
	if (curr == NULL){
		curr = createNewNode(name, gender, hobby, height, weight, age);
	}
	
	else if (curr->age != age){
		
		if (curr->age > age){
			curr->left = insert (curr->left, name, gender, hobby, height, weight, age);
		}
		
		else curr->right = insert (curr->right, name, gender, hobby, height, weight, age);
		
	}
	
	return curr;
	
}


struct Tree* successor(struct Tree* curr){
	
	if (curr == NULL) return NULL;
	
	if (curr->left == NULL) return curr;
	
	return successor(curr->left);
	
}


struct Tree* predecessor(struct Tree* curr){
	
	if (curr == NULL) return NULL;
	
	if (curr->right == NULL) return curr;
	
	return predecessor(curr->right);
	
}


struct Tree* deleteNode (struct Tree* curr, int find, bool *found){
	
	if (curr == NULL){
		printf ("Data not found!\n\n");
		*found = 0;
		return NULL;
	}
	
	else if (curr->age > find){
		curr->left = deleteNode(curr->left, find, found);
	}
	
	else if (curr->age < find){
		curr->right = deleteNode(curr->right, find, found);
	}
	
	else {
		
		if (curr->right == NULL && curr->left == NULL){
			free (curr);
			return NULL;
		}
		
		else if (curr->right == NULL || curr->left == NULL){
			struct Tree* child = (curr->left != NULL) ? curr->left : curr->right;
			free (curr);
			return child;
		}
		
		else {
			
			struct Tree* temp = predecessor(curr->left);
			curr->age = temp->age;
			curr->weight = temp->weight;
			curr->height = temp->height;
			strcpy (curr->name, temp->name);
			strcpy (curr->gender, temp->gender);
			strcpy (curr->hobby, temp->hobby);
			
			curr->left = deleteNode(curr->left, temp->age, found);
			
		}
		
	}
	
}


void printData(struct Tree* curr){
	printf ("Name: %s\n", curr->name);
	printf ("Gender: %s\n", curr->gender);
	printf ("Hobby: %s\n", curr->hobby);
	printf ("Height: %d\n", curr->height);
	printf ("Weight: %d\n", curr->weight);
	printf ("Age: %d\n\n", curr->age);
}


void search (struct Tree* curr, int find){
	
	if (!curr) {
		printf ("Data not found!\n\n");
		return;
	}
	
	else if (curr->age == find){
		printf ("Data found:\n\n");
		printData(curr);
		return;
	}
	
	if (curr->age > find){
		return search (curr->left, find);
	}
	
	else search (curr->right, find);
	
}


int count (struct Tree* curr){
	if (!curr) return 0;
	return (1 + count(curr->left) + count(curr->right));
}


int treeHeight(struct Tree* curr){
	
	if (!curr) return 0;
	
	int leftHeight = treeHeight(curr->left);
	int rightHeight = treeHeight(curr->right);
	
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
	
}


void printInorder(struct Tree* curr){
	
	if (!curr) return;
	
	printInorder(curr->left);
	printData(curr);
	printInorder(curr->right);
	
}


void printPreorder(struct Tree* curr){
	
	if (!curr) return;
	
	printData(curr);
	printPreorder(curr->left);
	printPreorder(curr->right);
	
}


void printPostorder(struct Tree* curr){
	
	if (!curr) return;
	
	printPostorder(curr->left);
	printPostorder(curr->right);
	printData(curr);
	
}


void createNode(){
	
	system ("cls");
	
	char name[101];
	char gender[11];
	char hobby[101];
	int height;
	int weight;
	int age;
	
	do {
		
		printf ("Input name: ");
		scanf ("%[^\n]", name); getchar();
		
		if (strlen(name) >= 1 && strlen(name) <= 20) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input gender: ");
		scanf ("%[^\n]", gender); getchar();
		
		if (strcmp(gender, "male") == 0 || strcmp(gender, "female") == 0) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input hobby: ");
		scanf ("%[^\n]", hobby); getchar();
		
		if (strlen(hobby) >= 1 && strlen(hobby) <= 20) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input height: ");
		scanf ("%d", &height); getchar();
		
		if (height >= 20) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input weight: ");
		scanf ("%d", &weight); getchar();
		
		if (weight >= 5) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input age: ");
		scanf ("%d", &age); getchar();
		
		if (age >= 0) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	root = insert (root, name, gender, hobby, height, weight, age);
	
	printf ("\n\nData input succeedd...");
	getchar();
	
}


void deleteData(){
	
	system ("cls");
	
	if (!root) {
		printf ("There's no data yet...");
		getchar();
		return;
	}
	
	int age;
	
	do {
		
		printf ("Input age: ");
		scanf ("%d", &age); getchar();
		
		if (age >= 0) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	bool found = 1;
	
	root = deleteNode(root, age, &found);
	
	if (!found){
		printf ("Data not found!\n\n");
	}
	
	else {
		printf ("Data deleted successfully\n\n");
	}
	
	printf ("Press enter to continue...");
	getchar();
	
}


void printDetails(){
	
	system ("cls");
	
	printf ("Tree Details\n");
	puts ("---------------------\n");
	
	if (!root) {
		printf ("There's no data yet...");
		getchar();
		return;
	}
	
	puts("Inorder:\n");
	printInorder(root);
	
	puts("Preorder:\n");
	printPreorder(root);
	
	puts("Postorder:\n");
	printPostorder(root);
	
	struct Tree* old = predecessor(root);
	struct Tree* young = successor(root);
	
	printf ("The oldest: %d\n", old->age);
	printf ("The youngest: %d\n\n", young->age);
	
	printf ("Total node: %d\n", count(root));
	printf ("Height of the Tree: %d\n\n", treeHeight(root));
	
	printf ("Press enter to continue..."); getchar();
	
}


void searchNode(){
	
	system ("cls");
	
	if (!root) {
		printf ("There's no data yet...");
		getchar();
		return;
	}
	
	int age;
	
	do {
		
		printf ("Input age: ");
		scanf ("%d", &age); getchar();
		
		if (age >= 0) break;
		else printf ("Input invalid!\n\n");
		
	}
	
	while (true);
	
	search(root, age);
	
}


void printIndented(Tree* curr, int level) {
	
    if (curr == NULL) {
        return;
    }

    level++;

    printIndented(curr->right, level);

    for (int i = 0; i < level - 1; i++) {
        printf("    ");
    }
    
    printf("%s\n", curr->name);

    printIndented(curr->left, level);
    
}


void printTree(Tree* root) {
	
	system ("cls");
	
    if (root == NULL) {
        printf("Tree is empty.\n");
        printf ("\n\nPress enter to continue...");
    	getchar();
        return;
    }

    printf("Binary Search Tree (in tree structure):\n\n");
    printIndented(root, 0);
    
    printf ("\n\nPress enter to continue...");
    getchar();
    
}


int main(){
	
	int action;
	
	do {
		
		system ("cls");
		
		printf ("xStyNWx's Tree Family :)\n");
		puts ("-------------------------------\n");
		
		puts ("1. Add a New Node");
		puts ("2. Delete a Node");
		puts ("3. Print Details");
		puts ("4. Print Tree");
		puts ("5. Search a Node");
		puts ("6. Exit\n");
		printf (">> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) createNode();
		else if (action == 2) deleteData();
		else if (action == 3) {
			printDetails();
		}
		
		else if (action == 4) {
			printTree(root);
		}
		
		else if (action == 5){
			searchNode();
			printf ("Press enter to continue...");
			getchar();
		}
		
		else if (action == 6) break;
		
	}
	
	while (true);
	
	system ("cls");
	printf ("Thank youu :)\n");
	
	return 0;
	
}
