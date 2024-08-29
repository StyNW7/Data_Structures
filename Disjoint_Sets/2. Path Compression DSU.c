#include <stdio.h>
#define MAX 9

int parent[MAX];

void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    // Simple Modification:
    // Find the representative of the set (root vertex), 
    // and then in the process of recursive, 
    // the visited nodes are attached directly to the representative.
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

void printParent(){
    for(int i=0;i<MAX;i++){
        printf("%d ", parent[i]);
    }
    printf("\n");
}

int main()
{
    // First, make set
    for(int i=0;i<MAX;i++){
        make_set(i);
    }
    // Make some unions according to the slide
    union_sets(5, 7);
    union_sets(6, 8);
    union_sets(3, 5);
    union_sets(3, 6);
    union_sets(2, 3);
    union_sets(2, 4);
    union_sets(1, 2);
    printParent();
    // Do a path compression by calling find_set function
    find_set(7);
    // The parrent array will be different as the path to the node will be compressed: 
    // Each node in the path will have the representative as parent
    printParent();
    return 0;
}

