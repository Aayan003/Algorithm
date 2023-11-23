#include <bits/stdc++.h>

using namespace std;

#define MAX 100

class NQueens
{
	private:
		int col[MAX], rd[MAX], ld[MAX], board[MAX], num;
		bool placeQueen(int i)
		{
			for(int j = 1; j <= num; ++j)
			{
				if(col[j] == 0 && ld[i + num - j] == 0 && rd[i + j - 1] == 0)
				{
					board[i] = j;
					col[j] = ld[i + num - j] = rd[i + j - 1] = 1;
					if(i == num)
						return true;
					else if(placeQueen(i + 1))
						return true;
					board[i] = 0;
					col[j] = ld[i + num - j] = rd[i + j - 1] = 0;
				}
			}
            return false;
		}
	public:
		NQueens(int n)
		{
			num = n;
			for(int i = 1; i <= num; ++i)
				col[i] = 0;
			for(int i = 1; i <= 2 * num - 1; ++i)
				ld[i] = rd[i] = 0;
		}
		void printSolution()
		{
			if(placeQueen(1))
			{
				cout << "Solution: ";
				for(int i = 1; i <= num; ++i)
					cout << "(" << i << ", " << board[i] << "), ";
				cout << endl;
			}
			else
				cout << "N solution!!\n";
		}
};

int main()
{
	int n;
	cout <<"Enter number of queens to be placed: ";
	cin >> n;
	NQueens qn(n);
	qn.printSolution();
	return 0;
}
