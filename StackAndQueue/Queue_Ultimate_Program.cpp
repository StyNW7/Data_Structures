#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Gamemap 2D Array

char gameMap[21][21] = {

	"####################",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#        P         #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"#                  #",
	"####################"

};

// Global Variable

int x = 9, y = 9;
int randX, randY;
int score = 0;

// Queue Structure

struct Queue {
	
	char condition[21];
	char move[11];
	char id[5];
	
	int priority;
	
	Queue *next, *prev;
	
} *head = NULL, *tail = NULL;

// Createnewnode function

struct Queue* createNewNode (char condition[], char move[], char id[], int priority){
	
	struct Queue* node = (Queue*) malloc (sizeof(Queue));
	
	strcpy (node->condition, condition);
	strcpy (node->move, move);
	strcpy (node->id, id);
	
	node->priority = priority;
	
	node->next = node->prev = NULL;
	
	return node;
	
}

// Push function

void push (char condition[], char move[], char id[], int priority){
	
	struct Queue* node = createNewNode(condition, move, id, priority);
	
	if (head == NULL){
		head = tail = node;
	}
	
	else if (head->priority < node->priority){
		node->next = head;
		head->prev = node;
		head = node;
	}
	
	else if (tail->priority > node->priority){
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	
	else {
		
		struct Queue* curr = head;
		
		while (curr && curr->priority >= node->priority){
			curr = curr->next;
		}
		
		if (!curr){
			node->prev = tail;
			tail->next = node;
			tail = node;
			return;
		}
		
		node->next = curr;
		node->prev = curr->prev;
		
		curr->prev->next = node;
		curr->prev = node;
		
	}
	
}

// Action checker and game score function

void actionChecker(){
	
	int loop = 0;
	
	if (head) {
		if (strcmp(head->condition, "low") == 0) loop = 1;
		else if (strcmp(head->condition, "medium") == 0) loop = 2;
		else if (strcmp(head->condition, "high") == 0) loop = 3;
	}
	
	for (int i = 0; i < loop; i++){
		
		int prevX = x;
		int prevY = y;
		
		if (strcmp (head->move, "up") == 0){
		
			if (x-1 >= 1) {
				--x;
				gameMap[prevX][prevY] = ' ';
				gameMap[x][y] = 'P';
			}
			
		}
		
		else if (strcmp (head->move, "down") == 0){
			
			if (x+1 <= 18) {
				++x;
				gameMap[prevX][prevY] = ' ';
				gameMap[x][y] = 'P';
			}
			
		}
		
		else if (strcmp (head->move, "left") == 0){
			
			if (y-1 >= 1) {
				--y;
				gameMap[prevX][prevY] = ' ';
				gameMap[x][y] = 'P';
			}
			
		}
		
		else if (strcmp (head->move, "right") == 0){
			
			if (y+1 <= 18) {
				++y;
				gameMap[prevX][prevY] = ' ';
				gameMap[x][y] = 'P';
			}
			
		}
		
	}
	
	// Game score checker
	
	if (x == randX && y == randY){
		score += (rand() % 10 + 1);
		gameMap[randX][randY] = 'P';
		randX = rand() % 18 + 1;
		randY = rand() % 18 + 1;
		gameMap[randX][randY] = '*';
	}
	
}

// Pop Search function

void popSearch (char id[], bool *found){
	
	if (head == NULL){
		printf ("Queue is empty\n\n");
		printf ("Press enter to continue...");
		getchar();
		return;
	}
	
	else if (head == tail && strcmp(head->id, id) == 0){
		free (head);
		head = tail = NULL;
	}
	
	else if (strcmp(head->id, id) == 0){
		head = head->next;
		free (head->prev);
		head->prev = NULL;
	}
	
	else if (strcmp(tail->id, id) == 0){
		tail = tail->prev;
		free (tail->next);
		tail->next = NULL;
	}
	
	else {
		
		struct Queue* curr = head;
		
		while (curr && strcmp(curr->id, id) != 0){
			curr = curr->next;
		}
		
		if (!curr){
			*found = 0;
			return;
		}
		
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		
		free (curr);
		
	}
	
}

// Print map function

void printMap(){
	
	for (int i = 0; i < 20; i++){
		printf ("%s\n", gameMap[i]);
	}
	
	puts ("\n");
	
}

// View all action function

void viewAction(){
	
	system ("cls");
	
	if (!head){
		printf ("There is no action right now");
		getchar();
		return;
	}
	
	struct Queue* curr = head;
	int num = 1;
	
	printf ("All Action List:\n\n");
	
	while (curr){
		printf ("%d. %s: [%s --> %s]\n", num++, curr->id, curr->move, curr->condition);
		curr = curr->next;
	}
	
	puts ("\n");
	
}

// Create new action

void createAction(){
	
	system ("cls");
	
	char move[11];
	char condition[21];
	char id[5];
	int priority;
	
	do {
		
		printf ("Input a action move [up, down, left, right]: ");
		scanf ("%[^\n]", move);
		getchar ();
		
		if (strcmp(move, "up") == 0 || strcmp(move, "down") == 0 || strcmp(move, "left") == 0 || strcmp(move, "right") == 0) break;
		else printf ("\nInput invalid\n\n");
		
	}
	
	while (true);
	
	do {
		
		printf ("Input a move condition [low, medium, high]: ");
		scanf ("%[^\n]", condition);
		getchar ();
		
		if (strcmp(condition, "low") == 0 || strcmp(condition, "medium") == 0 || strcmp(condition, "high") == 0) break;
		else printf ("\nInput invalid\n\n");
		
	}
	
	while (true);
	
	if (strcmp(condition, "low") == 0){
		priority = 1;
		id[0] = 'L';
	}
	
	else if (strcmp(condition, "medium") == 0){
		priority = 2;
		id[0] = 'M';
	}
	
	else if (strcmp(condition, "high") == 0){
		priority = 3;
		id[0] = 'H';
	}
	
	for (int i = 1; i < 4; i++){
		int temp = rand() % 10;
		id[i] = temp + '0';
	}
	
	push (condition, move, id, priority);
	
	printf ("\nAction created successfully\n\n");
	printf ("Press enter to continue...");
	getchar();
	
}

// Delete an action

void deleteAction(){
	
	system ("cls");
	
	viewAction();
	if (!head) return;
	
	char id[5];
		
	printf ("Input action ID [0 to back]: ");
	scanf ("%[^\n]", id);
	getchar ();
	
	if (strcmp(id, "0") == 0) return;
	
	bool found = 1;
	
	popSearch (id, &found);
	
	if (!found){
		printf ("\nID Invalid!\n\n");
	}
	
	else printf ("\nPop action succedd\n\n");
	
	printf ("Press enter to continue...");
	getchar();
	
}

// Do 1 action

void doAnAction(){
	
	system ("cls");
	
	if (!head) {
		printf ("There is no action right now");
		getchar();
		return;
	}
	
	if (head != tail) {
		
		actionChecker();
	
		head = head->next;
		free (head->prev);
		head->prev = NULL;
		
	}
	
	else {
		actionChecker();
	
		free (head);
		head = tail = NULL;
	}
	
	printf ("Do 1 action completed");
	getchar();
	
}

// Do all action

void doAllAction(){
	
	system ("cls");
	
	if (!head) {
		printf ("There is no action right now");
		getchar();
		return;
	}
	
	while (head){
		
		actionChecker();
		
		if (head == tail){
			free (head);
			head = tail = NULL;
			break;
		}
		
		head = head->next;
		free (head->prev);
		head->prev = NULL;
		
	}
	
	printf ("Do all action completed");
	getchar();
	
}

// Main function

int main(){
	
	srand(time(0));
	
	randX = rand() % 18 + 1;
	randY = rand() % 18 + 1;
	
	gameMap[randX][randY] = '*';
	
	int action;
	
	do {
		
		system ("cls");
		
		printMap();
		
		printf ("xStyNWx's Queue Game :)\n");
		printf ("Score: %d\n", score);
		puts ("-------------------------------\n");
		
		puts ("1. Create an action");
		puts ("2. Delete an action");
		puts ("3. Do an action");
		puts ("4. Do all action");
		puts ("5. View Action");
		puts ("6. Exit\n");
		printf (">> ");
		scanf ("%d", &action); getchar();
		
		if (action == 1) createAction();
		else if (action == 2) deleteAction();
		else if (action == 3) {
			doAnAction();
		}
		
		else if (action == 4) {
			doAllAction();
		}
		
		else if (action == 5){
			viewAction();
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

