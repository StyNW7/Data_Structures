// Import every library that needed on making this program

#include <stdio.h> // Standard C Library
#include <string.h> // For using strlen or strcmp function
#include <stdlib.h> // For using malloc function
#include <windows.h> // For using Sleep function
#include <conio.h> // For using getch
#include <unistd.h> // Using common functions
#include <time.h> // Using srand(time(0))

// Global Variable

const int EDGE_SIZE = 128;
int slangWordSize = 0;
bool update = true;

// Tries Structure

struct Tries {
	
	char character;
	char description[1001];
	char slangWord[101];
	int found;
	
	struct Tries* edge[EDGE_SIZE];
	
} *root = NULL;

// Create the New Node function

struct Tries* createNewNode (char character){
	
	struct Tries* node = (Tries*) malloc (sizeof (Tries));
	
	node->character = character;
	node->found = 0;
	node->slangWord[0] = '\0';
	node->description[0] = '\0';
	
	for (int i = 0; i < EDGE_SIZE; i++){
		node->edge[i] = 0;
	}
	
	return node;
	
}

// Insert a new word in the Tries

void insert(struct Tries* root, char* word, char* description) {
	
    struct Tries* current = root;
    char* tempWord = word;
    
    while (*tempWord != '\0') {
    	
        if (current->edge[(int)*tempWord] == NULL) {
            current->edge[(int)*tempWord] = createNewNode(*tempWord);
        }
        
        current = current->edge[(int)*tempWord];
        tempWord++;
        
    }
    
    if (current->found == 0) update = false;
    
    current->found = 1;
    strcpy (current->slangWord, word);
    strcpy (current->description, description);
    
}

// Function to check whether there is a slang word in the dictionary or not

int hasSlangWords(struct Tries* node) {
	
    if (node == NULL) {
        return 0;
    }

    if (node->found) {
        return 1;
    }

    for (int i = 0; i < EDGE_SIZE; i++) {
        if (node->edge[i] != NULL && hasSlangWords(node->edge[i])) {
            return 1;
        }
    }

    return 0;
    
}

// Traverse the Tries Structure using dfs concept and print all of them recursively

void dfsPrintWords(struct Tries* node, char* buffer, int depth) {
	
    if (node == NULL) {
        return;
    }
    
    if (node->found) {
    	++slangWordSize;
        printf("%d. %s --> %s\n", slangWordSize, node->slangWord, node->description);
    }
    
    for (int i = 0; i < EDGE_SIZE; i++) {
        if (node->edge[i] != NULL) {
            dfsPrintWords(node->edge[i], buffer, depth + 1);
        }
    }
    
}

// Function that print all of the slang words in the dictionary by calling the dfsPrintWords function

void printAllSlangWords(struct Tries* root) {
	
    if (root == NULL) {
        return;
    }
    
    char temp[256];
    temp[0] = '\0';
    
    dfsPrintWords(root, temp, 0);
    
}

// Function that print all of the slang words with starting prefix based on user's input by calling the dfsPrintWords function too

void printSlangWordsWithPrefix (struct Tries* root, char* prefix) {

    struct Tries* current = root;
    char* p = prefix;

    while (*p != '\0') {
    	
        int index = (int)*p;
        if (current->edge[index] == NULL) {
            return;
        }
        
        current = current->edge[index];
        p++;
        
    }

    char temp[256];
    temp[0] = '\0';
    strcpy(temp, prefix);
    
    dfsPrintWords(current, temp, strlen(prefix));
    
}

// Function that search slang word based on user's input and then search in the dictionary

struct Tries* searchSlangWords(struct Tries* node, char* word) {
	
    if (node == NULL) {
        return NULL;
    }

    struct Tries* current = node;

    while (*word != '\0') {
        int index = (int)*word;
        if (current->edge[index] == NULL) {
            return NULL;
        }
        current = current->edge[index];
        word++;
    }

