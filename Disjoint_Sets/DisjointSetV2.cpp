#include <stdio.h>

#define MAX 999

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
        } else if (rank[a] > rank[b]) {
            parent[b] = a;
        } else {
            parent[b] = a;
            rank[a]++;
        }
    }
}

int detect_cycle(int edges[][2], int num_edges) {
    
    for (int i = 0; i < MAX; i++) {
        make_set(i);
    }

    for (int i = 0; i < num_edges; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        if (find_set(u) == find_set(v)) {
            return 1;
        }
		
		else {
            union_sets(u, v);
        }
    }
    
    return 0;
}

void print_parent() {
    for (int i = 0; i < MAX; i++) {
        printf("%d ", parent[i]);
    }
    printf("\n");
}

int main() {
	
    int edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 1}};
    int num_edges = sizeof(edges) / sizeof(edges[0]);
    
    int location, path;
	scanf ("%d %d", &location, &path);
	getchar();
	
	for (int i = 0; i < path; i++){
		
		int a, b;
		scanf ("%d %d", &a, &b);
		getchar();
		
		make_set(a);
		make_set(b);
		
		union_sets(a, b);
		
	}

    if (detect_cycle(edges, num_edges)) {
        printf("Cycle detected\n");
    } 
	
	else {
        printf("Perfect plan\n");
    }

    return 0;
}

