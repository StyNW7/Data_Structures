/******************************************************************************

Optional material: Linked-list representation for DSU
Made accordingly to the example in the book. The picture is attached.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct item;

struct tnode{
    int value;
    struct tnode *next;
    struct item *parent;
}*addrNode[MAX]; // Make hashmap array to make find_set operation done in O(1), assuming no duplicate

struct item{
    struct tnode *head, *tail;  
};

void make_set(int v){
    struct item* newSet = (struct item*) malloc(sizeof(struct item));
    newSet->head = (struct tnode*) malloc(sizeof(struct tnode));
    
    // Initialize head and tail
    newSet->tail = newSet->head;
    
    // Save the new set in an array
    addrNode[v] = newSet->head;
 
    // Initialize the new set
    newSet->head->value = v;
    newSet->head->parent = newSet;
    newSet->head->next = NULL;
}

// Just need to access the hashmap addrNode and return the parent: Done in O(1)
struct item* find_set(int key) {
    struct tnode *ptr = addrNode[key];
    return ptr->parent;
}

void union_sets(int x, int y) {
    struct item *a = find_set(x);
    struct item *b = find_set(y);
    
    // Update the parent of all node in b to a
    struct tnode *curr = b->head;
    while (curr != NULL)
    {
        curr->parent = a;
        curr = curr->next;
    }
 
    // Join the tail of set a to head of set b, then update the tail of set a to be tail of set b
    a->tail->next = b->head;
    a->tail = b->tail;
 
    free(b);
}

int main()
{
    // Make set of 5
    int n = 5;
    for(int i = 0;i<n;i++)
        make_set(i);
    
    // Different address for every set
    for(int i = 0;i<n;i++)
        printf("Rep of %d: %p\n", i, find_set(i));
    
    // Now, set 2 address will be changed to set 1's
    union_sets(1, 2);
    printf("\n");
    for(int i = 0;i<n;i++)
        printf("Rep of %d: %p\n", i, find_set(i));
    
    // Then, set 4 address will be changed to set 3's
    union_sets(3, 4);
    printf("\n");
    for(int i = 0;i<n;i++)
        printf("Rep of %d: %p\n", i, find_set(i));
    
    // Here, set 4 address (and also set 3's) will change to set 0's
    union_sets(0, 4);
    printf("\n");
    for(int i = 0;i<n;i++)
        printf("Rep of %d: %p\n", i, find_set(i));
    
    return 0;
}

