#include <bits/stdc++.h>

using namespace std;

#define MAX 100
class Graph
{
    public:
        int weight = INT_MAX;
        bool edge = false;
};

class BellManFord
{
    private:
        Graph **G;
        int *vernum, *edgenum, distance[MAX], P[MAX];
        void InitSingleSource(int s)
        {
            for(int i = 0; i < *vernum; ++i)
            {
                distance[i] = INT_MAX;
                P[i] = -1;
            }
            distance[s] = 0;
        }
        void Relax(int u, int v)
        {
            if(distance[v] > distance[u] + G[u][v].weight)
            {
                distance[v] = distance[u] + G[u][v].weight;
                P[v] = u;
            }
        }
        bool checkifpath(int s)
        {
            InitSingleSource(s);
            for(int k = 0; k < *vernum - 1; ++k)
            {
                for(int i = 0; i < *vernum; ++i)
                {
                    for(int j = 0; j < *vernum; ++j)
                    {
                        if(G[i][j].edge)
                        {
                            Relax(i, j);
                        }
                    }
                }
            }
            for(int i = 0; i < *vernum; ++i)
            {
                for(int j = 0; j < *vernum; ++j)
                {
                    if(G[i][j].edge)
                    {
                        if(distance[j] > distance[i] + G[i][j].weight)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
    public:
        BellManFord(int *ver)
        {
            vernum = ver;
            G = new Graph*[*ver];
            for(int i = 0; i < *ver; ++i)
            {
                G[i] = new Graph[*ver];
            }
        }
        void addEdge(int u, int v, int wg)
        {
            
            G[u][v].weight = wg;
            G[u][v].edge = true;
        }
        void ifPossiblePath(int s)
        {
            if(checkifpath(s))
            {
                cout << "Path is possible\n";
                for(int i = 0; i < *vernum; ++i)
                    cout << "U->V: " << P[i] + 1 << "->" << i + 1 << "  Cost to reach " << P[i] + 1 << " from source 0 = " << distance[i] << "\n";
            }
            else
                cout << "Shortest path not possible as negative cycle is present.\n";
        }
        ~BellManFord()
        {
            for(int i = 0; i < *vernum; ++i)
            {
                delete G[i];
            }
            delete G;
        }
};


int main()
{
    int ver, edge;
    cout << "Enter Number of Vertex: ";
    cin >> ver;
    cout << "Enter Number of Edge: ";
    cin >> edge;
    BellManFord bf(&ver);
    for(int i = 0; i < edge; ++i)
    {
        int u, v, wg;
            cout << "Enter the u to v edge:\n";
            cout << "u: ";
            cin >> u;
            cout << "v : ";
            cin >> v;
            cout << "Enter the weight: ";
            cin >> wg;
        bf.addEdge(u - 1, v - 1, wg);
    }
    int start;
    cout << "Starting vertex: ";
    cin >> start;
    bf.ifPossiblePath(start - 1);
    return 0;
}
