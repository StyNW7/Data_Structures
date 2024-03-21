#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student {
	int id;
	char name[20];
	double score;
} student;

student arr[100];

int n = 0;
int id = 0;

void add (){
	
	system ("cls");
		
	id++;
	
	printf ("Input name: ");
	scanf ("%s", &arr[n].name); getchar();
	
	printf ("Input score: ");
	scanf ("%lf", &arr[n].score); getchar();
	
	n++;
	
}

void deleteData(){
	
	system ("cls");
			
	int del;
	printf ("Input index: ");
	scanf ("%d", &del);
	getchar();
	
	if (n == 0){
		printf ("There is no data yet!\n");
	}
	
	if (del <= n && n != 0){
		
		for (int i = del; i <= n; i++){
			arr[i] = arr[i+1];
		}
		
		n--;
		
	}
	
	else {
		printf ("There is no such data with that index!\n");
		printf ("Press enter to continue...");
		getchar();
	}
	
}

void displayData(){
	
	system("cls");
			
	if (n == 0) {
		printf ("==========================================================\n");
		printf ("| There is no data!                                      |\n");
		printf ("==========================================================\n");
	}
	
	else {
		printf ("==========================================================\n");
		printf ("| %-3s | %-5s | %-30s | %-7s |\n", "No", "ID", "Name", "Score");
		for (int i = 0; i < n; i++){
			printf ("| %-3d | %-5d | %-30s | %-7.2lf |\n", i+1, id, arr[i].name, arr[i].score);
		}
		printf ("==========================================================\n");
	}
	
	printf ("\n\nPress enter to continue...");
	getchar();
	
}

void checker(int menu){
	
	if (menu == 1) add();
	else if (menu == 2) deleteData();
	else if (menu == 3) displayData();
	
}

int main(){
	
	int menu;
	
	do {
		
		system ("cls");
		
		printf ("Menuuuuuu\n");
		
		if (n == 0 || n == 1) printf ("There is %d data in the array\n", n);
		else printf ("There are %d data in the array\n", n);
		
		puts("---------------");
		puts("1. Add Data");
		puts("2. Delete Data");
		puts ("3. Display Data");
		puts("4. Exit");
		
		printf ("\n>> ");
		
		do {
			scanf ("%d", &menu);
			getchar();
		}
		
		while (menu < 1 && menu > 4);
		
		if (menu != 4)checker (menu);
		else break;

	}
	
	while (true);
	
	system ("cls");
	
	printf ("Thanks :))\n");
	
	return 0;

}
