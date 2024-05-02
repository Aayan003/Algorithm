#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> cd;

const double pi = acos(-1);

cd* FFT(const cd* S, int N, bool inverse) {
    cd* A = new cd[N];
    if (N == 1) {
        A[0] = S[0];
        return A;
    }
    else {
        double power = -2.0 * pi / N * (inverse ? -1 : 1);
        cd w(cos(power), sin(power));
        cd p = 1.0;

        cd* X = new cd[N/2];
        cd* Y = new cd[N/2];

        for (int i = 0; i < N / 2; i++) {
            X[i] = S[2 * i];
            Y[i] = S[2 * i + 1];
        }

        cd* B = FFT(X, N / 2, inverse);
        cd* C = FFT(Y, N / 2, inverse);

        for (int k = 0; k < N / 2; k++) {
            cd term = p * C[k];
            A[k] = B[k] + term;
            A[k + N / 2] = B[k] - term;
            if (inverse) {
                A[k] /= 2;
                A[k + N / 2] /= 2;
            }
            p *= w;
        }
        delete[] X;
        delete[] Y;
        delete[] B;
        delete[] C;
        return A;
    }
}
int main()
{
    int N;
    cout << "Enter number of points: ";
    cin >> N;
    if ((log(N) / log(2) - (int)(log(N) / log(2))) > 0.0)
    {
        int temp = log(N) / log(2);
        N = 2;
        N = N << temp;
    }
    cd* S = new cd[N];
    for (int i = 0; i < N; i++)
    {
        double var;
        cout << "Enter " << i + 1 << " point: " << endl;
        cout << "Real part: ";
        cin >> var;
        double imag;
        cout << "Imaginary part: ";
        cin >> imag;
        S[i] = {var, imag};
        cout << "Entered Number: " <<  S[i].real() << " + " <<  S[i].imag() << endl;
    }
    //FFT
    cd* A = new cd[N];
    A = FFT(S, N, false);
    cout << "FFT:" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << "th result: " <<  A[i].real() << " + " <<  A[i].imag() << "i" << endl;
    }
    //Inverse FFT
    cd* iA = new cd[N];
    iA = FFT(A, N, true);
    cout << "Inverse of the FFT:" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << "th result: " <<  iA[i].real() << " + " <<  iA[i].imag() << "i" << endl;
    }
    return 0;
}
