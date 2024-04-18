#include <stdio.h>

// Basic Pointer Program

int main(){
	
	// Variable
	
	int a = 10;
	
	// Pointer b has address of variable a
	
	int *b = &a;
	
	// Double Pointer c has address of variable b which is then can access address of variable a
	
	int **c = &b;
	
	// Print each variable address
	
	printf ("%d\n", &a);
	printf ("%d\n", &b);
	printf ("%d\n", &c);
	
	// a = 10
	
	printf ("%d\n", a);
	
	a = 15;
	
	// *b will be 15 because the value of a change to 15
	
	printf ("%d\n", *b);
	
	a = 20;
	
	// **c will be 20 because the value of a change to 20

	printf ("%d\n", **c);
	
	return 0;
	
}
