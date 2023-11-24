#include <bits/stdc++.h>

using namespace std;

#define MAX 100

int maximum(int num1, int num2)
{
    return num1 > num2 ? num1 : num2;
}

string LCS(int n, int m, string A, string B)
{
    int dp[MAX][MAX];
    for(int i = 0; i <= n; ++i)
        dp[i][0] = 0;
    for(int j = 0; j <= m; ++j)
        dp[0][j] = 0;

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            if(A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = maximum(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    //printing the LCS
    int i = n, j = m;
    string lcs = "";
    while (i > 0 && j > 0)
    {
        if (A[i - 1] == B[j - 1])
        {
            lcs = A[i - 1] + lcs;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs;
}

int main()
{
    string A = "moye";
    string B = "moyemoye";
    string lcs = LCS(A.size(), B.size(), A, B);

    if (lcs.empty())
        cout << "No Sequence" << endl;
    else
        cout << "Longest Common Subsequence: " << lcs << endl;

    return 0;
}
