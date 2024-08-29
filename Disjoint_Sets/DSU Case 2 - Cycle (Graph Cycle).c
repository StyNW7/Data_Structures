/***********************************************************************************************************************

NOTE: DSU is different from graph, however it has so many application using graph as input data. 
This case is made so student can learn application of DSU without knowing about graph theory.

This case is using the theory of Cycle in Graph
In graph theory, a cycle in a graph is a non-empty trail in which only the first and last vertices are equal. 
========================================================================================================================

Problem: Efficient Trip Planning
A group of friends want to plan a trip in a foreign country and want to make sure to visit all the interesting place in 
the most efficient manner. To do this, they start listing the road they will take to reach each places.
The important part here is that they don't wanna go to the place that they have visited 
and take the same road (a cycle) for time and fuel efficiency. 

Input:
C R (C is the number of place, R is the total number of the roads connecting the places that the group plans to take)
a b (a and b are the place id which have a road connecting them, and the group plans to take the road)
The program will ask R number of a b pairs.

Output:
Whether the planning have a cycle or not (Perfect plan/Cycle detected)
**********************************************************************************************************************
Example 1:
Input:
6 5
0 1
1 2
2 5
5 4
4 3

Output: Perfect plan

Explanation: 
The plan is perfect already, they dont take any road that they have taken and dont visit any visited places.
**********************************************************************************************************************
Example 2:
Input:
4 3 
1 2 
2 0 
0 1

Output: Cycle detected

Explanation: 
Road 0 1 makes a cycle in the whole plan because they have visited 1 before.
***********************************************************************************************************************/

#include <stdio.h>
#define MAX 100

int parent[MAX];
int cycle = 0;

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
    if(a != b)
        parent[b] = a;
    // The point here is that if the program tries to join two sets that have the same parent, 
    // it means there is a cycle
    else 
        cycle++;
}

void printParent(int max){
    for(int i=0;i<max;i++){
        printf("%d ", parent[i]);
    }
    printf("\n");
}

int main()
{
    int V, E, a, b; // V is number of place, E is number of road, a & b consecutively are connected vertices (through edges)
    // Input the V and E first, then make set V times to initialize the value
    scanf("%d %d", &V, &E);
    for(int i = 0;i<V;i++){
        make_set(i);
    }
    // This program will take E number of input for the a - b pair of places (road) and union the vertices
    for(int i = 0;i<E;i++){
        scanf("%d %d", &a, &b);getchar();
        union_sets(a, b);
        // Uncomment if you wanna know the process:
        // printParent(V);
    }

    if(cycle>0)
        printf("Cycle detected");
    else 
        printf("Perfect plan");
        
    return 0;
}



