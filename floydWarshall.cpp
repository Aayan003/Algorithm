#include <bits/stdc++.h>

using namespace std;

#define MAX 100

class FloydWarshallSolver
{
private:
    long long int ***D;
    int vCount;

public:
    FloydWarshallSolver(int vertices)
    {
        vCount = vertices;
        D = new long long int **[vCount + 1];
        for (int i = 0; i <= vCount; ++i)
        {
            D[i] = new long long int *[vCount];
            for (int j = 0; j < vCount; ++j)
            {
                D[i][j] = new long long int[vCount];
            }
        }
    }

    ~FloydWarshallSolver()
    {
        for (int i = 0; i <= vCount; ++i)
        {
            for (int j = 0; j < vCount; ++j)
            {
                delete D[i][j];
            }
            delete D[i];
        }
        delete D;
    }

    long long int minimum(long long int num, long long int num2)
    {
        return num < num2 ? num : num2;
    }

    long long int **solve(long long int W[MAX][MAX])
    {
        for (int j = 0; j < vCount; ++j)
        {
            for (int k = 0; k < vCount; ++k)
            {
                D[0][j][k] = W[j][k];
            }
        }
        for (int k = 1; k <= vCount; ++k)
        {
            for (int i = 0; i < vCount; ++i) 
            {
                for (int j = 0; j < vCount; ++j)
                {
                    D[k][i][j] = minimum(D[k - 1][i][j], D[k - 1][i][k - 1] + D[k - 1][k - 1][j]);
                }
            }
        }
        return D[vCount];
    }
};

int main()
{
    int vertices = 4;
    FloydWarshallSolver solver(vertices);

    long long int W[MAX][MAX] =
    {
        {0, 8, INT_MAX, 1},
        {INT_MAX, 0, 1, INT_MAX},
        {4, INT_MAX, 0, INT_MAX},
        {INT_MAX, 2, 9, 0}};

    long long int **Final = solver.solve(W);

    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
            cout << Final[i][j] << " ";
        cout << endl;
    }

    return 0;
}
