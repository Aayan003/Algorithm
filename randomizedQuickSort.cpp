#include <bits/stdc++.h>

using namespace std;

#define MAX 100

class Quicksort
{
	private:
		void swap(int *inp1, int *inp2)
		{
			int temp = *inp1;
			*inp1 = *inp2;
			*inp2 = temp;
		}
		int partition(int arr[], int low, int high)
		{
			int random = low + rand() % (high - low);
			swap(&arr[random], &arr[low]);
			int pivot = arr[low], up = high, down = low;
			while(up > down)
			{
				while(arr[up] > pivot && up > low)
					--up;
				while(arr[down] <= pivot && down < high)
					++down;
				if(up > down)
					swap(&arr[up], &arr[down]);
			}
			swap(&arr[low], &arr[up]);
			return up;
		}
	public:
		void QuickSort(int arr[], int low, int high)
		{
			if(low < high)
			{
				int p = partition(arr, low, high);
				QuickSort(arr, low, p - 1);
				QuickSort(arr, p + 1, high);
			}
		}
};

int main()
{
	    srand(time(0));

	int arr[] = {64, 34, 25, 12, 22, 11, 90};
	cout << "Before sort: ";
	for(int i = 0; i < 7; ++i)
		cout << arr[i] << " ";
	Quicksort qs;
	qs.QuickSort(arr, 0, 6);
	cout << endl << "After Sort: ";
	for(int i = 0; i < 7; ++i)
		cout << arr[i] << " ";
	return 0;
}
