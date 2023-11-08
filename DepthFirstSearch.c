#include <stdio.h>
#define MAX 100

char colour[MAX]; 
int adjMatrix[MAX][MAX];
int Parent[MAX], time = 0, d[MAX], f[MAX];

void dfsVisit(int vCount, int start) {
    d[start] = time++;
    colour[start] = 'G';
    printf("Visited: %d ", start + 1);
    for(int i = 0; i < vCount; i++)
    {
        if (adjMatrix[start][i] == 1 && colour[i] == 'W')
        {
            //printf("Edge from %d to %d\n", start + 1, i + 1);
            Parent[i] = start;
            dfsVisit(vCount, i);
        }
    }
    f[start] = time++;
    colour[start] = 'B';
}

void DFS(int vertex) {
    time = 0;
    for(int i = 0; i < vertex; ++i) {
        if(colour[i] == 'W') {
            //printf("Starting DFS from vertex: %d\n", i + 1);
            dfsVisit(vertex, i);
        }
    }
}

void adjacency(int u, int v) {
    adjMatrix[u][v] = 1;
}

int main() {
    int vertex, edge;
    printf("Number of vertices: ");
    scanf("%d", &vertex);
    printf("\nNumber of edges: ");
    scanf("%d", &edge);
    for(int i = 0; i < vertex; i++)
    {
        colour[i] = 'W';
        Parent[i] = -1;
    }
    for(int i = 0; i < MAX; i++)
    {
        for(int i = 0; i < MAX; i++)
        {
            adjMatrix[i][i] = 0;
        }
    }
    for(int i = 0; i < edge; i++) {
        int u, v;
        printf("Edge between u & v vertices:\n");
        printf("u: ");
        scanf("%d", &u);
        printf("v: ");
        scanf("%d", &v);
        adjacency(u - 1, v - 1);
    }
    printf("\nDFS Traversal:\n");
    DFS(vertex);
    printf("\nColour array: ");
    for (int i = 0; i < vertex; ++i) {
        printf("%c ", colour[i]);
    }
    printf("\n");
    for(int i = 0; i < vertex; i++) {
        printf("Vertex %d: Discovery Time = %d, Finish Time = %d, Parent = %d\n", i + 1, d[i] + 1, f[i] + 1, Parent[i] + 1);
    }

    return 0;
}
