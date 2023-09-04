#include <iostream>
#include <vector>
#include <cmath>



using namespace std;

long long mod;
int N;

void mul_circulant(vector<long long>& x, vector<long long>& y) {
    vector<long long> z(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++)
            z[i] += (x[j] * y[i-j])%mod;
        for (int j = i+1; j < N; j++)
            z[i] += (x[j] * y[i-j+N])%mod;
    }

    for (int i = 0; i < N; i++) {
        y[i] = z[i]%mod;
    }
}

int main() {
    int T,S,L,R,X;
    long long num;
    cin >> T;
    for (int i =0; i<T; i++)
    {
        cin >> N >> S >> L >> R >>X;
        mod= pow(10, X);
        vector<long long> numbers (N, 0);
        vector<long long> mat (N, 0);
        for (int j = 0; j< N;j++)
        {
            cin >> num;
            numbers[j] = num%mod;
        }
        mat[0] = 1, mat[1] = L, mat[N-1] = R;
        while (S) {
            if (S%2 == 1) {
                mul_circulant(mat, numbers);
            }
            mul_circulant(mat,mat);
            S = S >> 1;
        }
        for (int j = 0; j< N -1 ;j++)
            cout << numbers[j] << " ";
        cout << numbers[N-1] << endl;
    }
    return 0;
}