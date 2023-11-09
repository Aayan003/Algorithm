#include <iostream>
#include <limits>
#define MAX 100

using namespace std;

char colour[MAX];
int adjMatrix[MAX][MAX];
int Parent[MAX];
int d[MAX];

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
            free(ptr);
            return cpy;
        }

        bool isEmpty()
        {
            return rear == NULL;
        }
};

void BFS(int vCount, int start)
{
    Queue Q;
    d[start] = 0;
    colour[start] = 'G';
    Parent[start] = -1;
    Q.enqueue(start);

    while (!Q.isEmpty())
    {
        int u = Q.dequeue();
        cout << "Visited: " << u + 1 << " ";
        for (int i = 0; i < vCount; i++) {
            if (adjMatrix[u][i] && colour[i] == 'W')
            {
                colour[i] = 'G';
                d[i] = d[u] + 1;
                Parent[i] = u;
                Q.enqueue(i);
            }
        }
        colour[u] = 'B';
    }
}

void adjacency(int u, int v)
{
    adjMatrix[u][v] = 1;
}

int main()
{
    int vertex, edge;
    cout << "Number of vertices: ";
    cin >> vertex;
    cout << "\nNumber of edges: ";
    cin >> edge;

    for (int i = 0; i < vertex; i++)
    {
        colour[i] = 'W';
        Parent[i] = -1;
        d[i] = numeric_limits<int>::max();
    }

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < edge; i++)
    {
        int u, v;
        cout << "Edge between u & v vertices:\n";
        cout << "u: ";
        cin >> u;
        cout << "v: ";
        cin >> v;
        adjacency(u - 1, v - 1);
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "\nBFS Traversal:\n";
    BFS(vertex, start - 1);
    cout << "\nColour array: ";
    for (int i = 0; i < vertex; ++i)
    {
        cout << colour[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < vertex; i++)
    {
        cout << "Vertex " << i + 1 << ": Weight = " << d[i] << ", Parent = " << Parent[i] << "\n";
    }

    return 0;
}
