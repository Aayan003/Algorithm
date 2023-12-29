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
    for (int i = 0; i <= n; ++i)
        v[i][0] = 0;
    for (int i = 0; i <= m; ++i)
        v[0][i] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (w[i - 1] > j)
                v[i][j] = v[i - 1][j];
            else
                v[i][j] = maximum(v[i - 1][j], v[i - 1][j - w[i - 1]] + p[i - 1]);
        }
    }
    return v[n][m];
}

int main()
{

    int m, n, weights[100], profits[100];
    cout << "Enter total capacity & number of elements: ";
    cin >> m >> n;
    for(int i = 0; i < n; ++i)
    {
        cout << "Enter " << i + 1 << " item's profit: ";
        cin >> profits[i];
        cout << "Weight: ";
        cin >> weights[i];
    }


    int maxValue = knapsack(n, m, weights, profits);

    cout << "Maximum value that can be obtained: " << maxValue << endl;

    return 0;
}
