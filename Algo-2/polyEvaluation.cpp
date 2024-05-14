#include <iostream>
#include <vector>

using namespace std;

class Polynomial{
    private:
        vector<int> arr;
         int size;
    public:
        Polynomial(int sz) : size(sz) {}

        int operator()(int x)const;
    friend ostream& operator<<(ostream& os, const Polynomial& obj);
    friend istream& operator>>(istream& is, Polynomial& obj){
    for (int i = 0; i < obj.size + 1; ++i) {
            int coeff;
            cout << "Enter coefficient of x^" << i << ": ";
            is >> coeff;
            obj.arr.push_back(coeff);
    }
        return is;
    }
};

int Polynomial :: operator()(int x)const{
            int i = size;
            int p = arr[i];
            while(i >= 1){
                p = p * x + arr[--i];
            }
            return p;
        }

ostream& operator<<(ostream& os, const Polynomial& obj) {
    for(int i = obj.size; i >= 0; --i){

        if(obj.arr[i] != 0){

            cout<< obj.arr[i] << "x^" << i << " ";

            if(i != 0 && obj.arr[i] > 0)
            cout << '+';
        }
    }
    return os;
}

int main()
{
    int size;
    cout << "Enter the hishest power of the polynomial: ";
    cin >> size;
    Polynomial eqn(size);
    cin >> eqn;
    cout << eqn;
    int x;
    cout << endl << "Enter the value of x: ";
    cin >> x;
    int result = eqn(x);
    cout << "Evaluated result is: " << result << endl;
    return 0;
}