    if (current != NULL && current->found) {
        return current;
    } 
	
	else {
        return NULL;
    }
    
}

// Default Function

void checker(int action);
void exitLogo();
void fullScreen();
int printMenu();
void printLogo();
void printTitle();
void gotoxy(int x, int y);

// Color

void red();
void green();
void yellow();
void blue();
void magenta();
void cyan();
void white();
void reset();
void randomClr();

// Function prototype about the Primary Function in this program

void releaseSlang();
void searchSlang();
void viewPrefixSlang();
void viewAllSlang();

// Main Function of this Program

int main(){
	
	// Global Root Variable
	
	root = createNewNode('\0');
	
	srand(time(0));
	
	fullScreen();
	printLogo();
	
	int action;
	
	do {
		
		slangWordSize = 0;

		action = printMenu();
		
		checker(action);
		
	}
	
	while (action != 15);
	
	return 0;
}

// Function to release or make a new slang word and edit the slang word description if the slang word already exist

void releaseSlang(){
	
	system ("cls");
	
	char slangWord[101];
	char description[1001];
	update = true;
	
	bool flag1 = true, flag2 = false;
	
	do {
		
		flag1 = true, flag2 = false;
		
		printf ("Input a new slang word [Must be more than 1 character and contains no space]: ");
		scanf ("%[^\n]", slangWord); getchar();
		
		if (strlen(slangWord) >= 2) flag1 = false;
		
		for (int i = 0; i < strlen(slangWord); i++){
			if (slangWord[i] == ' '){
				flag2 = true;
				break;
			}
		}
		
		if (flag1 && flag2) printf ("Must be more than 1 character and contains no space!\n\n");
		
		else if (flag1) printf ("Must be more than 1 character!\n\n");
		
		else if (flag2) printf ("Slang word must contains no space!\n\n");
		
	}
	
	while (flag1 || flag2);
	
	do {
		
		int counter = 0;
		
		printf ("Input a new slang word description [Must be more than 2 words]: ");
		scanf ("%[^\n]", description); getchar();
		
		for (int i = 0; i < strlen(description); i++){
			if (description[i] == ' ' && description[i+1] != ' '){
				counter++;
			}
		}
		
		if (counter >= 2) break;
		
		else printf ("Input must be more than 2 words!\n\n");
		
	}
	
	while (true);
	
	insert(root, slangWord, description);
	
	if (update) {
		printf ("\n\nSuccessfully updated a slang word\n\n");
		printf ("Press enter to continue...");
		getchar();
		return;
	}
	
	printf ("\n\nSuccessfully released new slang word\n\n");
	printf ("Press enter to continue...");
	getchar();
	
	return;
	
}

// Function to search a slang word based on the user's input

void searchSlang(){
	
	system ("cls");
	
	if (!hasSlangWords(root)){
		printf ("There is no slang word yet in the dictionary.\n\n");
		printf ("\nPress enter to continue...");
		getchar();
		return;
	}
	
	char slangWord[101];
	
	bool flag1 = true, flag2 = false;
	
	do {
		
		flag1 = true, flag2 = false;
		
		printf ("Input a slang word to be searched [Must be more than 1 character and contains no space]: ");
		scanf ("%[^\n]", slangWord); getchar();
		
		if (strlen(slangWord) >= 2) flag1 = false;
		
		for (int i = 0; i < strlen(slangWord); i++){
			if (slangWord[i] == ' '){
				flag2 = true;
				break;
			}
		}
		
		if (flag1 && flag2) printf ("Must be more than 1 character and contains no space!\n\n");
		
		else if (flag1) printf ("Must be more than 1 character!\n\n");
		
		else if (flag2) printf ("Slang word must contains no space!\n\n");
		
	}
	
	while (flag1 || flag2);
	
	struct Tries *found = searchSlangWords(root, slangWord);
	
	if (found){
		printf("\n\nSlang Word: %s\n", found->slangWord);
		printf ("Description: %s\n", found->description);
	}
	
	else {
		printf ("\nThere is no word \"%s\" in the dictionary.\n", slangWord);
	}
	
	printf ("\nPress enter to continue...");
	getchar();
	
}

