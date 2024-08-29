#include <stdio.h>

#define MAX 999

int parent[MAX];

void make_set(int v){
	parent[v] = v;
	return;
}

int find_set(int v){
	if (v == parent[v]) return v;
	return find_set(parent[v]);
}

void union_sets(int a, int b){
	a = find_set(a);
	b = find_set(b);
	
	if (a != b) parent[b] = a;
}

void print_parent(){
	for (int i = 0; i < MAX; i++){
		printf ("%d ", parent[i]);
	}
	printf ("\n");
}

int main(){
	
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
	
}


