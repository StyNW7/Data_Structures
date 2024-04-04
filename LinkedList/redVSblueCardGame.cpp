#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Card1 {
	
	char cards[5];
	Card1 *next, *prev;
	
} *card1Head = NULL, *card1Tail = NULL;


struct Card2 {
	
	char cards[5];
	Card2 *next, *prev;
	
} *card2Head = NULL, *card2Tail = NULL;


struct Card1* createNewNode (char cards[]){
	
	struct Card1* node = (struct Card1*) malloc (sizeof (struct Card1));
	
	strcpy (node->cards, cards);
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


struct Card2* createNewNode2 (char cards[]){
	
	struct Card2* node = (struct Card2*) malloc (sizeof (struct Card2));
	
	strcpy (node->cards, cards);
	
	node->next = NULL;
	node->prev = NULL;
	
	return node;
	
}


void pushAll1 (char card[]){
	
	Card1 *node = createNewNode (card);
	
	if (card1Head == NULL) {
		card1Head = card1Tail = node;
		node->next = node->prev = NULL;
	}
	
	// Push Tail
	
	else {
		
		card1Tail->next = node;
		node->prev = card1Tail;
		card1Tail = node;
		
	}
	
}

void pushAll2 (char card[]){
	
	Card2 *node = createNewNode2 (card);
	
	if (card2Head == NULL) {
		card2Head = card2Tail = node;
		node->next = node->prev = NULL;
	}
	
	// Push Tail
	
	else {
		
		card2Tail->next = node;
		node->prev = card2Tail;
		card2Tail = node;
		
	}
	
}


void pop1 (char card[]){
	
	//	Only 1 Data
	
	if (card1Head == card1Tail){
		free (card1Head);
		card1Head = card1Tail = NULL;
		return;
	}
	
	//	Pop Head
	
	if (strcmp(card1Head->cards, card) == 0){
		
		card1Head = card1Head->next;
		free (card1Head->prev);
		card1Head->prev = NULL;
		
	}
	
	//	Pop Tail
	
	else if (strcmp(card1Tail->cards, card) == 0){
		
		card1Tail = card1Tail->prev;
		free (card1Tail->next);
		card1Tail->next = NULL;
		
	}
	
	//	Pop Mid
	
	else {
		
		Card1 *curr = card1Head;
		
		while (curr && strcmp (curr->cards, card) != 0){
			
			curr = curr->next;
			
		}
		
		if (!curr){
			printf ("ID not found!\n");
			getchar();
		}
		
		else {
			Card1 *a = curr->prev;
			Card1 *del = curr;
			Card1 *b = del->next;
			
			a->next = b;
			b->prev = a;
			
			free (del);
		}

	}
	
}


void pop2 (char card[]){
	
	//	Only 1 Data
	
	if (card2Head == card2Tail){
		free (card2Head);
		card2Head = card2Tail = NULL;
		return;
	}
	
	//	Pop Head
	
	if (strcmp(card2Head->cards, card) == 0){
		
		card2Head = card2Head->next;
		free (card2Head->prev);
		card2Head->prev = NULL;
		
	}
	
	//	Pop Tail
	
	else if (strcmp(card2Tail->cards, card) == 0){
		
		card2Tail = card2Tail->prev;
		free (card2Tail->next);
		card2Tail->next = NULL;
		
	}
	
	//	Pop Mid
	
	else {
		
		Card2 *curr = card2Head;
		
		while (curr && strcmp (curr->cards, card) != 0){
			
			curr = curr->next;
			
		}
		
		if (!curr){
			printf ("ID not found!\n");
			getchar();
		}
		
		else {
			Card2 *a = curr->prev;
			Card2 *del = curr;
			Card2 *b = del->next;
			
			a->next = b;
			b->prev = a;
			
			free (del);
		}

	}
	
}


int main(){
	
	// Assumption no input validation
	
	srand(time(0));
	
	int card1Size = 0;
	int card2Size = 0;
	
	char cards[21][5] = {"0R", "1R", "2R", "3R", "4R", "5R", "6R", "7R", "8R", "9R", "0B", "1B", "2B", "3B", "4B", "5B", "6B", "7B", "8B", "9B"};
	
	char player1[8][5] = {""};
	char player2[8][5] = {""};
	bool flag = false;
	
	do {
		
		int index1 = 0;
		
        while (true) {
        	
            int random = rand() % 20;
            
            if (cards[random][0] != '-' && card1Size < 7) {
                strcpy(player1[index1], cards[random]);
                ++card1Size;
                cards[random][0] = '-';
                index1++;
            }

            if (card1Size == 7) break;
                
        }

        int index2 = 0;
        
        while (true) {
        	
            int random = rand() % 20;
            if (cards[random][0] != '-' && card2Size < 7) {
                strcpy(player2[index2], cards[random]);
                ++card2Size;
                cards[random][0] = '-';
                index2++;
            }

            if (card2Size == 7) {
                flag = true;
                break;
            }
        }
		
	}
	
	while (!flag);
	
	for (int i = 0; i < 7; i++){
		pushAll1 (player1[i]);
		pushAll2 (player2[i]);
	}
	
	Card1 *curr = card1Head;
	
	printf ("Player 1 Cards:\n");
	
	while (curr != NULL) {
		printf ("%s", curr->cards);
		if (curr->next != NULL) printf (" <-> ");
		curr = curr->next;
	}
	
	puts("");
	
	char temp[5];
	printf ("\n\nEnter first card: ");
	scanf ("%s", temp); getchar();
	
	pop1 (temp);
	
	curr = card1Head;
	
	printf ("Player 1 Cards:\n");
	
	while (curr != NULL) {
		printf ("%s", curr->cards);
		if (curr->next != NULL) printf (" <-> ");
		curr = curr->next;
	}
	
	printf ("\n\nEnter second card: ");
	scanf ("%s", temp); getchar();
	
	pop1 (temp);
	
	curr = card1Head;
	
	printf ("Player 1 Cards:\n");
	
	while (curr != NULL) {
		printf ("%s", curr->cards);
		if (curr->next != NULL) printf (" <-> ");
		curr = curr->next;
	}
	
	Card2 *curr2 = card2Head;
	
	printf ("\n\nPlayer 2 Cards:\n");
	
	while (curr2 != NULL) {
		printf ("%s", curr2->cards);
		if (curr2->next != NULL) printf (" <-> ");
		curr2 = curr2->next;
	}
	
	printf ("\n\nEnter first card: ");
	scanf ("%s", temp); getchar();
	
	pop2 (temp);
	
	curr2 = card2Head;
	
	printf ("\n\nPlayer 2 Cards:\n");
	
	while (curr2 != NULL) {
		printf ("%s", curr2->cards);
		if (curr2->next != NULL) printf (" <-> ");
		curr2 = curr2->next;
	}
	
	printf ("\n\nEnter second card: ");
	scanf ("%s", temp); getchar();
	
	pop2 (temp);
	
	curr2 = card2Head;
	

	
	system ("cls");
	
	curr = card1Head;
	
	printf ("Player 1 Cards:\n");
	
	while (curr != NULL) {
		printf ("%s", curr->cards);
		if (curr->next != NULL) printf (" <-> ");
		curr = curr->next;
	}
	
	printf ("\n\nPlayer 2 Cards:\n");
	
	curr2 = card2Head;
	
	while (curr2 != NULL) {
		printf ("%s", curr2->cards);
		if (curr2->next != NULL) printf (" <-> ");
		curr2 = curr2->next;
	}
	
	int point1 = 0, point2 = 0;
	curr = card1Head;
	curr2 = card2Head;
	
	for (int i = 0; i < 5; i++){
		
		if (strcmp(curr->cards, curr2->cards) > 0) point1++;
		else point2++;
		
		curr = curr->next;
		curr2 = curr2->next;
	}
	
	printf ("\n\nPoint:\n");
	printf ("Point Player 1: %d\n", point1);
	printf ("Point Player 2: %d\n", point2);
	
	if (point1 > point2) printf ("\n\nPlayer 1 Wins");
	else printf ("\n\nPlayer 2 Wins");
	
	return 0;
	
}