// Function to view all slang words based on the prefix given by user

void viewPrefixSlang(){
	
	system ("cls");
	
	if (!hasSlangWords(root)){
		printf ("There is no slang word yet in the dictionary.\n\n");
		printf ("\nPress enter to continue...");
		getchar();
		return;
	}
	
	char prefixWord[101];
	
	printf ("Input a prefix to be searched: ");
	scanf ("%[^\n]", prefixWord); getchar();
	
	struct Tries* current = root;
	const char* p = prefixWord;
	bool prefixWrong = false;
	
	while (*p != '\0') {
    	
        int index = (int)*p;
        if (current->edge[index] == NULL) {
            prefixWrong = true;
            break;
        }
        
        current = current->edge[index];
        p++;
        
    }
	
	if (prefixWrong){
		printf("\nThere is no slang words found with prefix \"%s\" in the dictionary.\n", prefixWord);
	}
	
	else {
		printf ("\nList of all slang words start with \"%s\":\n\n", prefixWord);
		printSlangWordsWithPrefix(root, prefixWord);
	}
	
	printf ("\nPress enter to continue...");
	getchar();
	
}

// Function to print all of the slang words stored in the Tries structure

void viewAllSlang(){
	
	system ("cls");
	
	if (!hasSlangWords(root)){
		printf ("There is no slang word yet in the dictionary.\n");
	}
	
	else {
		printf ("List of all slang words in the dictionary:\n\n");
		printAllSlangWords(root);
	}
	
	printf ("\nPress enter to continue...");
	getchar();
	
}

// Function to check what the user's action

void checker(int action) {
	
	switch (action) {
	
		case 11:
			releaseSlang();
			break;
		case 12:
			searchSlang();
			break;
		case 13:
			viewPrefixSlang();
			break;
		case 14:
			viewAllSlang();
			break;
		case 15:
			exitLogo();
			break;
	
	}
	
}

// Function that print the user's menu and contains logic for the up and down button

int printMenu(){
	
	int y = 11;
	
	do {
		
		system("cls");
		
		printTitle();
		
		printf ("What do you want to do?\n");
		printf ("1. Release a new slang word\n");
		printf ("2. Search a slang word\n");
		printf ("3. View all slang words starting with a certain prefix word\n");
		printf ("4. View all slang words\n");
		printf ("5. Exit\n\n");
		printf (">> ");
		printf ("Alt + Enter to escape the full screen");
		
		if (y == 11){
			gotoxy (29, y);
			printf ("<");
		}
		
		else if (y == 12){
			gotoxy (24, y);
			printf ("<");
		}
		
		else if (y == 13){
			gotoxy (61, y);
			printf ("<");
		}
		
		else if (y == 14){
			gotoxy (25, y);
			printf ("<");
		}
		
		else if (y == 15){
			gotoxy (10, y);
			printf ("<");
		}
		
		gotoxy (0, 22);
		char c = getch();
		
		if (c == 72) {
			if (y > 11) y--;
			else y = 15;
		}
		else if (c == 80){
			if (y < 15) y++;
			else y = 11;
		} 
		else if (c == 13) break;
		
	}
	
	while (1);

	return y;
	
}

// Function to force the Terminal to fullscreen

