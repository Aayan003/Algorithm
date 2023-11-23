#include <iostream>
#include <limits>
using namespace std;

class Compute
{
    private:
        int ***A, *dim, **m, **s, lim;
        void order()
        {
            for(int i = 0; i < lim - 1; i++)
            {
                m[i][i] = 0;
                for(int l = 1; l < lim; l++)
                {
                    for(int i = 0; i < lim - l; i++)
                    {
                        int j = i + l;
                        m[i][j] = numeric_limits<int>::max();
                        for(int k = i; k < j; k++)
                        {
                            int q = m[i][k] + m[k + 1][j] + dim[i] * dim[k + 1] * dim[j + 1];
                            if(q < m[i][j])
                            {
                                m[i][j] = q;
                                s[i][j] = k + 1;
                            }
                        }
                    }
                }
            }
        }
        void printPR(int ** inp)
        {
            for(int j = 0; j < lim; j++)
                    {for(int k = 0; k < lim; k++)
                        cout << inp[j][k] << "\t\t\t";
                cout << endl;}
        }
    public:
        void input()
        {
            cout << "Enter number of matrices: ";
            cin >> lim;
            dim = new int[lim + 1];
            cout << "Enter the dimensions: ";
            for(int i = 0; i <= lim; i++)
            {
                cin >> dim[i];
            }
            A = new int**[lim];
            for(int j = 0; j < lim; j++ )
            {
                A[j] = new int*[dim[j]];
                for(int k = 0; k < dim[j]; k++)
                {
                    A[j][k] = new int[dim[j + 1]];
                }
            }
            m = new int*[lim];
            s = new int*[lim];
            for(int i = 0; i < lim; i++)
            {
                m[i] = new int[lim];
                s[i] = new int[lim];
            }
            order();
            cout << "m Matrix: " << endl;
            printPR(m);
            cout << "s matrix: " << endl;
            printPR(s);
        }
        
};

int main()
{
    Compute cp;
    cp.input();
    return 0;
}
