#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Character {
	
	int damage;
	int level;
	char name[101];
	char job[21];
	
	Character *right, *left;
	
} *root = NULL;


struct Character* createNewNode (char name[], char job[], int damage, int level){
	
	struct Character* node = (Character*) malloc (sizeof(Character));
	
	node->damage = damage;
	node->level = level;
	
	strcpy (node->name, name);
	strcpy  (node->job, job);
	
	node->left = node->right = NULL;
	
	return node;
	
}


struct Character* insert(struct Character* curr, char name[], char job[], int damage, int level){
	
	if (curr == NULL){
		curr = createNewNode(name, job, damage, level);
	}
	
	else if (curr->damage != damage){
		
		if (curr->damage > damage){
			curr->left = insert (curr->left, name, job, damage, level);
		}
		
		else {
			curr->right = insert (curr->right, name, job, damage, level);
		}
		
	}
	
	return curr;
	
}


bool checker(){
	if (root == NULL) return 0;
	else return 1;
}


void printAllInorder(struct Character* curr){
	
	if (curr == NULL) return;
	
	printAllInorder (curr->left);
	printf ("* %-20s | %-15s | Lv. %-5d | Damage: %d\n", curr->name, curr->job, curr->level, curr->damage);
	printAllInorder (curr->right);
	
}


void viewAll(){
	
	system ("cls");
	
	printf ("Character List:\n\n");
	
	if (checker() == 0) {
		printf ("There is no data yet...\n\n");
	}
	
	else {
		
		printAllInorder (root);
		
	}
	
	printf ("\nPress enter to continue...");
	getchar();
	
}


void addCharacter(){
	
	system ("cls");
	
	char name[101];
	char job[21];
	int level;
	
	bool flag1 = true;
	
	do {
		
		flag1 = true;
		printf ("Input character's name [3 - 20][non space]: ");
		scanf ("%[^\n]", name); getchar();
		
		for (int i = 0; i < strlen(name); i++){
			if (name[i] == ' ') {
				flag1 = false;
				break;
			}
		}
		
		if (flag1 && strlen (name) >= 3 && strlen(name) <= 20) break;
		else printf ("Input invalid\n\n");
		
	}
	
	while (true);
	
	do {

		printf ("Input character's job [figher/rogue/mage]: ");
		scanf ("%[^\n]", job); getchar();
		
		if (strcmp(job, "fighter") == 0 || strcmp(job, "rogue") == 0 || strcmp(job, "mage") == 0) break;
		else printf ("Input invalid\n\n");
		
	}
	
	while (true);
	
	do {

		printf ("Input character's level [1 - 105]: ");
		scanf ("%d", &level); getchar();
		
		if (level >= 1 && level <= 105) break;
		else printf ("Input invalid\n\n");
		
	}
	
	while (true);
	
	int damage;
	
	if (strcmp(job, "fighter") == 0) {
		damage = level + (rand() % 50);
	}
	
	else if (strcmp(job, "rogue") == 0) {
		damage = level + (rand() % 25);
	}
	
	else if (strcmp(job, "mage") == 0) {
		damage = level + (rand() % 75);
	}
	
	root = insert (root, name, job, damage, level);
	
	printf ("\nAdd New Character Success...");
	getchar();
	
}

void printInorder(struct Character* curr){
	
	if (curr == NULL) return;
	
	printInorder (curr->left);
	printf ("%d ", curr->damage);
	printInorder (curr->right);
	
}

void printPreorder(struct Character* curr){
	
	if (curr == NULL) return;
	
	printf ("%d ", curr->damage);
	printPreorder (curr->left);
	printPreorder (curr->right);
	
}

void printPostorder(struct Character* curr){
	
	if (curr == NULL) return;
	
	printPostorder (curr->left);
	printPostorder (curr->right);
	printf ("%d ", curr->damage);
	
}

void printOrder(){
	
	system ("cls");
	
	printf ("Print By Order (Based on Damage)");
	printf ("\n---------------------------------------\n\n");
	
	printf ("Inorder: ");
	if (root == NULL) printf ("There's no data yet");
	else printInorder(root);
	puts("");
	printf ("Preorder: ");
	if (root == NULL) printf ("There's no data yet");
	else printPreorder(root);
	puts("");
	printf ("Postorder: ");
	if (root == NULL) printf ("There's no data yet");
	else printPostorder(root);
	puts("");
	
	printf ("\nPress enter to continue...");
	getchar();
	
}


struct Character* popAll(struct Character* curr){
	
	if (curr == NULL){
		return NULL;
	}
	
	curr->left = popAll(curr->left);
	curr->right = popAll(curr->right);
	free(curr);
	return NULL;
	
}


int main(){
	
	srand(time(0));
	
	int action;
	
	do {
		
		system ("cls");
		
		printf ("Blue Luna Online\n");
		printf  ("-------------------------\n\n");
		
		puts ("1. View All Characters");
		puts ("2. Add New Character");
		puts ("3. Inorder, Preorder, Postorder Character's damage");
		puts ("4. Exit and Popall\n");
		
		printf (">> ");
		scanf ("%d", &action);
		getchar();
		
		if (action == 1) viewAll();
		else if (action == 2) addCharacter();
		else  if (action == 3) printOrder();
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