void fullScreen() {
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

// Print the exit logo when the user choose to exit the program

void exitLogo() {
	
	system("cls");
	
	white();
	printf ("  _______ _                 _        \n");
	printf (" |__   __| |               | |       \n");
	printf ("    | |  | |__   __ _ _ __ | | _____ \n");
	printf ("    | |  | '_ \\ / _` | '_ \\| |/ / __|\n");
	printf ("    | |  | | | | (_| | | | |   <\\__ \\\n");
	printf ("    |_|  |_| |_|\\__,_|_| |_|_|\\_\\___/\n");
	printf ("\n\n");
	
	green();
	printf ("Made By: ");
	char word[] = {"Stanley Nathanael Wijaya - 2702217125\n"};
	
	for (int i = 0; i < strlen(word); i++){
		randomClr();
		printf ("%c", word[i]);
		Sleep(100);
	}
	
	reset();
	
	puts("");
	
}

// Function to random the color

void randomClr(){
	
	int randColor = rand() % 7;
	
	if (randColor == 0) red();
	if (randColor == 1) green();
	if (randColor == 2) yellow();
	if (randColor == 3) blue();
	if (randColor == 4) magenta();
	if (randColor == 5) cyan();
	if (randColor == 6) white();
	
}

// Colors that used in the program

void red(){
	printf ("\033[1;31m");
}

void green(){
	printf ("\033[1;32m");
}

void yellow(){
	printf ("\033[1;33m");
}

void blue(){
	printf ("\033[1;34m");
}

void magenta(){
	printf ("\033[1;35m");
}

void cyan(){
	printf ("\033[1;36m");
}

void white(){
	printf ("\033[1;37m");
}

void reset(){
	printf ("\033[1;0m");
}

// Function to move the cursor based on the x and y coordinates in the CMD

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Print the intro logo

void printLogo(){
	gotoxy(45, 0);
	printf ("  ______    __                          __                     \n"); Sleep(100);
	gotoxy(45, 1);
	printf (" /      \  /  |                        /  |                    \n"); Sleep(100);
	gotoxy(45, 2);
	printf ("/$$$$$$  |_$$ |_     ______   _______  $$ |  ______   __    __ \n"); Sleep(100);
	gotoxy(45, 3);
	printf ("$$ \__$$// $$   |   /      \ /       \ $$ | /      \ /  |  /  |\n"); Sleep(100);
	gotoxy(45, 4);
	printf ("$$      \$$$$$$/    $$$$$$  |$$$$$$$  |$$ |/$$$$$$  |$$ |  $$ |\n"); Sleep(100);
	gotoxy(45, 5);
	printf (" $$$$$$  | $$ | __  /    $$ |$$ |  $$ |$$ |$$    $$ |$$ |  $$ |\n"); Sleep(100);
	gotoxy(45, 6);
	printf ("/  \__$$ | $$ |/  |/$$$$$$$ |$$ |  $$ |$$ |$$$$$$$$/ $$ \__$$ |\n"); Sleep(100);
	gotoxy(45, 7);
	printf ("$$    $$/  $$  $$/ $$    $$ |$$ |  $$ |$$ |$$       |$$    $$ |\n"); Sleep(100);
	gotoxy(45, 8);
	printf (" $$$$$$/    $$$$/   $$$$$$$/ $$/   $$/ $$/  $$$$$$$/  $$$$$$$ |\n"); Sleep(100);
	gotoxy(45, 9);
	printf ("                                                     /  \__$$ |\n"); Sleep(100);
	gotoxy(45, 10);
	printf ("                                                     $$    $$/ \n"); Sleep(100);
	gotoxy(45, 11);
	printf ("                                                      $$$$$$/  \n"); Sleep(1500);
	gotoxy(45, 12);
}

// Print the Title "Boogle" Logo

void printTitle(){

	printf ("  ____                    _      \n");
	printf (" |  _ \\                  | |     \n");
	printf (" | |_) | ___   ___   __ _| | ___ \n");
	printf (" |  _ < / _ \\ / _ \\ / _` | |/ _ \\\n");
	printf (" | |_) | (_) | (_) | (_| | |  __/\n");
	printf (" |____/ \\___/ \\___/ \\__, |_|\\___|\n");
	printf ("                     __/ |     \n");
	printf ("                    |___/        \n");
	printf ("\n\n");
	
}


