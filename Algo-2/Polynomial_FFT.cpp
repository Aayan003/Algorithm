#include <bits/stdc++.h>

using namespace std;

typedef complex<double> cd;

const double pi = acos(-1);

cd* FFT(cd* S, int N, bool inverse) {
	cd *A = new cd[N];
	if(N == 1) {
		A[0] = S[0];
		return A;
	}
	double power = -2 * pi / N * (inverse ? -1 : 1);
	cd w(cos(power), sin(power));
	cd p = 1;
	
	cd *X = new cd[N/2];
	cd *Y = new cd[N/2];
	for(int i = 0; i < N/2; ++i) {
		X[i] = S[2 * i];
		Y[i] = S[2 * i + 1];
	}
	
	cd *B = FFT(X, N/2, inverse);
	cd *C = FFT(Y, N/2, inverse);
	
	for(int r = 0; r < N/2; ++r) {
		cd term = p * C[r];
		A[r] = B[r] + term;
		A[r + N/2] = B[r] - term;
		if(inverse) {
			A[r] /= 2;
			A[r + N/2] /= 2;
		}
		p *= w;
	}
	
	delete[] X;
	delete[] Y;
	delete[] B;
	delete[] C;
	
	
	return A;
}

class Polynomial {
	private:
		int n;
		vector<double> coeff;
	public:
		Polynomial(int lim);
		friend istream& operator>>(istream& is, Polynomial& obj) {
			for(int i = 0; i < obj.n; ++i) {
				int cf;
				is >> cf;
				obj.coeff[i] = (double)cf;
			}
			return is;
		}
		friend ostream& operator<<(ostream& os, const Polynomial& obj);
		Polynomial operator*(const Polynomial& obj);
		double operator[](int i) const;
		int operator()(int x)const;
};

Polynomial :: Polynomial(int lim) {
	n = lim+1;
	coeff.resize(n, 0);
}

double Polynomial :: operator[](int i) const {
	return coeff[i];
}

int Polynomial :: operator()(int x)const{
            int i = n;
            int p = coeff[i];
            while(i >= 1){
                p = p * x + coeff[--i];
            }
            return p;
        }

ostream& operator<<(ostream& os, const Polynomial& obj) {
	for(int i = obj.n - 1; i >= 0; --i) {
		if(i != obj.n - 1 && obj[i] > 0)	//Checking if the coefficient is the 1st element and +ve
			os << " + ";
		if(obj[i] != 0) {
			if(obj[i] < 0)	//Checking if -ve
				os << " ";
			os << obj[i];
			if(i != 0)
				os << "x^" << i << " ";
			else  				//Don't print x when i = 0, as x^0 = 1
				continue;
		}
	}
	return os;
}

Polynomial Polynomial :: operator*(const Polynomial& obj) {
	int max = n + obj.n;
	if(log(max)/log(2) - (int)(log(max)/log(2)) > 0) {
		int temp = (int)(log(max)/log(2));
		max = 2;
		max <<= temp;
	}
	
	cd* A = new cd[max];
	for(int i = 0; i < max; ++i){
		if(i < n)
			A[i] = {coeff[i], 0};
		else
			A[i] = {0, 0};
	}
	cd* fA = FFT(A, max, false);
	cd* B = new cd[max];
	for(int i = 0; i < max; ++i){
		if(i < obj.n)
			B[i] = {obj[i], 0};
		else
			B[i] = {0, 0};
	}
	cd* fB = FFT(B, max, false);
	for(int i = 0; i < max; ++i) {
		fA[i] *= fB[i];
	}
	
	cd* re = FFT(fA, max, true);
	
	int k = max - 1;
	while(abs(re[k].real()) < 1e-10 && k >= 0)
		k--;
	Polynomial result(k);
	for(int i = k; i >= 0; --i)
		result.coeff[i] = re[i].real();
	
	delete[] A;
	delete[] fA;
	delete[] B;
	delete[] fB;
	delete[] re;


	return result;
}


int main() {
	int N1, N2;
	ifstream pol("polF.txt");	//Use a text file with same name which has the i/ps
	if(!pol) {					//Or you can modify the code accordingly
		cout << "Error!" << endl;
		return 1;
	}
	
	pol >> N1 >> N2;
	Polynomial P1(N1);
	Polynomial P2(N2);
	pol >> P1;
	cout << "1st Polynomial: " << P1 << endl;
	pol >> P2;
	cout << "2nd Polynomial: " << P2 << endl;
	
	Polynomial Result = P1 * P2;
	
	cout << "Resultant Polynomial: " <<  Result << endl;
	int x;
	pol >> x;
	int res = Result(x);
	cout << "Evaluation: " << res << endl;
	return 0;
}