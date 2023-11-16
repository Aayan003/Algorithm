#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX 100

struct Element
{
    int from, to, prio;
};

struct Graph
{
    int weight, flag;
};

struct Queue
{
    struct Element item[MAX];
    int rear;
};

struct Krushkal
{
    struct Graph **A;
    struct Queue q;
    struct Disjoint
    {
        int dsj, rank;
    } dis[MAX];
    int *parent;
};

void swap(struct Element *num_1, struct Element *num_2)
{
    struct Element cpy = *num_1;
    *num_1 = *num_2;
    *num_2 = cpy;
}

void init(struct Queue *q)
{
    q->rear = -1;
}

int isFull(struct Queue *q)
{
    return (q->rear == MAX - 1);
}

int isEmpty(struct Queue *q)
{
    return (q->rear == -1);
}

void pri_enqueue(struct Queue *q, struct Element x)
{
    if (!isFull(q))
    {
        q->item[++q->rear] = x;
        int c = q->rear, f;
        do
        {
            f = (c - 1) / 2;
            if (q->item[c].prio < q->item[f].prio)
            {
                swap(&(q->item[c]), &(q->item[f]));
                c = f;
            }
            else
                break;
        } while (c != 0);
    }
}

void del(struct Queue *q)
{
    if (!isEmpty(q))
    {
        struct Element z = q->item[0];
        q->item[0] = q->item[q->rear--];
        int p = 0, smallest, left, right;
        do
        {
            smallest = left = 2 * p + 1;
            right = 2 * p + 2;
            if (left > q->rear)
                break;
            if (left <= q->rear && q->item[right].prio < q->item[left].prio)
            {
                smallest = right;
            }
            if (q->item[smallest].prio < q->item[p].prio)
            {
                swap(&(q->item[smallest]), &(q->item[p]));
                p = smallest;
            }
            else
                break;
        } while (p <= q->rear);
    }
}

struct Element top(struct Queue *q)
{
    return q->item[0];
}

void Link(struct Krushkal *k, int x, int y)
{
    if (k->dis[x].rank > k->dis[y].rank)
        k->parent[y] = x;
    else
    {
        k->parent[x] = y;
        if (k->dis[x].rank == k->dis[y].rank)
            ++k->dis[y].rank;
    }
}

void Makeset(struct Krushkal *k, int u)
{
    k->parent[u] = u;
    k->dis[u].dsj = u;
    k->dis[u].rank = 0;
}

int Findset(struct Krushkal *k, int x)
{
    if (x != k->parent[x])
        k->parent[x] = Findset(k, k->parent[x]);
    return k->parent[x];
}

void Union(struct Krushkal *k, int x, int y)
{
    Link(k, Findset(k, x), Findset(k, y));
}

struct Krushkal *initialize(int num)
{
    struct Krushkal *k = (struct Krushkal *)malloc(sizeof(struct Krushkal));
    k->A = (struct Graph **)malloc(MAX * sizeof(struct Graph *));
    for (int i = 0; i < MAX; ++i)
    {
        k->A[i] = (struct Graph *)malloc(MAX * sizeof(struct Graph));
    }
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; j++)
        {
            k->A[i][j].flag = 0;
            k->A[i][j].weight = INT_MAX;
        }
    }
    k->parent = (int *)malloc(MAX * sizeof(int));
    return k;
}

void adjacency(struct Krushkal *k, int u, int v, int wg)
{
    k->A[u][v].flag = 1;
    k->A[u][v].weight = wg;
}

int MST_Krushkal(struct Krushkal *k, int num, struct Graph last[MAX][MAX])
{
    int wg = 0;
    for (int i = 0; i < num; ++i)
        Makeset(k, i);

    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            if (k->A[i][j].flag)
            {
                struct Element X;
                X.from = i, X.to = j, X.prio = k->A[i][j].weight;
                pri_enqueue(&(k->q), X);
            }
        }
    }

    while (!isEmpty(&(k->q)))
    {
        struct Element Z = top(&(k->q));
        if (Findset(k, Z.from) != Findset(k, Z.to))
        {
            last[Z.from][Z.to].flag = 1;
            last[Z.to][Z.from].weight = Z.prio;
            Union(k, Z.from, Z.to);
            del(&(k->q));
            printf("from edge %d to edge %d weight is %d\n", Z.from + 1, Z.to + 1, Z.prio);
            wg += Z.prio;
        }
        else
        {
            del(&(k->q));
        }
    }
    return wg;
}

int main()
{
    int ver, edge;
    printf("Enter numbers of Vertex: ");
    scanf("%d", &ver);
    printf("Enter numbers of Edges: ");
    scanf("%d", &edge);

    struct Krushkal *kr = initialize(ver);

    for (int i = 0; i < edge; ++i)
    {
        int u, v, wg;
        printf("Edge between u & v vertices:\n");
        printf("u: ");
        scanf("%d", &u);
        printf("v: ");
        scanf("%d", &v);
        printf("Weight: ");
        scanf("%d", &wg);
        adjacency(kr, u - 1, v - 1, wg);
    }

    struct Graph G[MAX][MAX];
    int weight = MST_Krushkal(kr, ver, G);
    printf("\nWeight of the Minimum Spanning Tree: %d\n", weight);

    free(kr->parent);
    for (int i = 0; i < MAX; ++i)
    {
        free(kr->A[i]);
    }
    free(kr->A);
    free(kr);

    return 0;
}
