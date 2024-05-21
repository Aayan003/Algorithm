#include <bits/stdc++.h>

using namespace std;

#define MAX 100

void cChange(int &a, int &b) {
	if(a > b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

int* batchers(int *u, int m, int *v, int n) {
	int *s = new int[m + n];
	if (m == 0) {
        for (int i = 0; i < n; ++i) { 
            s[i] = v[i];
        }
    } else if (n == 0) {
        for (int i = 0; i < m; ++i) {  
            s[i] = u[i];
        }
    }
	else if(m == 1 && n == 1) {
		cChange(u[0], v[0]);
		s[0] = u[0];
		s[1] = v[0];
	}
	else {
		int x, y;
		if(m % 2 == 1)
			x = m / 2 + 1;
		else
			x = m / 2;
		if(n % 2 == 1)
			y = n / 2 + 1;
		else
			y = n / 2;
		
		int *Ou = new int[x];
		int *Eu = new int[m / 2];
		
		for(int i = 0, j = 0; i < m; i += 2, j++) {
			Ou[j] = u[i];
		}
		for(int i = 1, j = 0; i < m; i += 2, j++) {
			Eu[j] = u[i];
		}
		int *Ov = new int[y];
		int *Ev = new int[n / 2];
		
		for(int i = 0, j = 0; i < n; i += 2, j++) {
			Ov[j] = v[i];
		}
		for(int i = 1, j = 0; i < n; i += 2, j++) {
			Ev[j] = v[i];
		}
		
		int *a = batchers(Ou, x, Ov, y);
		int *b = batchers(Eu, m / 2, Ev, n / 2);
		int c = 0;
		if(m % 2 == 0 && n % 2 == 0)
			c = m / 2 + n / 2 - 1;
		else
			c = m / 2 + n / 2;
		
		s[0] = a[0];
		
		for(int i = 1; i <= c; ++i) {
			cChange(b[i - 1], a[i]);
		}
		for(int i = 1, j = 1; i <= c; ++i) {
			s[j++] = b[i - 1];
			s[j++] = a[i];
			if(m % 2 == 1 && n % 2 == 1 && i == c) {
				s[j++] = a[m / 2 + n / 2 + 1]; 
			}
			else if(m % 2 == 0 && n % 2 == 0 && i == c) {
				s[j++] = b[m / 2 + n / 2 - 1];
			}
		}
		delete[] Ou;
		delete[] Ov;
		delete[] Eu;
		delete[] Ev;
		delete[] a;
		delete[] b;
	}
	
	return s;
	
}

int* batchersSort(int *arr, int low, int num) {
	if(num > 1) {
		int m, n;
		int mid = num/2;
		m = mid;
		n = num - mid;
		int *u = new int[m];
		int *v = new int[n];
		for(int i = 0; i < m; ++i){
			u[i] = arr[i];
		}
		
		for(int i = 0; i < n; ++i) {
			v[i] = arr[i + mid];
		}
		
		
		u = batchersSort(arr, low, mid);
		v = batchersSort(arr, low + mid, n);
		int *s = batchers(u, m, v, n);
		delete[] u;
		delete[] v;
		
		return s;
	}
	
	int *s = new int[1];
	s[0] = arr[low];
	return s;
}

int main() {
	int n = 14;
	int *arr = new int[n];
	for(int i = 0; i < n; ++i) {
		arr[i] = rand() % n;
	}
	
	cout << "Intitial array: ";
	for(int i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	int *sorted = new int[n];
	sorted = batchersSort(arr, 0, n);
	cout << "Sorted array: ";
	for(int i = 0; i < n; ++i) {
		cout << sorted[i] << " ";
	}
	cout << endl;
	
	return 0;
}
