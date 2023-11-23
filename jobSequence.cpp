#include <bits/stdc++.h>

using namespace std;

#define MAX 100

class Job
{
	public:
		int jobNum, ded, profit;
};

class Greedy
{
	private:
		int profit[MAX], num;
		Job jobs[MAX];
		void sort()
		{
			for(int i = 1; i < num; ++i)
			{
				int j;
				Job temp = jobs[i];
				for(j = i - 1; j >= 0 && jobs[j].profit < temp.profit; --j)
				{
					jobs[j+1] = jobs[j];
				}
				jobs[j+1] = temp;
			}
		}
		void computeProfit()
		{
			for(int i = 0; i < num; ++i)
			{
				for(int j = jobs[i].ded - 1; j >= 0; --j)
				{
					if(profit[j] == -1)
					{						
						profit[j] = i;
						break;
					}
				}
			}
		}
	public:
		void takeInput()
		{
			cout << "Enter number of jobs: ";
			cin >> num;
			for(int i = 0; i < num; ++i)
			{
				cout << "For job number " << i + 1 << endl;
				cout << "Enter profit: ";
				cin >> jobs[i].profit;
				cout << "Enter deadline: ";
				cin >> jobs[i].ded;
				jobs[i].jobNum = i + 1;
				cout << jobs[i].jobNum << endl;
				profit[i] = -1;
			}
		}
		void printProfit()
		{
			sort();
			computeProfit();
			int sum = 0;
			for(int i = 0; i < num; ++i)
			{
					if(profit[i] != -1)
					{
						cout << "For job " << jobs[profit[i]].jobNum << " profit is " << jobs[profit[i]].profit << endl;
						sum += jobs[profit[i]].profit;
					}		
			}
			cout << "Total profit: " << sum << endl;
		}	
};

int main()
{
	Greedy bj;
	bj.takeInput();
	bj.printProfit();
	return 0;
}
