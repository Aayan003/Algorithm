#include <stdio.h>

int B[100];

int max_element(int A[], int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (max < A[i]) {
            max = A[i];
        }
    }
    return max;
}

void counting_sort(int A[], int n, int div) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++) {
        count[(A[i] / div) % 10]++;
    }

    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
        output[count[(A[i] / div) % 10] - 1] = A[i];
        count[(A[i] / div) % 10]--;
    }

    for (i = 0; i < n; i++) {
        A[i] = output[i];
    }
}

void radix_sort(int A[], int n) {
    int k = max_element(A, n);
    for (int div = 1; k / div > 0; div *= 10) {
        counting_sort(A, n, div);
    }
}

int main() {
    int A[1000], i, n;
    printf("Enter the length of array: ");
    scanf("%d", &n);
    printf("Enter the elements of array: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    printf("Entered array is:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    printf("Sorted array:\n");
    radix_sort(A, n);
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
