#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int menu;
	int n = 0;
	int arr[10];
	
	do {
		
		system ("cls");
		
		printf ("Menuuuuuu\n");
		
		if (n == 0 || n == 1) printf ("There is %d data in the array\n", n);
		else printf ("There are %d data in the array\n", n);
		
		puts("---------------");
		puts("1. Push");
		puts("2. Pop");
		puts ("3. View Data");
		puts("4. Exit");
		
		printf ("\n>> ");
		
		scanf ("%d", &menu);
		
		if (menu == 1) {
			
			system ("cls");
			
			printf ("Input value: ");
			scanf ("%d", &arr[n]);
			n++;
			
		}
		
		else if (menu == 2) {
			
			system ("cls");
			
			int del;
			printf ("Input index: ");
			scanf ("%d", &del);
			
			if (n == 0){
				printf ("There is no data yet!\n");
				getchar();
			}
			
			if (del <= n-1 && n != 0){
				
				for (int i = del; i <= n; i++){
					if (del == n) arr[i] = 0;
					else arr[i] = arr[i+1];
				}
				
				n--;
				
			}
			
			else {
				printf ("There is no such data with that index!\n");
				printf ("Press enter to continue...");
				getchar();
				getchar();
			}
			
		}
		
		else if (menu == 3){
			system("cls");
			
			if (n == 0) printf ("No data...\n");
			else {
				for (int i = 0; i < n; i++){
					printf ("%d ", arr[i]);
				}
			}
			printf ("\n\nPress enter to continue...");
			getchar();
			getchar();
			
		}
		
		else system("cls");

	}
	
	while (menu != 4);
	
	printf ("Thanks :))\n");
	
	return 0;
	
}
