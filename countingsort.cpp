#include <iostream>
using namespace std;
#define MAX 100
void counting(int A[5], int lim, int k)
{
    int C[MAX], B[MAX];
    for(int i = 0; i < k; ++i)
    {
        C[i] = 0;
    }
    for(int i = 0; i < lim; ++i)
    {
        C[A[i] - 1]++;
    }
    cout << endl;
    for(int i = 1; i < k; ++i)
    {
        C[i] += C[i - 1];
    }
    for(int i = lim - 1; i >= 0; --i)
    {
        B[C[A[i] - 1] - 1] = A[i];
        C[A[i] - 1]--;
    }
    for(int i = 0; i < lim; ++i)
    {
        A[i] = B[i];
    }
}
int main()
{
    int A[MAX];
    int n, maxelem;
    cout << "Enter the number of elements in array: ";
    cin >> n;
    cout << "Enter maximum element value: ";
    cin >> maxelem;
    cout << endl;
    cout << "Enter the elements of array: ";
    for (int i=0 ; i<n ; ++i )
    {
        cin >> A[i];
    }
    cout << "Array before sorting is :\n";
    for(int i=0 ; i<n ; ++i )
    {
        cout << A[i] << " ";
    }
    cout << endl;
    counting(A, n, maxelem);
    cout << "Array after sorting is :\n";
    for(int i=0 ; i<n ; ++i )
    {
        cout << A[i] << " ";
    }
    cout << endl;
    return 0;
}
