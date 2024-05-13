
#include <iostream>
#include <limits>

using namespace std;

#define MAX 100

class Element
{
    public:
        int vertices, key;
};

// class Graph
// {
//     public:
//         int weight = numeric_limits<int>::max(), flag = 0;
// };

class Queue
{
    private:
        Element item[MAX];
        int rear;

        inline void swap(Element *num_1, Element *num_2);

        void minHeapify();
    public:
        Queue() : rear(-1){};

        inline int isFull()
        {
            return (rear == MAX - 1);
        }

        inline int isEmpty()
        {
            return (rear == -1);
        }

        void buildMinHeap(int c);
        void pri_enqueue(Element x);

        Element del();
        
        void decreaseKey(int vertices, int num, int key);

        inline Element top()
        {
            return item[0];
        }
};

inline void Queue :: swap(Element *num_1, Element *num_2)
        {
            Element temp;
            temp = *num_1;
            *num_1 = *num_2;
            *num_2 = temp;
        }

void Queue :: minHeapify()
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
void Queue :: buildMinHeap(int c)
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
void Queue :: pri_enqueue(Element x)
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
Element Queue :: del()
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

void Queue :: decreaseKey(int vertices, int num, int key)
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

class Graph
{
    private:
        int **A;
        Queue q;
        int parent[MAX], vCount, eCount;
        
    public:
        Graph(int num, int ed);
        int MST_Prims(int num, int r, int last[MAX][MAX]);
        //friend ostream& operator<<(ostream& os, const Graph obj);
        friend istream& operator>>(istream& is, Graph& obj) {
            for (int i = 0; i < obj.eCount; ++i)
            {
                int u, v, wg;
                cout << "Edge between u & v vertices:\n";
                cout << "u: ";
                is >> u;
                cout << "v: ";
                is >> v;
                cout << "Weight: ";
                is >> wg;
                obj.A[v-1][u-1] = obj.A[u-1][v-1] = wg;
            }
            return is;
        }
        ~Graph();
};



// ostream& operator<<(ostream& os, const Graph obj) {
//     for(int i = 0; i < obj.lim; ++i) {
//         for(int j = 0; j < obj.lim; ++j) {
//             if(i > j / 2 && obj)
//         }
//     }
// }

Graph :: ~Graph()   
        {
            for(int i = 0; i < vCount; ++i)
            {
                delete[] A[i];
            }
            delete[] A;
        }

Graph :: Graph(int num, int ed)
        {
            vCount = num;
            eCount = ed;
            A = new int *[vCount];
            for (int i = 0; i < vCount; ++i)
            {
                A[i] = new int[vCount];
            }
            for (int i = 0; i < vCount; ++i)
            {
                for (int j = 0; j < vCount; j++)
                {
                    //A[i][j] = 0;
                    A[i][j] = numeric_limits<int>::max();
                }
            }
        }

int Graph :: MST_Prims(int num, int r, int last[MAX][MAX]) // I am using graph last for any future use of the MST
        {                                      //You can delete graph last
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
                    //cout << "Vertex!!: " << A[X.vertices][i] << endl;
                    if(mstflag[i] == false && key[i] > A[X.vertices][i])
                    {
                        last[X.vertices][i] = key[i] = A[X.vertices][i];
                        parent[i] = X.vertices;
                        q.decreaseKey(i, num, key[i]);
                    }
                }
                cout << "from edge " << parent[X.vertices] + 1 << " to edge " << X.vertices + 1 << " weight is " << X.key << endl;
                weightTotal += X.key;
            }
            return weightTotal;
        }

int main()
{
    int ver = 9, edge = 14;
    //Graph G[MAX][MAX];
    int arr[MAX][MAX];
    cout << "Enter numbers of vertices: ";
    cin >> ver;
    cout << "Enter numbers of Edges: ";
    cin >> edge;
    Graph pm(ver, edge);
    cin >> pm;
    int source;
    cout << "Enter the source vertices: ";
    cin >> source;
    int weight = pm.MST_Prims(ver, source - 1, arr);
    cout << "\nWeight of the Minimum Spanning Tree: " << weight << endl;
    return 0;
}