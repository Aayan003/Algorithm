#include <iostream>
#include <limits>
#include <queue>
#define MAX 100

using namespace std;


class Queue
{
private:
    class node
    {
    public:
        int data;
        node *next;
    };
    node *rear;

public:
    Queue()
    {
        rear = NULL;
    }

    void enqueue(int item)
    {
        node *new_node = new node;
        new_node->data = item;
        if (rear == NULL)
        {
            rear = new_node;
            (rear)->next = rear;
        }
        else
        {
            new_node->next = (rear)->next;
            (rear)->next = new_node;
            rear = new_node;
        }
    }

    int dequeue()
    {
        if (rear == NULL)
        {
            return -92929292;
        }
        node *ptr = (rear)->next;
        if ((rear)->next == rear)
        {
            rear = NULL;
        }
        else
        {
            (rear)->next = ptr->next;
        }
        int cpy = ptr->data;
        delete ptr;
        return cpy;
    }

    bool isEmpty()
    {
        return rear == NULL;
    }
};

class Graph
{
private:
    int vCount, adjMatrix[MAX][MAX], Parent[MAX];;
    char colour[MAX];

public:
    bool BFS(int rGraph[MAX][MAX] ,int start, int t);
    Graph(int V) : vCount(V){
        for(int i = 0; i < vCount; ++i){
            colour[i] = 'W';
            Parent[i] = -1;
            for(int j = 0; j < vCount; ++j){
                adjMatrix[i][j] = 0;
            }
        }
    }

    inline void adjacency(int u, int v, int w)
    {
        adjMatrix[u][v] = w;
    }

    int FordFulkerson(int s, int t);
};


bool Graph ::BFS(int rGrapgh[MAX][MAX], int start, int t)
{
    Queue Q;
    for(int i = 0; i < vCount; ++i){
        colour[i] = 'W';
    }
    colour[start] = 'G';
    Parent[start] = -1;
    Q.enqueue(start);
    while (!Q.isEmpty())
    {
        int u = Q.dequeue();
        for (int i = 0; i < vCount; i++)
        {
            if (rGrapgh[u][i] > 0 && colour[i] == 'W')
            {
                Parent[i] = u;
                if (i == t)
                {
                    return true;
                }
                Q.enqueue(i);
                colour[i] = 'G';
            }
        }
        colour[u] = 'B';
    }
	return false;
}

int Graph ::FordFulkerson(int s, int t)
{
    int rGraph[MAX][MAX];
    for (int i = 0; i < vCount; i++)
    {
        for (int j = 0; j < vCount; j++)
        {
            rGraph[i][j] = adjMatrix[i][j];
        }
    }
    int max_flow = 0;
    while (BFS(rGraph, s, t))
    {

        int min_flow = 99999999;
        int v = t;
        while (v != s)
        {
            int u = Parent[v];
            if (rGraph[u][v] < min_flow)
                min_flow = rGraph[u][v];
            v = Parent[v];
        }
        v = t;
        while (v != s)
        {
            int u = Parent[v];
            rGraph[u][v] -= min_flow;
            rGraph[v][u] += min_flow;
            v = Parent[v];
        }
        max_flow += min_flow;

    }
    return max_flow;
}

int main()
{
    int vertex, edge;
    cout << "Number of vertices: ";
    cin >> vertex;
    cout << "\nNumber of edges: ";
    cin >> edge;
    Graph G(vertex);


    for (int i = 0; i < edge; i++)
    {
        int u, v, wg;
        cout << "Edge between u & v vertices:\n";
        cout << "u: ";
        cin >> u;
        cout << "v: ";
        cin >> v;
        cout << "Enter the Weight: ";
        cin >> wg;
        G.adjacency(u - 1, v - 1, wg);
    }

    int start, t;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the destination node: ";
    cin >> t;
    int maxlim = G.FordFulkerson(start - 1, t - 1);
    cout << endl
         << "Max Flow: " << maxlim << endl;
    cout << "\n";

    return 0;
}
