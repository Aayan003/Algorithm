#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

#define MAX 100

class Element
{
    public:
        int vertices, key;
};

class Graph
{
    public:
        int weight = numeric_limits<int>::max(), flag = 0;
};

class Queue
{
    private:
        Element item[MAX];
        int rear;

        void swap(Element *num_1, Element *num_2)
        {
            Element temp;
            temp = *num_1;
            *num_1 = *num_2;
            *num_2 = temp;
        }

        void minHeapify()
        {
            if(!isEmpty())
            {
                int p = 0, smallest, left, right;
                do
                {
                    smallest = left = 2 * p + 1;
                    right = 2 * p + 2;
                    if (left > rear)
                        break;
                    if (left <= rear && item[right].key < item[left].key)
                    {
                        smallest = right;
                    }
                    if (item[smallest].key < item[p].key)
                    {
                        swap(&item[smallest], &item[p]);
                        p = smallest;
                    }
                    else
                        break;
                }while(p <= rear);
            }
        }
    public:
        Queue()
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

        void buildMinHeap(int c)
        {
            if(c == 0)
                return;
            int f = (c - 1) / 2;
            if(item[c].key < item[f].key)
            {
                swap(&item[c],&item[f]);
                buildMinHeap(f);
            }
        }
        void pri_enqueue(Element x)
        {
            if (!isFull())
            {
                item[++rear] = x;
                int c = rear;
                buildMinHeap(c);
            }
            else
                return;
        }

        Element del()
        {
            if (!isEmpty())
            {
                Element z = item[0];
                item[0] = item[rear];
                --rear;
                minHeapify();
                return z;
            }
        }
        
        void decreaseKey(int vertices, int num, int key)
        {
            int i;
            for(i=0; i < num; i++)
            {
                if(item[i].vertices == vertices)
                    break;
            }
            item[i].key = key;
            buildMinHeap(i);
        }

        Element top()
        {
            return item[0];
        }
};

class PrimS
{
    private:
        Graph **A;
        Queue q;
        int parent[MAX];
        
    public:
        PrimS(int num)
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
        ~PrimS()   
        {
            for(int i = 0; i < MAX; ++i)
            {
                delete[] A[i];
            }
            delete[] A;
        }
        void adjacency(int u, int v, int wg)
        {
            A[v][u].flag = A[u][v].flag = 1;
            A[v][u].weight = A[u][v].weight = wg;
        }

        int MST_Prims(int num, int r, Graph last[MAX][MAX]) // I am using graph last for any future use of the MST
        {                                                   //You can delete graph last
            int key[MAX];
            bool mstflag[MAX] = {true};
            for(int i = 0; i < num; ++i)
            {
                Element Y;
                Y.key = key[i] = numeric_limits<int>::max();
                Y.vertices = i;
                mstflag[i] = false;
                q.pri_enqueue(Y);
            }
            key[r] = 0, parent[r] = -1;
            q.decreaseKey(r, num, key[r]);
            int weightTotal = 0;
            while(!q.isEmpty())
            {
                Element X = q.del();
                mstflag[X.vertices] = true;
                int i;
                for(i = 0; i < num; ++i)
                {
                    if(mstflag[i] == false && key[i] > A[X.vertices][i].weight)
                    {
                        last[X.vertices][i].weight = key[i] = A[X.vertices][i].weight;
                        last[X.vertices][i].flag = 1;
                        parent[i] = X.vertices;
                        q.decreaseKey(i, num, key[i]);
                    }
                }
                cout << "from edge " << parent[X.vertices] + 1 << " to edge " << X.vertices + 1 << " weight is " << X.key << endl;
                weightTotal += X.key;
            }
            return weightTotal;
        }
};

int main()
{
    int ver = 9, edge = 14;
    Graph G[MAX][MAX];
    cout << "Enter numbers of vertices: ";
    cin >> ver;
    cout << "Enter numbers of Edges: ";
    cin >> edge;
    PrimS pm(ver);
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
        pm.adjacency(u - 1, v - 1, wg);
    }
    int source;
    cout << "Enter the source vertices: ";
    cin >> source;
    int weight = pm.MST_Prims(ver, source - 1, G);
    cout << "\nWeight of the Minimum Spanning Tree: " << weight << endl;
    return 0;
}
