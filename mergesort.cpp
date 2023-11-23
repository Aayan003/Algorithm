#include <bits/stdc++.h>

using namespace std;

#define MAX 100

void merge(int arr[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low, aux[MAX];
    while (i <= mid && j <= high) 
    {
        if (arr[i] < arr[j])
            aux[k++] = arr[i++]; 
        else
            aux[k++] = arr[j++]; 
    }
    while (i <= mid)
        aux[k++] = arr[i++];
    while (j <= high)
        aux[k++] = arr[j++];
    for (int c = low; c <= high; ++c) 
        arr[c] = aux[c]; 
}

void mergesort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (high + low) / 2;
        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    mergesort(arr, 0, 6);
    for (int i = 0; i < 7; ++i)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
