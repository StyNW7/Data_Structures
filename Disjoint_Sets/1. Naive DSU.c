#include <stdio.h>
#define MAX 5

int parent[MAX];

void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
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
    for(int i=0;i<MAX;i++){
        make_set(i);
    }
    printParent();
    union_sets(4, 3);
    printParent();
    union_sets(2, 1);
    printParent();
    union_sets(3, 1);
    printParent();
    union_sets(1, 0);
    printParent();
    return 0;
}

