#include <iostream>

using namespace std;

int intExp(int n, int x){
    int N = n, Z = x, Y = 1;
    while(N != 0){
        if(N & 1 == 1)
            Y *= Z;
        N /= 2;
        if(N != 0)
            Z *= Z;
    }
    return Y;
}

int main(){
    int n, x;
    cout << "Enter power: ";
    cin >> n;
    cout << "Enter the value of x: ";
    cin >> x;
    int val = intExp(n, x);
    cout << x << "^" << n << " after int exp: " << val << endl;
    return 0;
}
