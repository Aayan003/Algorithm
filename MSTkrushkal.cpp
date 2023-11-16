#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

#define MAX 100

class Element
{
public:
    int from, to, prio;
};

class Graph
{
public:
    int weight, flag = 0;
};

class Queue
{
private:
    Element item[MAX];
    int rear;

    void swap(Element *num_1, Element *num_2)
    {
        Element cpy;
        cpy = *num_1;
        *num_1 = *num_2;
        *num_2 = cpy;
    }

public:
    void init()
    {
        rear = -1;
    }

    int isFull()
    {
        return (rear == MAX - 1);
    }

    int isEmpty()
    {
        return (rear == -1);
    }

    void pri_enqueue(Element x)
    {
        if (!isFull())
        {
            item[++rear] = x;
            int c = rear, f;
            do
            {
                f = (c - 1) / 2;
                if (item[c].prio < item[f].prio)
                {
                    swap(&(item[c]), &(item[f]));
                    c = f;
                }
                else
                    break;
            } while (c != 0);
        }
        else
            return;
    }

    void del()
    {
        if (!isEmpty())
        {
            Element z = item[0];
            item[0] = item[rear--];
            int p = 0, smallest, left, right;
            do
            {
                smallest = left = 2 * p + 1;
                right = 2 * p + 2;
                if (left > rear)
                    break;
                if (left <= rear && item[right].prio < item[left].prio)
                {
                    smallest = right;
                }
                if (item[smallest].prio < item[p].prio)
                {
                    swap(&item[smallest], &item[p]);
                    p = smallest;
                }
                else
                    break;
            } while (p <= rear);
        }
    }

    Element top()
    {
        return item[0];
    }
};

class Krushkal
{
private:
    Graph **A;
    class Disjoint
    {
    public:
        int dsj, rank;
    };
    Queue q;
    Disjoint dis[MAX];
    int parent[MAX];

    void Link(int x, int y)
    {
        if (dis[x].rank > dis[y].rank)
            parent[y] = x;
        else
        {
            parent[x] = y;
            if (dis[x].rank == dis[y].rank)
                ++dis[y].rank;
        }
    }

    void Makeset(int u)
    {
        parent[u] = u;
        dis[u].dsj = u;
        dis[u].rank = 0;
    }

    int Findset(int x)
    {
        if (x != parent[x])
            parent[x] = Findset(parent[x]);
        return parent[x];
    }

    void Union(int x, int y)
    {
        Link(Findset(x), Findset(y));
    }

public:
    Krushkal(int num)
    {
        A = new Graph *[MAX];
        for (int i = 0; i < MAX; ++i)
        {
            A[i] = new Graph[MAX];
        }
        for (int i = 0; i < num; ++i)
        {
            for (int j = 0; j < num; j++)
            {
                A[i][j].flag = 0;
                A[i][j].weight = numeric_limits<int>::max();
            }
        }
    }
    ~Krushkal()   
    {
        for(int i = 0; i < MAX; ++i)
        {
            delete[] A[i];
        }
        delete[] A;
    }
    void adjacency(int u, int v, int wg)
    {
        A[u][v].flag = 1;
        A[u][v].weight = wg;
    }

    int MST_Krushkal(int num, Graph last[MAX][MAX])
    {
        int wg = 0; // Initialize wg
        for (int i = 0; i < num; ++i)
            Makeset(i);

        for (int i = 0; i < num; ++i)
        {
            for (int j = 0; j < num; ++j)
            {
                if (A[i][j].flag)
                {
                    Element X;
                    X.from = i, X.to = j, X.prio = A[i][j].weight;
                    q.pri_enqueue(X);
                }
            }
        }

        while (!q.isEmpty())
        {
            Element Z = q.top();
            if (Findset(Z.from) != Findset(Z.to))
            {
                last[Z.from][Z.to].flag = 1;
                last[Z.to][Z.from].weight = Z.prio;
                Union(Z.from, Z.to);
                q.del();
                cout << "from edge " << Z.from + 1 << " to edge " << Z.to + 1 << " weight is " << Z.prio << endl;
                wg += Z.prio;
            }
            else
            {
                q.del(); 
            }
        }
        return wg;
    }
};

int main()
{
    int ver, edge;
    Graph G[MAX][MAX];
    cout << "Enter numbers of Vertex: ";
    cin >> ver;
    cout << "Enter numbers of Edges: ";
    cin >> edge;
    Krushkal kr(ver);
    for (int i = 0; i < edge; ++i)
    {
        int u, v, wg;
        cout << "Edge between u & v vertices:\n";
        cout << "u: ";
        cin >> u;
        cout << "v: ";
        cin >> v;
        cout << "Weight: ";
        cin >> wg;
        kr.adjacency(u - 1, v - 1, wg);
    }
    int weight = kr.MST_Krushkal(ver, G);
    cout << "\nWeight of the Minimum Spanning Tree: " << weight << endl;
    return 0;
}
