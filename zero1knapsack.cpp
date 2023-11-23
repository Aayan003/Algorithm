#include <bits/stdc++.h>

using namespace std;

#define MAX 100

int maximum(int num1, int num2)
{
    return num1 > num2 ? num1 : num2;
}

int knapsack(int n, int m, int w[], int p[])
{
    int v[MAX][MAX];
    for (int i = 0; i < n; ++i)
        v[i][0] = 0;
    for (int i = 0; i < m; ++i)
        v[0][i] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (w[i] > j)
                v[i][j] = v[i - 1][j];
            else
                v[i][j] = maximum(v[i - 1][j], v[i - 1][j - w[i]] + p[i]);
        }
    }
    return v[n][m];
}

int main()
{
    
    int n = 4;
    int m = 5; 
     int weights[] = {2, 1, 3, 2};
    int profits[] = {12, 10, 20, 15};

    int maxValue = knapsack(n, m, weights, profits);

    cout << "Maximum value that can be obtained: " << maxValue << endl;

    return 0;
}
