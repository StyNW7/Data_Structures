#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX];
int rank[MAX];

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    if (a != b) {
        if (rank[a] < rank[b]) {
            parent[a] = b;
        } 
		
		else if (rank[a] > rank[b]) {
            parent[b] = a;
        } 
		
		else {
            parent[b] = a;
            rank[a]++;
        }
    }
}

int main() {
	
    int location, path;
    scanf("%d %d", &location, &path);

    for (int i = 0; i < location; i++) {
        make_set(i);
    }

    int cycle_detected = 0;

    for (int i = 0; i < path; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        if (find_set(a) == find_set(b)) {
            cycle_detected = 1;
        }
		
		else {
            union_sets(a, b);
        }
    }

    if (cycle_detected) {
        printf("Cycle detected\n");
    } 
	
	else {
        printf("Perfect plan\n");
    }

    return 0;
}

